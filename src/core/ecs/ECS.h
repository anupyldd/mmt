#pragma once

#include <cstdint>
#include <bitset>
#include <queue>
#include <array>
#include <exception>

#include "../../utility/Log.h"

namespace hnd
{
	namespace core
	{
		using Entity = uint32_t;
		constexpr Entity MAX_ENTITIES = 5000;
		
		using ComponentType = uint8_t;
		constexpr ComponentType MAX_COMPONENTS = 32;

		using Signature = std::bitset<MAX_COMPONENTS>;
		constexpr Signature emptySignature;

		//------------------------

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