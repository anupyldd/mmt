#pragma once

#include "PackFolder.h"
#include "Resources.h"

#include "raylib.h"

#include <functional>

namespace mmt
{
	namespace core
	{
		class Pack
		{
		public:
			void Load(const std::filesystem::path& path);
			
			void PrintLoadedResources() const;

		private:
			void LoadResource(ResourceType type, util::Zip& zip, const std::string& name);
			Texture2D LoadTexture(util::Zip& zip, const std::string& name);
			Font LoadFont(util::Zip& zip, const std::string& name);
			
		private:
			std::string				name;

			PackFolder<Texture2D>	textures;
			PackFolder<Texture2D>	objects;
			PackFolder<Font>		fonts;
		};
	}
}