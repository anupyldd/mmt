#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>

namespace mmt
{
	namespace core
	{
		enum class ResourceType { Texture, Object, Font, None };

		using ResourceHandle = uint32_t;

		struct TextureData
		{
			TextureData() = default;
			TextureData(const std::string& name, ResourceHandle handle, std::shared_ptr<Texture2D> tex)
				: name(name), handle(handle), texture(tex) { }

			std::string name;
			ResourceHandle handle;
			std::shared_ptr<Texture2D> texture;
		};

		struct FontData
		{
			FontData() = default;
			FontData(const std::string& name, ResourceHandle handle, std::shared_ptr<Font> font)
				: name(name), handle(handle), font(font) { }

			std::string name;
			ResourceHandle handle;
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
			std::unordered_map<std::string, TextureData> textures;
			std::unordered_map<std::string, TextureData> objects;
			std::unordered_map<std::string, FontData> fonts;
		};

		using PackRegistry = std::unordered_map<std::string, Pack>;
	}
}