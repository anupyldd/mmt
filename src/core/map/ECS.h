#pragma once

#include <memory>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <exception>
#include <unordered_map>
#include <utility>
#include <string_view>

#include "pico/pico_ecs.h"

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
			
			void RegisterCommon();

			// updates all systems
			void Update();

		public:	// ENTITIES

			// creates empty entity
			EntityId EntityCreate();

			// creates and adds default-initialized components
			EntityId EntityCreateSet(std::initializer_list<std::string_view> componentIds);
			
			/// creates and adds initialized components
			template<class... Comps>
			EntityId EntityCreateSet(std::pair<ComponentId, Comps>... components);
			
			void EntityAddComponent(EntityId entity, const std::string& comp);

			void EntityDestroy(EntityId entity);
			
			// Queues an entity for destruction at the end of system execution
			void EntityQueueDestroy(EntityId entity);

			bool EntityIsReady(EntityId entity) const;
			
			bool EntityHasComponent(EntityId entity, const std::string& comp) const;
			
			ComponentBase* EntityGetComponent(EntityId entity, const std::string& comp);
			
			void EntityComponentsRemove(EntityId entity, std::initializer_list<std::string_view> comps);

			void EntityQueueComponentRemove(EntityId entity, const std::string& comp);

		public: // COMPONENTS

			template<class CompType>
			void ComponentRegister(const std::string& name, ConstructorPtr ctor = nullptr, DestructorPtr dtor = nullptr);

		public:	// SYSTEMS

			void SystemRegister(SystemId id, std::initializer_list<ComponentId> componentList = {});
			void SystemRequireComponents(std::initializer_list<ComponentId> componentList);
			void SystemExcludeComponent(std::initializer_list<ComponentId> componentList);

		private:
			ECS* ecs = nullptr;

			std::unordered_map<std::string, ComponentId> components;
			std::unordered_map<std::string, SystemId> systems;
		};	

		// -----------------------------------

		template<class CompType>
		inline void EcsManager::ComponentRegister(const std::string& name, ConstructorPtr ctor, DestructorPtr dtor)
		{
			if (components.contains(name))
			{
				LOG_ERROR(std::format("Cannot register component {} (id {}): this name is already taken", name, id));
				return;
			}

			components[name] = ecs_register_component(ecs, sizeof(CompType), ctor, dtor);
		}

	}
}