#pragma once

#include "../../utility/Defines.h"
#include "Pack.h"

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
			//template<class ResType>
			//std::shared_ptr<ResType> GetResource(const std::string& pack, ResourceType type, 
			//	const std::initializer_list<std::string>& path);

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
		//template<class ResType>
		//std::shared_ptr<ResType> GetResource(const std::string& pack, ResourceType type,
		//	const std::initializer_list<std::string>& path)
		//{
		//
		//}
	}
}