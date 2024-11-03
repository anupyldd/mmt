#include "EntityManager.h"

namespace hnd
{
	namespace core
	{
		EntityManager::EntityManager()
		{
			for (Entity ent = 0; ent < MAX_ENTITIES; ++ent)
			{
				availableEntities.push(ent);
			}
		}
		Entity EntityManager::CreateEntity()
		{
			if (livingEntityCount >= MAX_ENTITIES)
				throw std::runtime_error(std::format("Too many entities. Max: {}", MAX_ENTITIES));

			Entity id = availableEntities.front();
			availableEntities.pop();
			return id;
		}
		void EntityManager::DestroyEntity(Entity entity)
		{
			if (entity >= MAX_ENTITIES)
				LOG_ERROR(std::format("Unable to remove entity {}, entity out of range", entity));

			signatures[entity].reset();
			availableEntities.push(entity);
			--livingEntityCount;
		}
		void EntityManager::SetSignature(Entity entity, Signature signature)
		{
			if (entity >= MAX_ENTITIES)
				LOG_ERROR(std::format("Unable to set signature for entity {}, entity out of range", entity));

			signatures[entity] = signature;
		}
		Signature EntityManager::GetSignature(Entity entity)
		{
			if (livingEntityCount >= MAX_ENTITIES)
			{
				LOG_ERROR(std::format("Unable to access signature of entity {}, entity out of range", entity));
				return emptySignature;
			}

			return signatures[entity];
		}
	}
}