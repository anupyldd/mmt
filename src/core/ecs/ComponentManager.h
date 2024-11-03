#pragma once

#include "Types.h"
#include "ComponentArray.h"

#include <memory>
#include <unordered_map>
#include <type_traits>
#include <exception>

namespace hnd
{
	namespace core
	{
		class ComponentManager
		{
		public:
			template<class T> void RegisterComponent();
			template<class T> ComponentType GetComponentType();

			template<class T> void AddComponent(Entity entity, T component);
			template<class T> void RemoveComponent(Entity entity);
			template<class T> T& GetComponent(Entity entity);
			
			void EntityDestroyed(Entity entity);

		private:
			template<class T>
			std::shared_ptr<ComponentArray<T>> GetComponentArray();

		private:
			std::unordered_map<const char*, ComponentType> componentTypes;
			std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays;
			ComponentType nextComponentType = 0;
		};

		//------------------------

		template<class T>
		inline void ComponentManager::RegisterComponent()
		{
			const char* typeName = typeid(T).name();
			if (componentTypes.find(typeName) == componentTypes.end())
			{
				LOG_ERROR(std::format("Cannot register component {} more than once", typeName));
				return;
			}

			componentTypes.insert({ typeName, nextComponentType });
			componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
			++nextComponentType;
		}

		template<class T>
		inline ComponentType ComponentManager::GetComponentType()
		{
			const char* typeName = typeid(T).name();
			if (componentTypes.find(typeName) == componentTypes.end())
				throw std::runtime_error(std::format("Component {} is not registered", typeName));

			return componentTypes.at(typeName);
		}

		template<class T>
		inline void ComponentManager::AddComponent(Entity entity, T component)
		{
			GetComponentArray<T>()->AddComponent(entity, component);
		}

		template<class T>
		inline void ComponentManager::RemoveComponent(Entity entity)
		{
			GetComponentArray<T>()->RemoveComponent(entity);
		}

		template<class T>
		inline T& ComponentManager::GetComponent(Entity entity)
		{
			return GetComponentArray<T>()->GetComponent(entity);
		}

		inline void ComponentManager::EntityDestroyed(Entity entity)
		{
			for (auto const& pair : componentArrays)
			{
				auto const& component = pair.second;
				component->EntityDestroyed(entity);
			}
		}

		template<class T>
		inline std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
		{
			const char* typeName = typeid(T).name();
			if (componentTypes.find(typeName) == componentTypes.end())
			{
				LOG_ERROR(std::format("Component {} not registered", typeName));
				return nullptr;
			}

			return std::static_pointer_cast<ComponentArray<T>>(componentArrays.at(typeName));
		}
	}
}