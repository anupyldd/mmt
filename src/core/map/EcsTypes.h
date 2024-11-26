#pragma once

#include "pico/pico_ecs.h"

namespace mmt
{
	namespace core
	{
		using Ecs = ecs_t;
		using EntityId = ecs_id_t;
		using ComponentId = ecs_id_t;
		using SystemId = ecs_id_t;
		using ConstructorPtr = ecs_constructor_fn;
		using DestructorPtr = ecs_destructor_fn;
		using ReturnCode = ecs_ret_t;
		using SystemFuncPtr = ecs_system_fn;
		using SystemAddCallbackPtr = ecs_added_fn;
		using SystemRemoveCallbackPtr = ecs_removed_fn;
	}
}