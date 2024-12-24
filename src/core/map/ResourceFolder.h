#pragma once

#include <string>
#include <map>
#include <memory>
#include <filesystem>

#include "Resources.h"

#include "log/loguru.hpp"

namespace mmt
{
	namespace core
	{
		namespace res
		{
			class PackFolder
			{
			public:
				PackFolder() = default;
				PackFolder(const std::string& name, ResourceType type) 
					: name(name), type(type) { }

				/*
				* takes in path like textures/subfolder/tex.png
				* breaks it into parts by /
				* iterates over vector of strings to load file into appropriate folder
				*/
				void LoadFile(const std::string& path)
				{
					std::vector<std::string> pathParts;
					std::stringstream input(path);
					std::string part;
					while (std::getline(input, part, '/'))
					{
						pathParts.emplace_back(part);
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
								current = *current.subFolders[pathParts[i]];
							else
								current = *current.subFolders.emplace(pathParts[i], 
									std::make_unique<PackFolder>(pathParts[i], type)).first->second;
							continue;
						}

						switch (type)
						{
						case ResourceType::Texture:
							break;
						case ResourceType::Object:
							break;
						case ResourceType::Font:
							break;
						case ResourceType::Script:
							break;
						case ResourceType::None:
							LOG_F(ERROR, "Failed to load resource from archive: folder type not set");
							break;
						default:
							break;
						}
					}
				}

				void Unload()
				{
					textures.clear();
					fonts.clear();
					for (auto& sf : subFolders) sf.second->Unload();
				}

			private:
				std::string name;
				ResourceType type = ResourceType::None;

				std::map<std::string, Resource<Texture2D>> textures;
				std::map<std::string, Resource<Font>> fonts;

				std::map<std::string, std::unique_ptr<PackFolder>> subFolders;
			};
		}
	}
}