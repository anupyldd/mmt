#pragma once

#include <memory>

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace hnd
{
	namespace core
	{
		class EcsManager
		{
		public:
			EcsManager() = default;

			void Init();

			Entity CreateEntity();
			void DestroyEntity(Entity entity);

			template<class T> void RegisterComponent();
			template<class T> void AddComponent(Entity entity, T component);
			template<class T> void RemoveComponent(Entity entity);
			template<class T> T& GetComponent(Entity entity);
			template<class T> T& GetComponentType();

			template<class T> std::shared_ptr<T> RegisterSystem();
			template<class T> void SetSystemSignature(Signature signature);

		private:
			std::unique_ptr<EntityManager> entityManager;
			std::unique_ptr<ComponentManager> componentManager;
			std::unique_ptr<SystemManager> systemManager;
		};

		//----------------------------------

		inline void EcsManager::Init()
		{
			componentManager = std::make_unique<ComponentManager>();
			entityManager = std::make_unique<EntityManager>();
			systemManager = std::make_unique<SystemManager>();
		}
		inline Entity EcsManager::CreateEntity()
		{
			return entityManager->CreateEntity();
		}
		inline void EcsManager::DestroyEntity(Entity entity)
		{
			entityManager->DestroyEntity(entity);
			componentManager->EntityDestroyed(entity);
			systemManager->EntityDestroyed(entity);
		}
		template<class T>
		inline void EcsManager::RegisterComponent()
		{
			componentManager->RegisterComponent<T>();
		}
		template<class T>
		inline void EcsManager::AddComponent(Entity entity, T component)
		{
			componentManager->AddComponent<T>(entity, component);

			auto signature = entityManager->GetSignature(entity);
			signature.set(componentManager->GetComponentType<T>(), true);
			entityManager->SetSignature(entity, signature);

			systemManager->EntitySignatureChanged(entity, signature);
		}
		template<class T>
		inline void EcsManager::RemoveComponent(Entity entity)
		{
			componentManager->RemoveComponent<T>(entity);

			auto signature = entityManager->GetSignature(entity);
			signature.set(componentManager->GetComponentType<T>(), false);
			entityManager->SetSignature(entity, signature);

			systemManager->EntitySignatureChanged(entity, signature);
		}
		template<class T>
		inline T& EcsManager::GetComponent(Entity entity)
		{
			return componentManager->GetComponent<T>(entity);
		}
		template<class T>
		inline T& EcsManager::GetComponentType()
		{
			return componentManager->GetComponentType<T>();
		}
		template<class T>
		inline std::shared_ptr<T> EcsManager::RegisterSystem()
		{
			return systemManager->RegisterSystem<T>();
		}
		template<class T>
		inline void EcsManager::SetSystemSignature(Signature signature)
		{
			systemManager->SetSignature<T>(signature);
		}
	}
}