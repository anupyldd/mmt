#pragma once

#include "PackFolder.h"
#include "Resources.h"
//#include "../../utility/Zip.h"

#include "raylib.h"

#include <functional>



namespace mmt
{
	namespace core
	{
		class Pack
		{
		public:
			// loads all resources
			void Load(const std::filesystem::path& path);
			// loads only names
			void PreLoad(const std::filesystem::path& path);
			
			// load specific resource
			//std::shared_ptr<Texture2D>	LoadGetTexture(const std::string& name);
			//std::shared_ptr<Texture2D>	LoadGetObject(const std::string& name);
			//std::shared_ptr<Font>		LoadGetFont(const std::string& name);


		public:
			// unloads and clears all loaded resources
			void Clear();

			std::string GetStats() const;
			void PrintLoadedResources() const;

		private:
			void LoadResource(ResourceType type, util::Zip& zip, const std::string& name, bool preload);

			Texture2D LoadTexture(util::Zip& zip, const std::string& name);
			//Texture2D LoadTexture(const std::string& name);
			
			Font LoadFont(util::Zip& zip, const std::string& name);
			//Font LoadFont(const std::string& name);
			
		private:
			std::string	name;
			std::unique_ptr<util::Zip> zip;

			PackFolder<Texture2D>	textures;
			PackFolder<Texture2D>	objects;
			PackFolder<Font>		fonts;
		};
	}
}