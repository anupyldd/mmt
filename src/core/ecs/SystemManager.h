#pragma once

#include <memory>
#include <unordered_map>

#include "Types.h"
#include "System.h"

namespace hnd
{
	namespace core
	{
		class SystemManager
		{
		public:
			template<class T> std::shared_ptr<T> RegisterSystem();
			template<class T> void SetSignature(Signature signature);
			
			void EntityDestroyed(Entity entity);
			void EntitySignatureChanged(Entity entity, Signature signature);

		private:
			std::unordered_map<const char*, Signature> signatures;
			std::unordered_map<const char*, std::shared_ptr<System>> systems;
		};

		//-------------------------------------

		template<class T>
		inline std::shared_ptr<T> SystemManager::RegisterSystem()
		{
			const char* typeName = typeid(T).name();
			if (systems.find(typeName) != systems.end())
			{
				LOG_ERROR(std::format("Cannot register system {} more than once", typeName));
				return nullptr;
			}

			auto system = std::make_shared<T>();
			systems.insert({ typeName, system });
			return system;
		}
		template<class T>
		inline void SystemManager::SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();
			if (systems.find(typeName) == systems.end())
			{
				LOG_ERROR(std::format("System {} is not registered", typeName));
				return;
			}

			signatures.insert({ typeName, signature });
		}
		inline void SystemManager::EntityDestroyed(Entity entity)
		{
			for (const auto& pair : systems)
			{
				const auto& system = pair.second;
				system->entities.erase(entity);
			}
		}
		inline void SystemManager::EntitySignatureChanged(Entity entity, Signature signature)
		{
			for (auto const& pair : systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = signatures.at(type);

				if ((signature & systemSignature) == systemSignature)
				{
					system->entities.insert(entity);
				}
				else
				{
					system->entities.erase(entity);
				}
			}
		}
	}
}