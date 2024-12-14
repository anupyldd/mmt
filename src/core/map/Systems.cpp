#ifndef PICO_ECS_IMPLEMENTATION
#define PICO_ECS_IMPLEMENTATION
#endif 

#include "Systems.h"

#include "log/loguru.hpp"

namespace mmt
{
	namespace core
	{
		using namespace comps;
		using namespace pico_ecs_cpp;

		PICO_ECS_CPP_SYSTEM_FUNCTION(SerializationSystem)
		{
			EcsInstance* inst = static_cast<EcsInstance*>(udata);
			if (inst)
			{
				for (int i = 0; i < entity_count; ++i)
				{
					DLOG_F(INFO, "Serializing entity %i", entities[i]);
				}
				return 0;
			}
			return 1;
		}
	}
}