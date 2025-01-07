#include "PackFolder.h"

/*
namespace mmt
{
	namespace core
	{
		void PackFolder::LoadFile(const std::string& path, miniz_cpp::zip_file& zip)
		{
			std::vector<std::string> pathParts;
			std::stringstream input(path);
			std::string part;
			while (std::getline(input, part, '/'))
			{
				pathParts.emplace_back(part);
			}

			if (pathParts.size() == 0)
			{
				LOG_F(ERROR, "Failed to load file: path is empty");
				return;
			}

			ResourceType type = GetResourceType(pathParts[0]);

			if (type == ResourceType::None)
			{
				LOG_F(ERROR, "Failed to load file: unknown resource type [%s]", pathParts[0]);
				return;
			}

			size_t size = pathParts.size();
			PackFolder& current = *this;
			for (size_t i = 0; i < size; ++i)
			{
				if (i != size)
				{
					// if subfolder exists, go to it
					// if not, create and go to it
					if (current.subFolders.contains(pathParts[i]))
						current = *current.subFolders.at(pathParts[i]);
					else
						current = *current.subFolders.emplace(pathParts[i],
							std::make_shared<PackFolder>(pathParts[i])).first->second;
					continue;
				}

				// load file as unsigned char* and get its extention
				std::string ext = path.substr(path.find_last_of('.'));
				std::string data = static_cast<std::ostringstream&>(zip.open(path)).str();
				const unsigned char* fileData = reinterpret_cast<const unsigned char*>(data.data());
				int dataSize = static_cast<int>(data.size());

				switch (type)
				{
				case ResourceType::Texture:
				case ResourceType::Object:
				{
					if (IsSupportedImageFormat(ext))
					{
						textures[pathParts.back()].res = std::make_shared<Texture2D>(
							LoadTextureFromImage(LoadImageFromMemory(ext.c_str(), fileData, dataSize)));
					}
					else LOG_F(ERROR, "Failed to load texture/object [%s]: image format [%s] is not supported",
						pathParts.back().c_str(), ext.c_str());
					break;
				}
				case ResourceType::Font:
				{
					if (IsSupportedFontFormat(ext))
					{
						fonts[pathParts.back()].res = std::make_shared<Font>(
							LoadFontFromMemory(ext.c_str(), fileData, dataSize, 96, nullptr, 0));
					}
					else LOG_F(ERROR, "Failed to load font [%s]: font format [%s] is not supported",
						pathParts.back().c_str(), ext.c_str());
					break;
				}
				case ResourceType::Script:
					LOG_F(WARNING, "Scripts are not implemented yet");
					break;
				default:
					break;
				}
			}
		}
		void PackFolder::Unload()
		{
			textures.clear();
			fonts.clear();
			for (auto& sf : subFolders) sf.second->Unload();
		}
		ResourceType PackFolder::GetResourceType(std::string_view path) const
		{
			if (path == "textures") return ResourceType::Texture;
			else if (path == "objects") return ResourceType::Object;
			else if (path == "fonts") return ResourceType::Font;
			else if (path == "scripts") return ResourceType::Script;
			else return ResourceType::None;
		}
	}
}
*/