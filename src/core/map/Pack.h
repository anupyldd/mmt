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

			const PackFolder<MmtTexture>& GetTextureFolder() const;
			const PackFolder<MmtObject>& GetObjectFolder() const;
			const PackFolder<MmtFont>& GetFontFolder() const;

		private:
			void LoadResource(ResourceType type, util::Zip& zip, const std::string& name, bool preload);

			MmtTexture LoadTexture(util::Zip& zip, const std::string& name);

			MmtObject LoadObject(util::Zip& zip, const std::string& name);
			
			MmtFont LoadFont(util::Zip& zip, const std::string& name);
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

			PackFolder<MmtTexture>	textures;
			PackFolder<MmtObject>	objects;
			PackFolder<MmtFont>		fonts;
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
			PackFolder<ResType>* currentFolder = nullptr;
			if constexpr (std::is_same<ResType, MmtTexture>::value)
			{
				currentFolder = &textures;
			}
			else if constexpr (std::is_same<ResType, MmtObject>::value)
			{
				currentFolder = &objects;
			}
			else if constexpr (std::is_same<ResType, MmtFont>::value)
			{
				currentFolder = &fonts;
			}
			for (size_t i = 0; i < path.size(); ++i)
			{
				if (i == path.size() - 1)
				{
					//currentFolder->res.at()
				}
			}
		}

		template<class ResType>
		std::shared_ptr<ResType> Pack::FetchResource(const std::initializer_list<std::string>& path)
		{
			
		}
		
	}
}