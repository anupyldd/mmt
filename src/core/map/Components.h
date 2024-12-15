#pragma once

#include <string>
#include <type_traits>
#include <format>
#include <typeinfo>
#include <tuple>
#include <chrono>
#include <vector>

#define PICO_ECS_CPP_SHORTHAND_MACROS

#include "json/picojson.h"
#include "ecs/PicoEcsCpp.h"
#include "raylib.h"

#include "../../utility/StringUtil.h"
#include "../../utility/Defines.h"
#include "../../utility/Serialization.h"

namespace mmt
{
	namespace core
	{
		// ecs components
		namespace comps
		{
			struct Transform
			{
				float x = 0.0f, y = 0.0f; // coord
				float s = 1.0f;	// scale
				float a = 0.0f;	// angle
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Transform);

			struct Object
			{
				uint32_t h = 0; // handle
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Object);

			struct Active
			{
			};

			struct NotVisible
			{
			};

			struct Texture // from file
			{
				uint32_t h = 0; // handle
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Texture);

			struct Canvas // texture to draw on
			{
				uint32_t h = 0; // handle
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Canvas);

			struct Name
			{
				std::string n;	// name
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Name);

			struct Description
			{
				std::string d;	// description
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Description);

			struct Nodes
			{
				std::vector<Vector2> n;	// nodes
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Nodes);

			struct Layer
			{
				int l;	// layer
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Layer);

			struct Brush
			{
				uint32_t h = 0;	// handle
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Brush);

			struct Script
			{
				uint32_t h = 0;	// handle
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Script);

			struct Serializeable
			{
			};

			struct Text
			{
				std::string t; // text
				uint32_t f = 0; // font
			};
			PICO_ECS_CPP_COMPONENT_CONSTRUCTOR_COPY(Text);
		}
	}
}