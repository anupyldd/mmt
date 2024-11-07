#pragma once

#include <string>
#include <type_traits>

#include "pico/pico_ecs.h"

#include "../../utility/StringHash.h"

namespace hnd
{
	namespace core
	{
		namespace components
		{
			using ComponentId = ecs_id_t;

			template<class CompType>
			inline constexpr uint32_t GenerateComponentId()
			{
				return util::HashString32(typeid(CompType).name());
			}

			struct Serializeable
			{
				virtual std::string Serialize() = 0;
			};
			template<class CompType>
			struct Component : Serializeable
			{
				Component() { id = GenerateComponentId<CompType>(); }

				virtual std::string Serialize() override final
				{
					// TODO
				}

				static ComponentId id;
			};
		}
		
	}
}