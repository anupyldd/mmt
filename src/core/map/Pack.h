#pragma once

#include "PackFolder.h"
#include "Resources.h"

#include "raylib.h"

namespace mmt
{
	namespace core
	{
		class Pack
		{
		public:
			void Load(const std::filesystem::path& path);

		private:
			void LoadResource(ResourceType type, util::Zip& zip, const std::vector<std::string>& parts);

		private:
			PackFolder<Texture2D>	textures;
			PackFolder<Texture2D>	objects;
			PackFolder<Font>		fonts;
		};
	}
}