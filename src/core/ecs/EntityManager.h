#pragma once

#include <cstdint>
#include <bitset>
#include <queue>
#include <array>
#include <exception>

#include "../../utility/Log.h"
#include "Types.h"

namespace hnd
{
	namespace core
	{
		class EntityManager
		{
		public:
			EntityManager();
			
			Entity CreateEntity();
			void DestroyEntity(Entity entity);
			void SetSignature(Entity entity, Signature signature);
			Signature GetSignature(Entity entity);

		private:
			std::queue<Entity> availableEntities;
			std::array<Signature, MAX_ENTITIES> signatures;
			uint32_t livingEntityCount = 0;
		};
	}
}