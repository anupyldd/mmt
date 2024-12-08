#pragma once

#include <string>
#include <type_traits>
#include <format>
#include <typeinfo>
#include <tuple>
#include <chrono>
#include <vector>

#include "picojson.h"
#include "raylib.h"
#include "PicoEcsCpp.h"

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

			struct Object
			{
				uint32_t h = 0; // handle
			};

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

			struct Canvas // texture to draw on
			{
				uint32_t h = 0; // handle
			};

			struct Name
			{
				std::string n;	// name
			};

			struct Description
			{
				std::string d;	// description
			};

			struct Nodes
			{
				std::vector<Vector2> n;	// nodes
			};

			struct Layer
			{
				int l;	// layer
			};

			struct Brush
			{

			};

			struct Script
			{
				uint32_t h = 0;	// handle
			};

			struct Serializeable
			{
			};

			struct Text
			{
				std::string t; // text
				uint32_t f = 0; // font
			};
		}
	}
}