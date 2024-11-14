#include "EcsManager.h"

namespace hnd
{
	namespace core
	{
		void EcsManager::CreateInstance(const std::string& mapName, int maxEntityCount)
		{
			if (instances.contains(mapName))
			{
				LOG_ERROR(std::format("Failed to create ECS instance for map {}: instance for this map already exists", mapName));
				return;
			}

			instances[mapName] = std::make_unique<EcsInstance>();
			instances.at(mapName)->Init(maxEntityCount);
		}
		void EcsManager::LoadInstace(const std::string& mapName)
		{
			if (instances.contains(mapName))
			{
				LOG_ERROR(std::format("Failed to load ECS instance for map {}: instance for this map is already loaded", mapName));
				return;
			}

			instances[mapName] = std::make_unique<EcsInstance>();
			instances.at(mapName)->Load(GetInstanceFilePath(mapName));
		}
		void EcsManager::DestroyInstance(const std::string& mapName)
		{
			if (!instances.contains(mapName))
			{
				LOG_ERROR(std::format("Failed to destroy ECS instance for map {}: instance does not exist", mapName));
				return;
			}

			instances.at(mapName)->Destroy();
			instances.erase(mapName);
		}
		std::filesystem::path EcsManager::GetInstanceFilePath(const std::string& mapName) const
		{
			LOG_DBG("TODO: GetInstanceFilePath()");
			return std::filesystem::path();
		}
		void EcsManager::SetActiveInstace(const std::string& mapName)
		{
			if (!instances.contains(mapName))
			{
				LOG_ERROR(std::format("Failed to set ECS instance for map {} as active: instance does not exist", mapName));
				return;
			}

			activeInstance = instances.at(mapName).get();
		}
		void EcsManager::UpdateActive()
		{
			if (activeInstance) activeInstance->Update();
		}
	}
}