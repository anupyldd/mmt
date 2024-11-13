#pragma once

namespace hnd
{
	namespace core
	{
		using ECS = ecs_t;
		using EntityId = ecs_id_t;
		using ComponentId = ecs_id_t;
		using SystemId = ecs_id_t;
		using ConstructorPtr = ecs_constructor_fn;
		using DestructorPtr = ecs_destructor_fn;
	}
}