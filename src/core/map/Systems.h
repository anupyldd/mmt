#pragma once

#include "EcsTypes.h"

/*
* creates a system function signature without a body.
* pass Name without the word "System", it's added in the macro.
* resulting names look like RenderSystem, VisibilitySystem, etc.
*/
#define DECLARE_SYSTEM_FUNCTION(Name)\
	ecs_ret_t Name##System(ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata)

// final callback name "<SystemName>AddedCallback"
#define	DECLARE_SYSTEM_ADDED_CALLBACK(Name)\
	void Name##AddedCallback(ecs_t* ecs, ecs_id_t entity_id, void* udata)

// final callback name "<SystemName>RemovedCallback"
#define	DECLARE_SYSTEM_REMOVED_CALLBACK(Name)\
	void Name##RemovedCallback(ecs_t* ecs, ecs_id_t entity_id, void* udata)

namespace hnd
{
	namespace core
	{
		DECLARE_SYSTEM_FUNCTION(Transform)
		{

		}
	}
}