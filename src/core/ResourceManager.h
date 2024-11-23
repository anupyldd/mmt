#pragma once

#include "raylib.h"

#include "../utility/Log.h"
#include "../utility/Defines.h"
#include "../utility/RresImpl.h"
#include "../utility/StringHash.h"
#include "Config.h"

#include <unordered_map>
#include <memory>
#include <cstdint>
#include <filesystem>
#include <string>
#include <variant>

namespace hnd
{
	namespace core
	{
		/*
		* order of resource loading
		* - resources directory is scanned recursively
		* - relative paths are hashed to form handles
		* - registry is populated
		*/

		constexpr unsigned char FOURCC_IMAGE[4] = { 'I','M','G','E' };
		constexpr unsigned char FOURCC_FONT[4]  = { 'F','N','T','G' };

		using ResourceHandle = uint32_t;

		struct Pack
		{
			std::string name;
			std::unordered_map<ResourceHandle, std::shared_ptr<Texture2D>> textures;
			std::unordered_map<ResourceHandle, std::shared_ptr<Font>> fonts;
		};
		
		using PackRegistry = std::unordered_map<std::string, Pack>;

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
			void LoadArchive(Pack& pack, const std::filesystem::path& path);
			void LoadFile(Pack& pack, const std::filesystem::path& path);
			
		private:
			PackRegistry packs;

			std::filesystem::path resPath;
		};
	}
}