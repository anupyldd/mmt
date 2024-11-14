#pragma once

#include "EcsInstance.h"

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <filesystem>

namespace hnd
{
	namespace core
	{
		/*
		* manages ecs instances.
		* each instance is associated with 1 map, 1 map can have only 1 instance.
		* instances are loaded/saved/etc by map name
		*/
		class EcsManager
		{
		public:
			// creates default instance
			void CreateInstance(const std::string& mapName, int maxEntityCount);

			// loads previously saved instance from file by id
			void LoadInstace(const std::string& mapName);

			void DestroyInstance(const std::string& mapName);

			void SetActiveInstace(const std::string& mapName);

			void UpdateActive();

		private:
			std::filesystem::path GetInstanceFilePath(const std::string& mapName) const;

		private:
			std::unordered_map<std::string, std::unique_ptr<EcsInstance>> instances;
			EcsInstance* activeInstance = nullptr;
		};
	}
}