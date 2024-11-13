#pragma once

#include <memory>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <exception>
#include <unordered_map>
#include <utility>
#include <string_view>

#include "../../utility/Log.h"
#include "../Config.h"
#include "EcsTypes.h"
#include "Components.h"

namespace hnd
{
	namespace core
	{
		using namespace components;

		// when creating a map user can select density, default - medium (5k entities)
		enum class EntityDensity { Low, Medium, High };

		class EcsManager
		{
		public:
			void Init(EntityDensity mapSize);

			~EcsManager();
			
			// removes all entities from the ECS, preserving systems and components.
			void Reset();

			void RegisterCommon();

			// updates all systems
			void Update();

		public:	// ENTITIES

			// creates empty entity
			EntityId EntityCreate();

			// creates and adds default-initialized components
			EntityId EntityCreateSet(std::initializer_list<std::string_view> comps);
			
			/// creates and adds initialized components
			template<class... Comps>
			EntityId EntityCreateSet(std::pair<const char*, Comps>... comps);
			
			// adds default-initialized components
			void EntityAddComponents(EntityId entity, std::initializer_list<std::string_view> comps);

			// adds initialized components
			template<class... Comps>
			void EntityAddComponents(EntityId entity, std::pair<const char*, Comps>... comps);

			void EntityDestroy(EntityId entity);
			
			// queues an entity for destruction at the end of system execution
			void EntityQueueDestroy(EntityId entity);

			bool EntityIsReady(EntityId entity) const;
			
			bool EntityHasComponent(EntityId entity, const std::string& comp) const;
			
			// Comp and comp should be the same, like Transform and "Transform"
			template<class CompType>
			CompType* EntityGetComponent(EntityId entity, const std::string& comp);
			
			void EntityComponentsRemove(EntityId entity, std::initializer_list<std::string_view> comps);

			void EntityQueueComponentRemove(EntityId entity, const std::string& comp);

		public: // COMPONENTS

			template<class CompType>
			void ComponentRegister(const std::string& name, ConstructorPtr ctor = nullptr, DestructorPtr dtor = nullptr);

		public:	// SYSTEMS

			void SystemRegister(
				const std::string& name, 
				SystemFuncPtr func,
				std::initializer_list<std::string_view> requireComps = {},
				std::initializer_list<std::string_view> excludeComps = {},
				SystemAddCallbackPtr addCb = nullptr, 
				SystemRemoveCallbackPtr removeCb = nullptr,
				void* cbData = nullptr);
			void SystemRequireComponents(const std::string& name, std::initializer_list<std::string_view> comps);
			void SystemExcludeComponent(const std::string& name, std::initializer_list<std::string_view> comps);

		private:
			ECS* ecs = nullptr;

			std::unordered_map<std::string, ComponentId> components;
			std::unordered_map<std::string, SystemId> systems;
		};	

		// -------------------------------------------------------------------
		// -------------------------------------------------------------------
		// -------------------------------------------------------------------

		template<class ...Comps>
		inline EntityId EcsManager::EntityCreateSet(std::pair<const char*, Comps> ...comps)
		{
			EntityId id = ecs_create(ecs);

			([&]
				{
					ecs_add(ecs, id, components.at(comps.first), &comps.second);
				}
			(), ...);

			return id;
		}

		template<class ...Comps>
		inline void EcsManager::EntityAddComponents(EntityId entity, std::pair<const char*, Comps>... comps)
		{
			([&]
				{
					ecs_add(ecs, entity, components.at(comps.first), &comps.second);
				}
			(), ...);
		}

		template<class CompType>
		inline CompType* EcsManager::EntityGetComponent(EntityId entity, const std::string& comp)
		{
			return dynamic_cast<CompType>(ecs_get(ecs, entity, components.at(comp)));
		}

		template<class CompType>
		inline void EcsManager::ComponentRegister(const std::string& name, ConstructorPtr ctor, DestructorPtr dtor)
		{
			if (components.contains(name))
			{
				LOG_ERROR(std::format("Cannot register component {}: this name is already taken", name));
				return;
			}

			components[name] = ecs_register_component(ecs, sizeof(CompType), ctor, dtor);
		}

	}
}