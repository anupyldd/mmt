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

namespace mmt
{
	namespace core
	{
		class EcsInstance;

		// { atlas_name : { map_name : ecs_instance } }
		using EcsInstanceMap = std::unordered_map<std::string, std::unordered_map<std::string, std::unique_ptr<EcsInstance>>>;
		// { atlas_name : { map_name : ecs_instance } }
		using EcsActiveInstance = std::pair<std::string, std::pair<std::string, EcsInstance*>>;

		// -----------------------

		class EcsManager
		{
			MMT_SINGLETON(EcsManager);

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

		inline EcsManager& EcsMgr() { return EcsManager::GetInstance(); }
	}
}