#pragma once

#include "../../utility/Defines.h"
#include "Pack.h"
#include "../Localization.h"

#include <filesystem>
#include <map>
#include <vector>
#include <initializer_list>

namespace mmt
{
	namespace core
	{
		class PackManager
		{
			MMT_SINGLETON(PackManager);

		public:
			void SetSearchPath(const std::filesystem::path& rel);

			void LoadAll();
			void PreLoadAll();
			void ClearAll();

			/*
			pack - pack name
			type - resource type
			path - list of folder names that finishes with resource name
			*/
			template<class ResType>
			std::shared_ptr<ResType> GetResource(const std::vector<std::string>& path);

			const raylib::Texture2D& GetPreview(const std::vector<std::string>& path);

			void LoadSelected(const std::unordered_map<std::string, bool>& sel);
			void PreLoadSelected(const std::unordered_map<std::string, bool>& sel);
			void ClearSelected(const std::unordered_map<std::string, bool>& sel);

			// scans the pack dir and loads pack names
			void FindAvailable();

			const std::map<std::string, Pack>& GetPackList() const;

		private:
			std::filesystem::path path;
			std::map<std::string, Pack> packs;
		};

		// --------------------------------
		template<class ResType>
		std::shared_ptr<ResType> PackManager::GetResource(const std::vector<std::string>& path)
		{
			//return packs.at(pack).GetResource
			const auto& pack = path[0];
			if (path[1] == LocC("textures")) packs.at(pack).GetResource<MmtTexture>(path);
			else if (path[1] == LocC("objects")) packs.at(pack).GetResource<MmtObject>(path);
			else if (path[1] == LocC("fonts")) packs.at(pack).GetResource<MmtFont>(path);
			else if (path[1] == LocC("scripts")) packs.at(pack).GetResource<MmtScript>(path);
			else return nullptr;

			/*
			ResourceType type =
				path[1] == LocC("textures")	? ResourceType::Texture :
				path[1] == LocC("objects")	? ResourceType::Object :
				path[1] == LocC("fonts")	? ResourceType::Font :
				path[1] == LocC("scripts")	? ResourceType::Script : ResourceType::None;

			switch (type)
			{
			case ResourceType::Texture: 
				return packs.at(pack).GetResource<MmtTexture>(std::vector<std::string>(path.begin() + 1, path.end()));
			case ResourceType::Object:
				return packs.at(pack).GetResource<MmtObject>(std::vector<std::string>(path.begin() + 1, path.end()));
			case ResourceType::Font:
				return packs.at(pack).GetResource<MmtFont>(std::vector<std::string>(path.begin() + 1, path.end()));
			case ResourceType::Script:
				return packs.at(pack).GetResource<MmtTexture>(std::vector<std::string>(path.begin() + 1, path.end()));
			default: return nullptr;
			}
			*/
		}
	}
}