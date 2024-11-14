#pragma once

#include "EcsTypes.h"
#include "Components.h"
#include "Ecs.h"
#include "../../utility/Log.h"

#include "raylib.h"

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
		using namespace components;
		using namespace ecs_wrapper;

		/*
		* required: sprite, transform, visibility
		* excluded:
		*/
		DECLARE_SYSTEM_FUNCTION(RenderSprite)
		{
			for (size_t i = 0; i < entity_count; i++)
			{
				/*
				* problem: component id can differ between ecs instances
				* there' no way to know it before registering
				* systems need to somehow get the id
				* so i guess there has to be some manager that manages insatnces of ecs
				* and it'll retrieve the id of the component in the currently active ecs
				*/

				//Transform* transform = EntityGetComponent<Transform>(ecs,entities[i],)
			}
		}
	}
}