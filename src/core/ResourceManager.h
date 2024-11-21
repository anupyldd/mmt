#pragma once

#include "raylib.h"

#include "../utility/Defines.h"

#include "../utility/RresImpl.h"

#include <unordered_map>
#include <memory>
#include <cstdint>
#include <filesystem>
#include <string>

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

		struct TextureData
		{
			std::string name;
			Texture2D	texture;
		};

		using AssetHandle = uint32_t;
		using TextureRegistry = std::unordered_map<uint32_t, std::shared_ptr<TextureData>>;
		using SpriteRegistry = std::unordered_map<uint32_t, std::shared_ptr<TextureData>>;

		class ResourceManager
		{
			HND_SINGLETON(ResourceManager);
			
		public:
			void Load();
			void Unload();

			void LoadPack(const std::string& name);

			const Texture2D& GetTexture(AssetHandle handle) const;
			const Texture2D& GetSprite(AssetHandle handle) const;

		private:
			TextureRegistry textures;
			SpriteRegistry	sprites;
		};
	}
}