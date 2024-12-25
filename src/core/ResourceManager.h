#pragma once

#include "raylib.h"
#include "json/picojson.h"

#include "../utility/Log.h"
#include "../utility/Defines.h"
#include "../utility/StringUtil.h"
#include "Config.h"
#include "map/Resources.h"
#include "map/PackFolder.h"

#include <unordered_map>
#include <memory>
#include <cstdint>
#include <filesystem>
#include <string>
#include <variant>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string.h>

namespace mmt
{
	namespace core
	{
		class PackFolder;
		class PackRegistry;

		/*
		* steps for resource manager:
		* 1) PreLoad() before main menu to get list of packs and load the registry
		* 2) Load() when a map is first opened
		* 3) LoadPack() or UnloadPack() on demand
		*/


		class ResourceManager
		{
			MMT_SINGLETON(ResourceManager);
			
		public:
			~ResourceManager();

			// checks all the available packs, but does not load them
			void PreLoad();	

			const std::unordered_map<std::string, PackFolder>& GetPackMap() const;

			// sets shouldLoad for a pack
			void SetPackLoad(const std::string& pack, bool load);

			// general load that is run once on start
			void Load();

			// general unload that is run once on exit
			void Unload() {};

			// loads app icon, font
			void LoadApp();	

			// loads a specific pack, after general Load()
			void LoadPack(const std::string& name);

			// unloads a specific pack, after general Load()
			void UnloadPack(const std::string& name);

		private:
			//void LoadPack(const std::filesystem::path& path);
			//void LoadPackMeta(Pack& pack, const std::filesystem::path& path);
			//void LoadDirectory(Pack& pack, ResourceType type, const std::filesystem::path& path);
			//void LoadArchive(Pack& pack, ResourceType type, const std::filesystem::path& path);
			//void LoadFile(Pack& pack, const std::filesystem::path& path);

			void LoadPackRegistry();
			void SavePackRegistry();
			
		private:
			std::unordered_map<std::string, PackFolder> packs;
			std::filesystem::path packPath = std::filesystem::current_path() / "data" / "res" / "packs";
			std::unique_ptr<PackRegistry> packReg;

			Font	defaultFont{ 0 };
			Image	appIcon{ 0 };
		};
	}
}