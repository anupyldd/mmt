#pragma once

#include "EcsInstance.h"
#include "MapUtil.h"
#include "EcsTypes.h"
#include "../../utility/Defines.h"

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <utility>

#define ECS_MGR hnd::core::EcsManager::GetInstance()

namespace hnd
{
	namespace core
	{

		// { atlas_name : { map_name : ecs_instance } }
		using EcsInstanceMap = std::unordered_map<std::string, std::unordered_map<std::string, std::unique_ptr<EcsInstance>>>;
		// { atlas_name : { map_name : ecs_instance } }
		using EcsActiveInstance = std::pair<std::string, std::pair<std::string, EcsInstance*>>;

		/*
		* manages ecs instances.
		* each instance is associated with 1 map, 1 map can have only 1 instance.
		* instances are loaded/saved/etc by map name.
		* ecs manager works in together with atlases, but not managed by them.
		* only one instance of EcsManager exists in a program.
		*/
		class EcsManager
		{
			SINGLETON(EcsManager);

		public:
			// creates default instance
			void CreateInstance(const std::string& atlasName, const std::string& mapName, int maxEntityCount);

			// loads previously saved instance from file by name
			void LoadInstace(const std::string& atlasName, const std::string& mapName);

			void DestroyInstance(const std::string& atlasName, const std::string& mapName);

			void SetActiveInstace(const std::string& atlasName, const std::string& mapName);

			void UpdateActive();

		public:

			EcsInstance* GetActiveInstance() const;
			ComponentId GetActiveComponentId(const std::string& compName) const;

		private:
			bool InstanceExists(const std::string& atlasName, const std::string& mapName) const;
			std::filesystem::path GetInstanceFilePath(const std::string& atlasName, const std::string& mapName) const;

		private:
			EcsInstanceMap instances;
			EcsActiveInstance activeInstance;
		};
	}
}