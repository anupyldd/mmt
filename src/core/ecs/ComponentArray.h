#pragma once 

#include <cstdint>
#include <array>
#include <unordered_map>
#include <type_traits>

#include "Types.h"
#include "../../utility/Log.h"

namespace hnd
{
	namespace core
	{
		class IComponentArray
		{
		public:
			virtual ~IComponentArray() = default;
			virtual void EntityDestroyed(Entity entity) = 0;
		};

		//---------------------------------------

		template<class T>
		class ComponentArray : public IComponentArray
		{
		public:
			void AddComponent(Entity entity, T component);
			void RemoveComponent(Entity entity);
			T& GetComponent(Entity entity);
			virtual void EntityDestroyed(Entity entity) override final;
			
		private:
			std::array<T, MAX_ENTITIES> componentArray;
			std::unordered_map<Entity, size_t> entityToIndex;
			std::unordered_map<size_t, Entity> indexToEntity;
			size_t size = 0;
		};

		//---------------------------------------

		template<class T>
		inline void ComponentArray<T>::AddComponent(Entity entity, T component)
		{
			if (entityToIndex.find(entity) == entityToIndex.end())
			{
				LOG_ERROR(std::format("Cannot add component {} twice to the same entity {}", typeid(T).name(), entity));
				return;
			}

			size_t newIndex = size;
			entityToIndex.at(entity) = newIndex;
			indexToEntity.at(newIndex) = entity;
			componentArray.at(newIndex) = component;
			++size;
		}
		template<class T>
		inline void ComponentArray<T>::RemoveComponent(Entity entity)
		{
			if (entityToIndex.find(entity) == entityToIndex.end())
			{
				LOG_ERROR(std::format("Cannot remove non-existent component {} from entity {}", typeid(T).name(), entity));
				return;
			}

			size_t indexOfRemovedEntity = entityToIndex.at(entity);
			size_t indexOfLastElement = size - 1;
			componentArray.at(indexOfRemovedEntity) = componentArray.at(indexOfLastElement);

			// Update map to point to moved spot
			Entity entityOfLastElement = indexToEntity.at(indexOfLastElement);
			entityToIndex.at(entityOfLastElement) = indexOfRemovedEntity;
			indexToEntity.at(indexOfRemovedEntity) = entityOfLastElement;

			entityToIndex.erase(entity);
			indexToEntity.erase(indexOfLastElement);

			--size;
		}
		template<class T>
		inline T& ComponentArray<T>::GetComponent(Entity entity)
		{
			return componentArray.at(entityToIndex.at(entity));
		}
		template<class T>
		inline void ComponentArray<T>::EntityDestroyed(Entity entity)
		{
			if (entityToIndex.find(entity) != entityToIndex.end())
				RemoveComponent(entity);
		}
	}
}