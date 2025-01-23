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
		enum class PackState
		{
			Unloaded, Scanned, Loaded
		};

		class Pack
		{
		public:
			// loads all resources
			void Load(const std::filesystem::path& path);
			// loads only names
			void PreLoad(const std::filesystem::path& path);
			
			// get specific resource
			template<class ResType>
			std::shared_ptr<ResType> GetResource(const std::initializer_list<std::string>& path);

		public:
			// unloads and clears all loaded resources
			void Clear();

			std::string GetStats() const;
			PackState GetState() const;
			void PrintLoadedResources() const;

			const PackFolder<Texture2D>& GetTextureFolder() const;
			const PackFolder<Texture2D>& GetObjectFolder() const;
			const PackFolder<Font>& GetFontFolder() const;

		private:
			void LoadResource(ResourceType type, util::Zip& zip, const std::string& name, bool preload);

			Texture2D LoadTexture(util::Zip& zip, const std::string& name);
			//Texture2D LoadTexture(const std::string& name);
			
			Font LoadFont(util::Zip& zip, const std::string& name);
			//Font LoadFont(const std::string& name);
			
		private:
			// when state is scanned
			template<class ResType>
			std::shared_ptr<ResType> LoadGetResource(const std::initializer_list<std::string>& path);

			// when state is loaded
			template<class ResType>
			std::shared_ptr<ResType> FetchResource(const std::initializer_list<std::string>& path);

		private:
			std::string	name;
			std::unique_ptr<util::Zip> zip;
			PackState state = PackState::Unloaded;

			PackFolder<Texture2D>	textures;
			PackFolder<Texture2D>	objects;
			PackFolder<Font>		fonts;
		};

		// -------------------------------------

		template<class ResType>
		std::shared_ptr<ResType> Pack::GetResource(const std::initializer_list<std::string>& path)
		{
			switch (state)
			{
			case PackState::Unloaded:
			default:
			{
				LOG_F(ERROR, "Attempting to get resource [%s] from unloaded pack [%s]",
					path.end()->c_str(), name);
				return nullptr;
			}
			case PackState::Scanned:
			{
				return LoadGetResource<ResType>(path);
			}
			case PackState::Loaded:
			{
				return FetchResource<ResType>(path);
			}
			}
		}

		template<class ResType>
		std::shared_ptr<ResType> Pack::LoadGetResource(const std::initializer_list<std::string>& path)
		{
			
		}

		template<class ResType>
		std::shared_ptr<ResType> Pack::FetchResource(const std::initializer_list<std::string>& path)
		{
			if constexpr (std::is_same<ResType, )
		}

	}
}