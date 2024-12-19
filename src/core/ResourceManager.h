#pragma once

#include "raylib.h"
#include "json/picojson.h"

#include "../utility/Log.h"
#include "../utility/Defines.h"
#include "../utility/RresImpl.h"
#include "../utility/StringUtil.h"
#include "map/ResourcePack.h"
#include "Config.h"

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
		class ResourceManager
		{
			MMT_SINGLETON(ResourceManager);
			
		public:
			void View();	// checks all the available packs, but does not load them
			const std::unordered_map<std::string, Pack>& GetPackMap() const;
			void SetPackLoad(const std::string& pack, bool load);

			void Load();
			void Unload();

			void LoadApp();

			void LoadPack(const std::string& name);
			void UnloadPack(const std::string& name);

		private:
			Pack LoadPack(const std::filesystem::path& path);
			void LoadPackMeta(Pack& pack, const std::filesystem::path& path);
			void LoadDirectory(Pack& pack, ResourceType type, const std::filesystem::path& path);
			void LoadArchive(Pack& pack, ResourceType type, const std::filesystem::path& path);
			void LoadFile(Pack& pack, const std::filesystem::path& path);
			
		private:
			std::unordered_map<std::string, Pack> packs;
			std::filesystem::path packPath = std::filesystem::current_path() / "data" / "res" / "packs";

			Font	defaultFont{ 0 };
			Image	appIcon{ 0 };
		};
	}
}