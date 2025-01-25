#pragma once

#include "PackFolder.h"
#include "Resources.h"
#include "../../utility/StringUtil.h"

#include "raylib-cpp.hpp"

#include <functional>
#include <typeindex>


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
			std::shared_ptr<ResType> GetResource(const std::vector<std::string>& path);

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
			template<class ResType>
			void LoadResource(util::Zip& zip, const std::string& name, bool preload);
			//void LoadResource(ResourceType type, util::Zip& zip, const std::string& name, bool preload);

			MmtTexture LoadTexture(util::Zip& zip, const std::string& name);

			MmtObject LoadObject(util::Zip& zip, const std::string& name);
			
			MmtFont LoadFont(util::Zip& zip, const std::string& name);
			//Font LoadFont(const std::string& name);
			
		private:
			// when state is scanned
			template<class ResType>
			std::shared_ptr<ResType> LoadGetResource(const std::vector<std::string>& path);
			
			// when state is loaded
			template<class ResType>
			std::shared_ptr<ResType> FetchResource(const std::vector<std::string>& path);

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
		void Pack::LoadResource(util::Zip& zip, const std::string& name, bool preload)
		{
			auto parts = util::SplitByDelimiter(name, '/');
			if (parts.size() == 0)
			{
				LOG_F(ERROR, "Failed to load resource [%s]: resource path could not be split",
					name.c_str());
				return;
			}
			parts.erase(parts.begin()); // remove first part since type is already known

			PackFolder<ResType>* currentFolder = nullptr;

			if constexpr (std::is_same<ResType, MmtTexture>::value)
			{
				if (!IsSupportedImageFormat(util::GetExtension(name)))
				{
					LOG_F(ERROR, "Failed to load texture [%s]: image format [%s] is not supported",
						name.c_str(), util::GetExtension(name).c_str());
					return;
				}
				currentFolder = &textures;
			}
			else if constexpr (std::is_same<ResType, MmtObject>::value)
			{
				if (!IsSupportedImageFormat(util::GetExtension(name)))
				{
					LOG_F(ERROR, "Failed to load object [%s]: image format [%s] is not supported",
						name.c_str(), util::GetExtension(name).c_str());
					return;
				}
				currentFolder = &objects;
			}
			else if constexpr (std::is_same<ResType, MmtFont>::value)
			{
				if (!IsSupportedFontFormat(util::GetExtension(name)))
				{
					LOG_F(ERROR, "Failed to load font [%s]: font format [%s] is not supported",
						name.c_str(), util::GetExtension(name).c_str());
					return;
				}
				currentFolder = &fonts;
			}
			else if constexpr (std::is_same<ResType, MmtScript>::value)
			{
				// TODO
			}

			if (!currentFolder)
			{
				LOG_F(ERROR, "Failed to load resource [%s]: currentFolder is null", name.c_str());
				return;
			}

			for (size_t i = 0; i < parts.size(); ++i)
			{
				if (i == parts.size() - 1)
				{
					if (!preload)
					{
						std::string nm = util::RemoveExtension(parts[i]);
						currentFolder->res[nm] = std::make_shared<ResType>();
						currentFolder->res.at(nm)->Load(zip, name);
					}
					else
					{
						currentFolder->res[util::RemoveExtension(parts[i])] =
							std::make_shared<ResType>();
						LOG_F(INFO, "Pre-Loaded resource [%s]", name.c_str());
					}
				}
				else
				{
					if (currentFolder->subFolders.contains(parts[i]))
					{
						currentFolder = currentFolder->subFolders.at(parts[i]).get();
					}
					else
					{
						currentFolder->subFolders[parts[i]] = std::make_shared<PackFolder<ResType>>();
						auto sfp = currentFolder->subFolders[parts[i]];
						sfp->name = parts[i];
						currentFolder = sfp.get();
					}
				}
			}
		}

		template<class ResType>
		std::shared_ptr<ResType> Pack::GetResource(const std::vector<std::string>& path)
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
		std::shared_ptr<ResType> Pack::LoadGetResource(const std::vector<std::string>& path)
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
		std::shared_ptr<ResType> Pack::FetchResource(const std::vector<std::string>& path)
		{
			PackFolder<ResType>* currentFolder = nullptr;
			if constexpr (std::is_same<ResType, MmtTexture>::value) currentFolder = &textures;
			else if constexpr (std::is_same<ResType, MmtObject>::value) currentFolder = &objects;
			else if constexpr (std::is_same<ResType, MmtFont>::value) currentFolder = &fonts;
			else
			{
				LOG_F(ERROR, "Attempting to fetch a resource of unknown type [%s]", typeid(ResType).name());
				return nullptr;
			}
			//else if constexpr (std::is_same<ResType, MmtScript>::value) currentFolder = &scripts;
			for (size_t i = 0; i < path.size() - 1; ++i)
			{
				//currentFolder = currentFolder->subFolders.at(path[i]);
			}
			return currentFolder->res.at(path.end());
		}
		
	}
}