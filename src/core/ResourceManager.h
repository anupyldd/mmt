#pragma once

#include "raylib.h"
#include "picojson.h"

#include "../utility/Log.h"
#include "../utility/Defines.h"
#include "../utility/RresImpl.h"
#include "../utility/StringHash.h"
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

namespace hnd
{
	namespace core
	{
		constexpr unsigned char FOURCC_IMAGE[4] = { 'I','M','G','E' };
		constexpr unsigned char FOURCC_FONT[4]  = { 'F','N','T','G' };

		// -------------------------------------

		class ResourceManager
		{
			HND_SINGLETON(ResourceManager);
			
		public:
			void SetResourcePath(const std::filesystem::path& path);

			void Load();
			void Unload();

			void LoadPack(const std::string& name);
			void UnloadPack(const std::string& name);

		private:
			Pack LoadPack(const std::filesystem::path& path);
			void LoadPackMeta(Pack& pack, const std::filesystem::path& path);
			void LoadDirectory(Pack& pack, ResourceType type, const std::filesystem::path& path);
			void LoadArchive(Pack& pack, ResourceType type, const std::filesystem::path& path);
			void LoadFile(Pack& pack, const std::filesystem::path& path);
			
			ResourceHandle GenerateHandle(const std::string& packName, ResourceType type, const std::string& resName);

		private:
			PackRegistry packs;
			std::filesystem::path resPath;
			Font defaultFont{ 0 };
		};
	}
}