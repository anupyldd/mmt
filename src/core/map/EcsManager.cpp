#include "EcsManager.h"

namespace hnd
{
	namespace core
	{
		void EcsManager::CreateInstance(const std::string& atlasName, const std::string& mapName, int maxEntityCount)
		{
			if (InstanceExists(atlasName, mapName))
			{
				HND_LOG_ERROR(std::format("Failed to create ECS instance for map {}: instance for this map already exists", mapName));
				return;
			}

			instances[atlasName][mapName] = std::make_unique<EcsInstance>();
			instances.at(atlasName).at(mapName)->Init(maxEntityCount);
		}
		void EcsManager::LoadInstace(const std::string& atlasName, const std::string& mapName)
		{
			if (InstanceExists(atlasName, mapName))
			{
				HND_LOG_ERROR(std::format("Failed to load ECS instance for map {}: instance for this map is already loaded", mapName));
				return;
			}

			instances[atlasName][mapName] = std::make_unique<EcsInstance>();
			instances.at(atlasName).at(mapName)->Load(GetInstanceFilePath(atlasName, mapName));
		}
		void EcsManager::DestroyInstance(const std::string& atlasName, const std::string& mapName)
		{
			if (!InstanceExists(atlasName, mapName))
			{
				HND_LOG_ERROR(std::format("Failed to destroy ECS instance for map {}: instance does not exist", mapName));
				return;
			}

			instances.at(atlasName).at(mapName)->Destroy();
			instances.at(atlasName).erase(mapName);
		}
		std::filesystem::path EcsManager::GetInstanceFilePath(const std::string& atlasName, const std::string& mapName) const
		{
			return util::GetPathToMapSaveFile(atlasName, mapName);
		}
		EcsInstance* EcsManager::GetActiveInstance() const
		{
			return activeInstance.second.second;
		}
		bool EcsManager::InstanceExists(const std::string& atlasName, const std::string& mapName) const
		{
			return instances.contains(atlasName) && instances.at(atlasName).contains(mapName);
		}
		void EcsManager::SetActiveInstace(const std::string& atlasName, const std::string& mapName)
		{
			if (!InstanceExists(atlasName, mapName))
			{
				HND_LOG_ERROR(std::format("Failed to set ECS instance for map {} as active: instance does not exist", mapName));
				return;
			}

			activeInstance.second.second = instances.at(atlasName).at(mapName).get();
		}
		void EcsManager::UpdateActive()
		{
			if (GetActiveInstance()) GetActiveInstance()->Update();
		}
		ComponentId EcsManager::GetActiveComponentId(const std::string& compName) const
		{
			return GetActiveInstance()->ComponentGetId(compName);
		}
	}
}