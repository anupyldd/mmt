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
				//std::cout << infos[i].type << '\n';
				rresResourceChunk chunk = rresLoadResourceChunk(spath.c_str(), infos[i].id);
				int unp = UnpackResourceChunk(&chunk);
				if (infos[i].type == FOURCC_IMAGE)
				{
					Image img = LoadImageFromResource(chunk);
					pack.textures[HashString32(spath.c_str())] = std::make_shared<Texture2D>(LoadTextureFromImage(img));
					UnloadImage(img);
				}
				else if (infos[i].type == FOURCC_FONT)
				{

				}
				rresUnloadResourceChunk(chunk);
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