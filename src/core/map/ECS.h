#pragma once

#include <memory>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <exception>
#include <utility>

#include "pico/pico_ecs.h"

#include "../../utility/Log.h"

namespace hnd
{
	namespace core
	{
		using ECS			= ecs_t;
		using EntityId		= ecs_id_t;
		using ComponentId	= ecs_id_t;
		using SystemId		= ecs_id_t;

		// when creating a map user can select density, default - medium (5k entities)
		enum class EntityDensity { Small, Medium, Large };

		constexpr int MAX_ENTITY_COUNT_LOW_DENSITY		= 2000;
		constexpr int MAX_ENTITY_COUNT_MEDIUM_DENSITY	= 5000;	
		constexpr int MAX_ENTITY_COUNT_HIGH_DENSITY		= 10000;

		class EcsManager
		{
		public:
			void Init(EntityDensity mapSize);
			
			void RegisterCommon();

			// updates all systems
			void Update();

			// creates empty entity
			EntityId CreateEntity();

			// creates and adds default-initialized components
			EntityId CreateSetEntity(std::initializer_list<ComponentId> componentIds);
			
			/// creates and adds initialized components. LIST OF COMPONENT OBJECTS MUST BE IN THE SAME ORDER AS IN THE LIST OF IDS
			template<class... Comps>
			EntityId CreateSetEntity(std::pair<ComponentId, Comps>... components);

			void DestroyEntity(EntityId entity);

			void AddComponent(EntityId entity, ComponentId component);

			void RegisterComponent(ComponentId id);
			void RemoveComponent(EntityId entity);

			void RegisterSystem(SystemId id, std::initializer_list<ComponentId> componentList = {});
			void AddRequiredSystemComponents(std::initializer_list<ComponentId> componentList);


		private:
			ECS* ecs = nullptr;

			std::vector<ComponentId> components;
			std::vector<SystemId> systems;
		};

		// -----------------------------------

	}
}