#pragma once

// pico_ecs wrapper

#include <memory>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <exception>
#include <unordered_map>
#include <utility>
#include <string>
#include <string_view>

#include "EcsTypes.h"
#include "../../utility/Log.h"

namespace hnd
{
	namespace core
	{
		namespace ecs_wrapper
		{

			inline EntityId EntityCreate(Ecs* ecs)
			{
				return ecs_create(ecs);
			}

			inline EntityId EntityCreateSet(Ecs* ecs, std::initializer_list<ComponentId> comps)
			{
				EntityId id = ecs_create(ecs);

				for (auto& c : comps)
				{
					try
					{
						ecs_add(ecs, id, c, nullptr);
					}
					catch (const std::exception& e)
					{
						HND_LOG_ERROR(std::format("Failed to add component {} to entity {}: {}",
							c, id, e.what()));
					}
				}
			}

			/// creates and adds initialized components
			template<class... Comps>
			inline EntityId EntityCreateSet(Ecs* ecs, std::pair<ComponentId, Comps>... comps)
			{
				EntityId id = ecs_create(ecs);

				([&]
					{
						ecs_add(ecs, id, comps.first, &comps.second);
					}
				(), ...);

				return id;
			}

			// adds default-initialized components
			inline void EntityAddComponents(Ecs* ecs, EntityId entity, std::initializer_list<ComponentId> comps)
			{
				for (auto& c : comps)
				{
					try
					{
						ecs_add(ecs, entity, c, nullptr);
					}
					catch (const std::exception& e)
					{
						HND_LOG_ERROR(std::format("Failed to add component {} to entity {}: {}",
							c, entity, e.what()));
					}
				}
			}

			// adds initialized components
			template<class... Comps>
			inline void EntityAddComponents(Ecs* ecs, EntityId entity, std::pair<const char*, Comps>... comps)
			{
				([&]
					{
						ecs_add(ecs, entity, components.at(comps.first), &comps.second);
					}
				(), ...);
			}

			inline void EntityDestroy(Ecs* ecs, EntityId entity)
			{
				ecs_destroy(ecs, entity);
			}

			// queues an entity for destruction at the end of system execution
			inline void EntityQueueDestroy(Ecs* ecs, EntityId entity)
			{
				ecs_queue_destroy(ecs, entity);
			}

			inline bool EntityIsReady(Ecs* ecs, EntityId entity)
			{
				return ecs_is_ready(ecs, entity);
			}

			inline bool EntityHasComponent(Ecs* ecs, EntityId entity, ComponentId comp)
			{
				return ecs_has(ecs, entity, comp);
			}

			// Comp and comp should be the same, like Transform and "Transform"
			template<class CompType>
			inline CompType* EntityGetComponent(Ecs* ecs, EntityId entity, ComponentId comp)
			{
				return dynamic_cast<CompType>(ecs_get(ecs, entity, comp));
			}

			inline void EntityComponentsRemove(Ecs* ecs, EntityId entity, std::initializer_list<ComponentId> comps)
			{
				for (auto& c : comps)
				{
					try
					{
						ecs_remove(ecs, entity, c);
					}
					catch (const std::exception& e)
					{
						HND_LOG_ERROR(std::format("Failed to remove component {} from entity {}: {}",
							c, entity, e.what()));
					}
				}
			}

			inline void EntityQueueComponentRemove(Ecs* ecs, EntityId entity, ComponentId comp)
			{
				ecs_queue_remove(ecs, entity, comp);
			}
		}
	}
}