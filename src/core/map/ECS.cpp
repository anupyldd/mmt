#define PICO_ECS_MAX_COMPONENTS 32
#define PICO_ECS_MAX_SYSTEMS 16

#define PICO_ECS_IMPLEMENTATION

#include "ECS.h"

namespace hnd
{
	namespace core
	{
		void EcsManager::Init(EntityDensity mapSize)
		{
			switch (mapSize)
			{
			case EntityDensity::Small:
				ecs = ecs_new(MAX_ENTITY_COUNT_LOW_DENSITY, NULL);
				break;
			case EntityDensity::Medium:
				ecs = ecs_new(MAX_ENTITY_COUNT_MEDIUM_DENSITY, NULL);
				break;
			case EntityDensity::Large:
				ecs = ecs_new(MAX_ENTITY_COUNT_HIGH_DENSITY, NULL);
				break;
			default: 
				ecs = ecs_new(MAX_ENTITY_COUNT_MEDIUM_DENSITY, NULL);
				break;
			}

			RegisterCommon();
		}
		EntityId EcsManager::CreateEntity()
		{
			return ecs_create(ecs);
		}
		EntityId EcsManager::CreateSetEntity(std::initializer_list<ComponentId> componentIds)
		{
			EntityId id = ecs_create(ecs);
			for (const auto comp : componentIds)
			{
				if (std::ranges::find(components, comp) != components.end())
				{
					ecs_add(ecs, id, comp, NULL);
				}
				else
				{
					LOG_ERROR(std::format("Failed to assign component {} to entity {}: component is not registered", comp, id));
				}
			}
		}
	}
}