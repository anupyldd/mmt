#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>

namespace hnd
{
	namespace core
	{
		enum class ResourceType { Texture, Object, Font, None };

		using ResourceHandle = uint32_t;

		struct TextureData
		{
			TextureData() = default;
			TextureData(const std::string& name, std::shared_ptr<Texture2D> tex)
				: name(name), texture(tex) { }

			std::string name;
			std::shared_ptr<Texture2D> texture;
		};

		struct FontData
		{
			FontData() = default;
			FontData(const std::string& name, std::shared_ptr<Font> font)
				: name(name), font(font) { }

			std::string name;
			std::shared_ptr<Font> font;
		};

		struct Pack
		{
			std::string name,
				author,
				license,
				version,
				description,
				lastUpdate;
			//std::unordered_map<ResourceHandle, std::shared_ptr<Texture2D>> textures;
			//std::unordered_map<ResourceHandle, std::shared_ptr<Texture2D>> objects;
			//std::unordered_map<ResourceHandle, std::shared_ptr<Font>> fonts;
			std::unordered_map<ResourceHandle, TextureData> textures;
			std::unordered_map<ResourceHandle, TextureData> objects;
			std::unordered_map<ResourceHandle, FontData> fonts;
		};

		using PackRegistry = std::unordered_map<std::string, Pack>;
	}
}