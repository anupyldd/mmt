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
			auto& conf = Config::GetInstance().map;

			switch (mapSize)
			{
			case EntityDensity::Low:
				ecs = ecs_new(conf->maxEntityNumberLow, NULL);
				break;
			case EntityDensity::Medium:
				ecs = ecs_new(conf->maxEntityNumberMedium, NULL);
				break;
			case EntityDensity::High:
				ecs = ecs_new(conf->maxEntityNumberHigh, NULL);
				break;
			default: 
				ecs = ecs_new(conf->maxEntityNumberMedium, NULL);
				break;
			}

			RegisterCommon();
		}
		EcsManager::~EcsManager()
		{
			ecs_free(ecs);
		}
		void EcsManager::Reset()
		{
			ecs_reset(ecs);
		}
		void EcsManager::RegisterCommon()
		{
		}
		EntityId EcsManager::EntityCreate()
		{
			return ecs_create(ecs);
		}
		EntityId EcsManager::EntityCreateSet(std::initializer_list<std::string_view> comps)
		{
			EntityId id = ecs_create(ecs);

			for (auto& c : comps)
			{
				try
				{
					ecs_add(ecs, id, components.at(std::string(c)), nullptr);
				}
				catch (const std::exception& e)
				{
					LOG_ERROR(std::format("Failed to add component {} to entity {}: {}",
						c, id, e.what()));
				}
			}

			return id;
		}
		void EcsManager::EntityAddComponents(EntityId entity, std::initializer_list<std::string_view> comps)
		{
			for (auto& c : comps)
			{
				try
				{
					ecs_add(ecs, entity, components.at(std::string(c)), nullptr);
				}
				catch (const std::exception& e)
				{
					LOG_ERROR(std::format("Failed to add component {} to entity {}: {}",
						c, entity, e.what()));
				}
			}
		}
		void EcsManager::EntityDestroy(EntityId entity)
		{
			ecs_destroy(ecs, entity);
		}
		void EcsManager::EntityQueueDestroy(EntityId entity)
		{
			ecs_queue_destroy(ecs, entity);
		}
		bool EcsManager::EntityIsReady(EntityId entity) const
		{
			return ecs_is_ready(ecs, entity);
		}
		bool EcsManager::EntityHasComponent(EntityId entity, const std::string& comp) const
		{
			return ecs_has(ecs, entity, components.at(comp));
		}
		void EcsManager::EntityComponentsRemove(EntityId entity, std::initializer_list<std::string_view> comps)
		{
			for (auto& c : comps)
			{
				try
				{
					ecs_remove(ecs, entity, components.at(std::string(c)));
				}
				catch (const std::exception& e)
				{
					LOG_ERROR(std::format("Failed to remove component {} from entity {}: {}",
						c, entity, e.what()));
				}
			}
		}
		void EcsManager::EntityQueueComponentRemove(EntityId entity, const std::string& comp)
		{
			ecs_queue_remove(ecs, entity, components.at(comp));
		}
		void EcsManager::SystemRegister(
			const std::string& name,
			SystemFuncPtr func,
			std::initializer_list<std::string_view> requireComps,
			std::initializer_list<std::string_view> excludeComps, 
			SystemAddCallbackPtr addCb, 
			SystemRemoveCallbackPtr removeCb, 
			void* cbData)
		{
			if (systems.contains(name))
			{
				LOG_ERROR(std::format("Cannot register system {}: this name is already taken", name));
				return;
			}

			SystemId id = ecs_register_system(ecs, func, addCb, removeCb, cbData);
			systems[name] = id;

			for (auto& c : requireComps)
			{
				ecs_require_component(ecs, id, components.at(std::string(c)));
			}
			for (auto& c : excludeComps)
			{
				ecs_exclude_component(ecs, id, components.at(std::string(c)));
			}
		}
		/*
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
			return id;
		}
		*/
	}
}