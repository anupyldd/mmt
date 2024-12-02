#pragma once

#include <string>
#include <type_traits>
#include <format>
#include <typeinfo>
#include <tuple>
#include <chrono>

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
		namespace components
		{
			using namespace util;

			using JsonValue = picojson::value;
			using JsonObj = picojson::object;
			using JsonValObj = picojson::value::object;

			struct ComponentBase
			{
				virtual void Serialize(JsonValObj& valObj) = 0;
				virtual void Deserialize(JsonObj& obj) = 0;
				virtual ~ComponentBase() = default;
			};
			template<class CompType>
			struct Component : ComponentBase
			{
				virtual void Serialize(JsonValObj& valObj) override
				{
					static_cast<CompType*>(this)->Serialize(valObj);
				}

				virtual void Deserialize(JsonObj& obj) override
				{
					static_cast<CompType*>(this)->Deserialize(obj);
				}
			};

			// ------------------------------------------------------------------------
			// ------------------------------------------------------------------------
			// ------------------------------------------------------------------------
			/*
			MTT_COMPONENT(Atlas)
			{
				int sortBy = 2;
				std::string name = "Unnamed Atlas";
				uint32_t id = 0;

				virtual void Serialize(JsonValObj& valObj) override final
				{
					picojson::value::object obj;
					ToJson(
						obj,
						MMT_SERIALIZE(name),
						MMT_SERIALIZE(sortBy),
						MMT_SERIALIZE(id)
					);
					picojson::value val(obj);
					valObj[STR(Atlas)] = val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					FromJson(
						obj,
						MMT_DESERIALIZE(name),
						MMT_DESERIALIZE(sortBy),
						MMT_DESERIALIZE(id)
					);
				}
			};
			MTT_COMPONENT_CONSTRUCTOR(Atlas);

			MTT_COMPONENT(Map)
			{
				std::string name = "Unnamed map",
					creationTime = "Undefined time",
					lastEditTime = "Undefined time";
				uint32_t	atlasId = 0;

				virtual void Serialize(JsonValObj& valObj) override final
				{
					picojson::value::object obj;
					ToJson(
						obj,
						MMT_SERIALIZE(name),
						MMT_SERIALIZE(atlasId),
						MMT_SERIALIZE(creationTime),
						MMT_SERIALIZE(lastEditTime)
					);
					picojson::value val(obj);
					valObj[STR(Map)] = val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					FromJson(
						obj,
						MMT_DESERIALIZE(name),
						MMT_DESERIALIZE(atlasId),
						MMT_DESERIALIZE(creationTime),
						MMT_DESERIALIZE(lastEditTime)
					);
				}
			};
			MTT_COMPONENT_CONSTRUCTOR(Map);

			// ------------------------------------------------------------------------

			MTT_COMPONENT(Transform)
			{
				float	x = 0.0f, 
						y = 0.0f;
				float	scale = 1.0f;
				float	angle = 0.0f;

				virtual void Serialize(JsonValObj& valObj) override final
				{
					picojson::value::object obj;
					ToJson(
						obj,
						MMT_SERIALIZE(x),
						MMT_SERIALIZE(y),
						MMT_SERIALIZE(scale),
						MMT_SERIALIZE(angle)
					);
					picojson::value val(obj);
					valObj[STR(Transform)] = val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					FromJson(
						obj,
						MMT_DESERIALIZE(x),
						MMT_DESERIALIZE(y),
						MMT_DESERIALIZE(scale),
						MMT_DESERIALIZE(angle)
					);
				}
			};
			MTT_COMPONENT_CONSTRUCTOR(Transform);

			// texture from file, not canvas
			MTT_COMPONENT(Texture)
			{
				std::string name;

				virtual void Serialize(JsonValObj& valObj) override final
				{
					picojson::value::object obj;
					ToJson(
						obj,
						MMT_SERIALIZE(name)
					);
					picojson::value val(obj);
					valObj[STR(Texture)] = val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					FromJson(
						obj,
						MMT_DESERIALIZE(name)
					);
				}
			};
			MTT_COMPONENT_CONSTRUCTOR(Texture);

			MTT_COMPONENT(Sprite)
			{
				std::string name = 0;

				virtual void Serialize(JsonValObj& valObj) override final
				{
					picojson::value::object obj;
					ToJson(
						obj,
						MMT_SERIALIZE(name)
					);
					picojson::value val(obj);
					valObj[STR(Texture)] = val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					FromJson(
						obj,
						MMT_DESERIALIZE(name)
					);
				}
			};
			MTT_COMPONENT_CONSTRUCTOR(Sprite);

			MTT_COMPONENT(Name)
			{
				std::string name;

				virtual void Serialize(JsonValObj& valObj) override final
				{
					picojson::value::object obj;
					ToJson(
						obj,
						MMT_SERIALIZE(name)
					);
					picojson::value val(obj);
					valObj[STR(Name)] = val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					FromJson(
						obj,
						MMT_DESERIALIZE(name)
					);
				}
			};
			MTT_COMPONENT_CONSTRUCTOR(Name);

			MTT_COMPONENT(Description)
			{
				std::string desc;

				virtual void Serialize(JsonValObj& valObj) override final
				{
					picojson::value::object obj;
					ToJson(
						obj,
						MMT_SERIALIZE(desc)
					);
					picojson::value val(obj);
					valObj[STR(Description)] = val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					FromJson(
						obj,
						MMT_DESERIALIZE(desc)
					);
				}
			};
			MTT_COMPONENT_CONSTRUCTOR(Description);

			// markers ------------------------------------------------

			// can be active object, tool, map, whatever
			MTT_MARKER_COMPONENT(Active);
			MTT_MARKER_COMPONENT(Culled);
			*/
		}
		
	}
}