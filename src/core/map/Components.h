#pragma once

#include <string>
#include <type_traits>
#include <format>
#include <typeinfo>
#include <tuple>

#include "picojson.h"
#include "pico/pico_ecs.h"
#include "raylib.h"

#include "../../utility/StringHash.h"
#include "../../utility/Defines.h"
#include "../../utility/Serialization.h"

namespace hnd
{
	namespace core
	{
		namespace components
		{
			// COMPONENT ID'S TO BE STORED IN EACH ECS INSTANCE SEPARATELY IN A MAP

			using namespace util;

			using JsonValue = picojson::value;
			using JsonObj = picojson::object;
			using JsonValObj = picojson::value::object;

			struct ComponentBase
			{
				virtual JsonValue Serialize() = 0;
				virtual void Deserialize(const JsonObj& obj) = 0;
				virtual ~ComponentBase() = default;
			};
			template<class CompType>
			struct Component : ComponentBase
			{
				virtual JsonValue Serialize() override
				{
					return static_cast<CompType*>(this)->Serialize();
				}

				virtual void Deserialize(const JsonObj& obj) override
				{
					static_cast<CompType*>(this)->Deserialize(obj);
				}
			};

			// ------------------------------------

			struct Position : Component<Position>
			{
				float	x = 0, 
						y = 0;

				virtual JsonValue Serialize() override final
				{
					picojson::value::object obj;
					NumbersToJson(obj, PAIR(x, "x"), PAIR(y, "y"));
					picojson::value val(obj);
					return val;
				}
				virtual void Deserialize(const JsonObj& obj) override final
				{
					NumberFromJson(obj, x, "x");
					NumberFromJson(obj, y, "y");
				}
			};
			

		}
		
	}
}