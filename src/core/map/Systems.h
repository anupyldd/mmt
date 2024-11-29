#pragma once

#include "EcsTypes.h"
#include "Components.h"
#include "Ecs.h"
//#include "EcsManager.h"
#include "../ResourceManager.h"
#include "../../utility/Log.h"

#include "raylib.h"

/*
* creates a system function signature without a body.
* pass Name without the word "System", it's added in the macro.
* resulting names look like RenderSystem, VisibilitySystem, etc.
*/
#define MMT_SYSTEM_FUNCTION(Name)\
	inline ecs_ret_t Name##System(ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata)

// final callback name "<SystemName>AddedCallback"
#define	MMT_SYSTEM_ADDED_CALLBACK(Name)\
	inline void Name##AddedCallback(ecs_t* ecs, ecs_id_t entity_id, void* udata)

// final callback name "<SystemName>RemovedCallback"
#define	MMT_SYSTEM_REMOVED_CALLBACK(Name)\
	inline void Name##RemovedCallback(ecs_t* ecs, ecs_id_t entity_id, void* udata)

// to be used in a loop of a system, gets the ptr to comp
#define MMT_GET_ENTITY_COMPONENT_PTR(CompType)  \
	EntityGetComponent<CompType>(ecs, entities[i], CompType##Id);

namespace mmt
{
	namespace core
	{
		using namespace components;
		using namespace ecs_wrapper;

		/*
		* required: sprite, transform
		* excluded: culled
		*/
		MMT_SYSTEM_FUNCTION(RenderSprite)
		{
			for (size_t i = 0; i < entity_count; i++)
			{
				
				Transform* transform = MMT_GET_ENTITY_COMPONENT_PTR(Transform);
				Sprite* sprite = MMT_GET_ENTITY_COMPONENT_PTR(Sprite);
				//DrawCircle(transform->x, transform->y, 5, RED);
			}
		}
		

	}
}