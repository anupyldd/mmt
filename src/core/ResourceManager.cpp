#include "ResourceManager.h"

#include "raylib.h"
#include "log/loguru.hpp"

namespace mmt
{
	namespace core
	{
		void ResourceManager::SetResourcePath(const std::filesystem::path& path)
		{
			resPath = std::filesystem::current_path() / path;
		}
		void ResourceManager::Load()
		{
			try
			{
				SetResourcePath(std::filesystem::path("data/resources/packs"));
				LoadApp();

				for (const auto& entry : std::filesystem::directory_iterator(resPath))
				{
					if (entry.is_directory())
					{
						packs[entry.path().filename().stem().string()] = LoadPack(entry.path());
					}
				}

			#if _DEBUG
				DLOG_F(INFO, "Loaded packs: ------------------");
				for (const auto& p : packs)
				{
					DLOG_F(INFO, p.second.name.c_str());
					DLOG_F(INFO, p.second.author.c_str());
					DLOG_F(INFO, p.second.license.c_str());
					DLOG_F(INFO, p.second.version.c_str());
					DLOG_F(INFO, p.second.lastUpdate.c_str());
					DLOG_F(INFO, p.second.description.c_str());
					DLOG_F(INFO, "\ttextures:");
					for (const auto& t : p.second.textures)
					{
						DLOG_F(INFO, t.second.name.c_str());
						DLOG_F(INFO, std::to_string(t.second.handle).c_str());
					}
					DLOG_F(INFO, "\tobjects:");
					for (const auto& o : p.second.objects)
					{
						DLOG_F(INFO,o.second.name.c_str());
						DLOG_F(INFO,std::to_string(o.second.handle).c_str());
					}
					DLOG_F(INFO, "\tfonts:");
					for (const auto& f : p.second.textures)
					{
						DLOG_F(INFO, f.second.name.c_str());
						DLOG_F(INFO, std::to_string(f.second.handle).c_str());
					}
				#endif
				}
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, "Failed to load resources: %s", e.what());
			}
		}
		void ResourceManager::LoadApp()
		{
			auto path = std::filesystem::current_path() / "data" / "resources" / "app";
			DLOG_F(INFO, path.string().c_str());
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.path().extension().string() == ".ttf")
				{
					defaultFont = LoadFont(entry.path().string().c_str());
				}
				else if (entry.path().extension().string() == ".png")
				{
					appIcon = LoadImage(entry.path().string().c_str());
				}
			}
			if (!IsFontValid(defaultFont)) LOG_F(ERROR, "Invalid default font");
			if (IsImageValid(appIcon)) SetWindowIcon(appIcon);
		}
		Pack ResourceManager::LoadPack(const std::filesystem::path& path)
		{
			DLOG_F(INFO, "Loading pack at %s", path.string());

			Pack pack;

			// loading metadata
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				std::string fileName = entry.path().filename().string();
				std::transform(fileName.begin(), fileName.end(), fileName.begin(),
					[](unsigned char c) { return std::tolower(c); });
				
				if (fileName == "metadata.json")
				{
					LoadPackMeta(pack, entry.path());
				}
			}

			// loading resources
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				std::string fileName = entry.path().filename().string();
				std::transform(fileName.begin(), fileName.end(), fileName.begin(),
					[](unsigned char c) { return std::tolower(c); });

				if (entry.is_directory())
				{
					ResourceType type = ResourceType::None;
					if (fileName == "textures") type = ResourceType::Texture;
					else if (fileName == "objects") type = ResourceType::Object;
					else if (fileName == "fonts") type = ResourceType::Font;

					if (type != ResourceType::None)LoadDirectory(pack, type, entry.path());
				}
			}

			return pack;
		}

		void ResourceManager::LoadPackMeta(Pack& pack, const std::filesystem::path& path)
		{
			DLOG_F(INFO, "Loading metadata");

			std::ifstream file(path);
			std::stringstream contents;
			contents << file.rdbuf();

			std::string strCont = contents.str();
			picojson::value val;

			std::string err = picojson::parse(val, strCont);
			if (!err.empty()) LOG_F(ERROR, "Failed to parse meta file at %s: %s",
				path.string(), err);

			if (!val.is<picojson::object>()) LOG_F(ERROR, "Meta json at %s is not an object",
				path.string());

			const picojson::value::object& obj = val.get<picojson::object>();
			
			pack.name = obj.at("name").get<std::string>();
			pack.author = obj.at("author").get<std::string>();
			pack.license = obj.at("license").get<std::string>();
			pack.version = obj.at("version").get<std::string>();
			pack.lastUpdate = obj.at("last_update").get<std::string>();
			pack.description = obj.at("description").get<std::string>();

			DLOG_F(INFO, "Pack metadata:\n%s\n%s\n%s\n%s\n%s\n%s",
				pack.name, pack.author, pack.license, pack.version, pack.lastUpdate, pack.description);
		}

		void ResourceManager::LoadDirectory(Pack& pack, ResourceType type, const std::filesystem::path& path)
		{
			using namespace util;

			for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
			{
				// archive loading handles different types of resources itself
				if (entry.path().extension() == ".rres")
				{
					LoadArchive(pack, type, entry.path());
				}
				// loading objects or textures
				else if ((
					entry.path().extension() == ".jpg"  ||
					entry.path().extension() == ".jpeg" ||
					entry.path().extension() == ".png"  ||
					entry.path().extension() == ".tga"  ||
					entry.path().extension() == ".bmp") &&
					type != ResourceType::Font)
				{
					Image img = LoadImage(entry.path().string().c_str());

					if (type == ResourceType::Texture)
					{
						pack.textures[entry.path().filename().string()] =
							TextureData(entry.path().stem().string(), 
								GenerateHandle(pack.name, type, entry.path().filename().string()),
								std::make_shared<Texture2D>(LoadTextureFromImage(img)));

						DLOG_F(INFO, "Loaded texture: %s", entry.path().filename().string());
					}
					else
					{
						pack.objects[entry.path().filename().string()] =
							TextureData(entry.path().stem().string(),
								GenerateHandle(pack.name, type, entry.path().filename().string()),
								std::make_shared<Texture2D>(LoadTextureFromImage(img)));

						DLOG_F(INFO, "Loaded object: %s", entry.path().filename().string());
					}

					UnloadImage(img);
				}
				// loading fonts
				else if ((
					entry.path().extension() == ".ttf"  ||
					entry.path().extension() == ".otf") &&
					type == ResourceType::Font)
				{
					pack.fonts[entry.path().filename().string()] =
						FontData(entry.path().stem().string(), 
							GenerateHandle(pack.name, type, entry.path().filename().string()),
							std::make_shared<Font>(LoadFont(entry.path().string().c_str())));

					DLOG_F(INFO, "Loaded font: %s", entry.path().filename().string());
				}
			}
		}

		ResourceHandle ResourceManager::GenerateHandle(const std::string& packName, ResourceType type, const std::string& resName)
		{
			std::string strType;
			switch (type)
			{
			case ResourceType::Texture: strType = "texture"; break;
			case ResourceType::Object:	strType = "object"; break;
			case ResourceType::Font:	strType = "font"; break;
			default: break;
			}
			std::stringstream sstr;
			sstr << resPath.string() << strType << resName;
			return util::HashString32(sstr.str().c_str());
		}

		bool ResourceManager::SameFourCC(const unsigned char first[4], const unsigned char second[4]) const
		{
			return	first[0] == second[0] && 
					first[1] == second[1] && 
					first[2] == second[2] && 
					first[3] == second[3];
		}

		void ResourceManager::LoadArchive(Pack& pack, ResourceType type, const std::filesystem::path& path)
		{
			using namespace util;
			DLOG_F(INFO, "ARCHIVE: %s", path.filename().string());

			std::string spath = path.string();

			rresCentralDir dir = rresLoadCentralDirectory(spath.c_str());
			if (dir.count == 0) DLOG_F(INFO, "ARCHIVE: No central directory");

			unsigned int chunkCount = 0;
			rresResourceChunkInfo* infos = rresLoadResourceChunkInfoAll(spath.c_str(), &chunkCount);
			unsigned int prevId = 0;

			for (unsigned int i = 0; i < chunkCount; i++)
			{
				// skips fonts in tex/obj dirs and tex/obj in font dir
				if ((SameFourCC(infos[i].type, FOURCC_IMAGE) && type == ResourceType::Font) ||
					SameFourCC(infos[i].type, FOURCC_FONT) && (type == ResourceType::Texture|| type==ResourceType::Object))
					continue;

				std::string name;
				for (unsigned int j = 0; j < dir.count; j++)
				{
					if ((infos[i].id == dir.entries[j].id) && (infos[i].id != prevId))
					{
						name = std::string(dir.entries[j].fileName);
						prevId = dir.entries[j].id;
						break;
					}
				}

				if(SameFourCC(infos[i].type, FOURCC_IMAGE))
				{
					rresResourceChunk chunk = rresLoadResourceChunk(spath.c_str(), infos[i].id);
					int result = UnpackResourceChunk(&chunk);
					if (result == 0)
					{
						Image img = LoadImageFromResource(chunk);
						if (type == ResourceType::Texture)
						{
							pack.textures[name] =
								TextureData(
									name,
									GenerateHandle(pack.name, type, name),
									std::make_shared<Texture2D>(LoadTextureFromImage(img)));

							DLOG_F(INFO, "ARCHIVE: loaded texture: %s", name);
						}
						else
						{
							pack.objects[name] =
								TextureData(
									name, 
									GenerateHandle(pack.name, type, name),
									std::make_shared<Texture2D>(LoadTextureFromImage(img)));

							DLOG_F(INFO, "ARCHIVE: loaded object: %s", name);
						}
						UnloadImage(img);
					}
					else LOG_F(ERROR, "Failed to unpack resource chunk");

					rresUnloadResourceChunk(chunk);
				}
				else if (SameFourCC(infos[i].type, FOURCC_FONT))
				{
					rresResourceMulti multi = rresLoadResourceMulti(spath.c_str(), infos[i].id);
					int result = -1;
					for (unsigned int i = 0; i < multi.count; i++)
					{
						result = UnpackResourceChunk(&multi.chunks[i]);
						if (result != 0) LOG_F(ERROR, "Failed to unpack multi resource chunk");
					}
					if (result == 0)
					{
						pack.fonts[name]= 
							FontData(
								name, 
								GenerateHandle(pack.name, type, name),
								std::make_shared<Font>(LoadFontFromResource(multi)));

						DLOG_F(INFO, "ARCHIVE: loaded font: %s", name);
					}
					rresUnloadResourceMulti(multi);
				}
			}
		}

		/*
		void ResourceManager::LoadArchive(Pack& pack, ResourceType type, const std::filesystem::path& path)
		{
			using namespace util;
			MMT_LOG_DEBUG("ARCHIVE: " + path.filename().string());

			std::string spath = path.string();

			rresCentralDir dir = rresLoadCentralDirectory(spath.c_str());
			if (dir.count == 0) MMT_LOG_DEBUG("ARCHIVE: No central directory");

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
					else MMT_LOG_ERROR(
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
						if (result != 0) MMT_LOG_ERROR(
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
			//MMT_LOG_DEBUG("FILE: " + path.filename().string());
		}
		*/
	}
}