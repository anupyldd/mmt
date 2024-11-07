#pragma once

#include <string>
#include <type_traits>
#include <format>
#include <typeinfo>

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
			using ComponentId = ecs_id_t;

			// COMPONENT ID'S TO BE STORED IN EACH ECS INSTANCE SEPARATELY IN A MAP

			struct ComponentBase
			{
				virtual std::string Serialize() = 0;
				virtual void Deserialize(const std::string& str) = 0;
				virtual ~ComponentBase() = default;
			};
			template<class CompType>
			struct Component : ComponentBase
			{
				virtual std::string Serialize() override
				{
					return static_cast<CompType*>(this)->Serialize();
				}

				virtual void Deserialize(const std::string& str) override
				{
					static_cast<CompType*>(this)->Deserialize(const std::string & str);
				}
			};

			// ------------------------------------

			struct Position : Component<Position>
			{
				float	x = 0, 
						y = 0;

				virtual std::string Serialize() override
				{
					return std::format("{}|{}", x, y);
				}
				virtual void Deserialize(const std::string& str) override
				{
					auto vals = util::DeserializeComponent(str);
					x = std::stof(vals[0]);
					x = std::stof(vals[1]);
				}
			};
			
		}
		
	}
}