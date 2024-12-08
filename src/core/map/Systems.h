#pragma once

#ifndef PICO_ECS_CPP_SHORTHAND_MACROS
#define PICO_ECS_CPP_SHORTHAND_MACROS
#endif

#include "Components.h"
#include "../ResourceManager.h"
#include "../../utility/Log.h"

#include "raylib.h"
#include "ecs/PicoEcsCpp.h"


namespace mmt
{
	namespace core
	{
		using namespace pico_ecs_cpp;
		using namespace comps;

		/*
		* requires: Serializeable
		* excludes: none
		* 
		* serializes every entity with Serializeable component
		* not included into save file: Serializeable, Active, Culled
		*/
		PICO_ECS_CPP_SYSTEM_FUNCTION(SerializationSystem);

	}
}