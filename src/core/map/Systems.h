#pragma once

#include "EcsTypes.h"
#include "Components.h"
#include "Ecs.h"
#include "EcsManager.h"
#include "../ResourceManager.h"
#include "../../utility/Log.h"

#include "raylib.h"

/*
* creates a system function signature without a body.
* pass Name without the word "System", it's added in the macro.
* resulting names look like RenderSystem, VisibilitySystem, etc.
*/
#define MMT_DECLARE_SYSTEM_FUNCTION(Name)\
	ecs_ret_t Name##System(ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata)

// final callback name "<SystemName>AddedCallback"
#define	MMT_DECLARE_SYSTEM_ADDED_CALLBACK(Name)\
	void Name##AddedCallback(ecs_t* ecs, ecs_id_t entity_id, void* udata)

// final callback name "<SystemName>RemovedCallback"
#define	MMT_DECLARE_SYSTEM_REMOVED_CALLBACK(Name)\
	void Name##RemovedCallback(ecs_t* ecs, ecs_id_t entity_id, void* udata)

// to be used in a loop of a system, gets the ptr to comp
#define MMT_GET_ENTITY_COMPONENT_PTR(CompType)  \
	EntityGetComponent<CompType>(ecs, entities[i], EcsManager::GetInstance().GetActiveComponentId(#CompType));

namespace mmt
{
	namespace core
	{
		using namespace components;
		using namespace ecs_wrapper;
		class EcsManager;
		/*
		* required: sprite, transform
		* excluded: culled
		MMT_DECLARE_SYSTEM_FUNCTION(RenderSprite)
		{
			for (size_t i = 0; i < entity_count; i++)
			{
				
				Transform* transform = MMT_GET_ENTITY_COMPONENT_PTR(Transform);
				Sprite* sprite = MMT_GET_ENTITY_COMPONENT_PTR(Sprite);
				// not getting visible since it's just a marker
				DrawCircle(transform->x, transform->y, 5, RED);
			}
		}
		*/

	}
}