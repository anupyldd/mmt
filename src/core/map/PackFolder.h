#pragma once

#include <string>
#include <map>
#include <memory>
#include <filesystem>
#include <optional>

#include "Resources.h"
#include "../../utility/Zip.h"

#include "log/loguru.hpp"
/*
namespace mmt
{
	namespace core
	{

		class PackFolder
		{
		public:
			PackFolder() = default;
			PackFolder(const std::string& name) 
				: name(name) { }

			//
			//takes in path like textures/subfolder/tex.png
			//breaks it into parts by /
			//iterates over vector of strings to load file into appropriate folder
			//
			void LoadFile(const std::string& path, miniz_cpp::zip_file& zip);

			// recursively unloads entire folder
			void Unload();

		private:
			ResourceType GetResourceType(std::string_view path) const;

		private:
			std::string name;

			std::map<std::string, Resource<Texture2D>> textures;
			std::map<std::string, Resource<Font>> fonts;

			std::map<std::string, std::shared_ptr<PackFolder>> subFolders;
		};
		
	}
}
*/