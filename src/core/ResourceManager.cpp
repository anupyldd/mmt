#include "ResourceManager.h"

#include "raylib.h"

namespace hnd
{
	namespace core
	{
		void ResourceManager::SetResourcePath(const std::filesystem::path& path)
		{
			resPath = std::filesystem::current_path() / path;
		}
		void ResourceManager::Load()
		{
			SetResourcePath(std::filesystem::path(Config::GetInstance().meta->resourceRelPath));

			for (const auto& entry : std::filesystem::directory_iterator(resPath))
			{
				if (entry.is_directory())
				{
					packs[entry.path().filename().stem().string()] = LoadPack(entry.path());
				}
			}
		}
		Pack ResourceManager::LoadPack(const std::filesystem::path& path)
		{
			Pack pack;
			for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
			{
				if (entry.path().filename().extension().string() == ".rres")
				{
					LoadArchive(pack, entry.path());
				}
				else if (entry.is_regular_file())
				{
					LoadFile(pack, entry.path());
				}
			}
			return pack;
		}
		void ResourceManager::LoadArchive(Pack& pack, const std::filesystem::path& path)
		{
			using namespace util;
			HND_LOG_DEBUG("ARCHIVE: " + path.filename().string());

			std::string spath = path.string();

			rresCentralDir dir = rresLoadCentralDirectory(spath.c_str());
			if (dir.count == 0) HND_LOG_DEBUG("ARCHIVE: No central directory");

			unsigned int chunkCount = 0;
			rresResourceChunkInfo* infos = rresLoadResourceChunkInfoAll(spath.c_str(), &chunkCount);

			for (unsigned int i = 0; i < chunkCount; ++i)
			{
				if (infos[i].type == FOURCC_IMAGE)
				{
					rresResourceChunk chunk = rresLoadResourceChunk(spath.c_str(), infos[i].id);
					int result = UnpackResourceChunk(&chunk);
					if (result == 0)
					{
						Image img = LoadImageFromResource(chunk);
						pack.textures[HashString32(spath.c_str())]
							= std::make_shared<Texture2D>(LoadTextureFromImage(img));
						UnloadImage(img);
					}
					else HND_LOG_ERROR(
						std::format("Failed to unpack resource chunk (id:{})", infos[i].id));

					rresUnloadResourceChunk(chunk);
				}
				else if (infos[i].type == FOURCC_FONT)
				{
					rresResourceMulti multi = rresLoadResourceMulti(spath.c_str(), infos[i].id);
					int result = -1;
					for (unsigned int i = 0; i < multi.count; i++)
					{
						result = UnpackResourceChunk(&multi.chunks[i]); 
						if (result != 0) HND_LOG_ERROR(
							std::format("Failed to unpack multi resource chunk (id:{}, i:{})", infos[i].id, i));
					}
					if (result == 0)   
					{
						pack.fonts[HashString32(spath.c_str())]
							= std::make_shared<Font>(LoadFontFromResource(multi));
					}
					rresUnloadResourceMulti(multi);
				}
			}

			rresUnloadCentralDirectory(dir);
			RRES_FREE(infos);
		}
		void ResourceManager::LoadFile(Pack& pack, const std::filesystem::path& path)
		{
			//HND_LOG_DEBUG("FILE: " + path.filename().string());
		}
	}
}