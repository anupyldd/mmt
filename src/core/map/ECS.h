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

namespace hnd
{
	namespace core
	{
		// when creating a map user can select density, default - medium (5k entities)
		enum class EntityDensity { Low, Medium, High };

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

			template<class CompType>
			void RegisterComponent(const std::string& name, ConstructorPtr ctor = nullptr, DestructorPtr dtor = nullptr);
			void RemoveComponent(EntityId entity, const std::string& comp);

			void RegisterSystem(SystemId id, std::initializer_list<ComponentId> componentList = {});
			void AddRequiredSystemComponents(std::initializer_list<ComponentId> componentList);


		private:
			ECS* ecs = nullptr;

			std::unordered_map<std::string, ComponentId> components;
			std::unordered_map<std::string, SystemId> systems;
		};	

		// -----------------------------------

		template<class CompType>
		inline void EcsManager::RegisterComponent(const std::string& name, ConstructorPtr ctor, DestructorPtr dtor)
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