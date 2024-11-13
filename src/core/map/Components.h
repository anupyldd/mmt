#pragma once

#include <string>
#include <type_traits>
#include <format>
#include <typeinfo>
#include <tuple>

#include "picojson.h"
#include "raylib.h"

#include "../../utility/StringHash.h"
#include "../../utility/Defines.h"
#include "../../utility/Serialization.h"
#include "EcsTypes.h"

/*
defines a component constructor that takes in an instance of the component object as argument,
then copies it into the actual component. Final constructor has a name "<Component>Constructor"
*/
#define DEFINE_COMPONENT_CONSTRUCTOR(Component)											\
	void Component##Constructor (ecs_t* ecs, ecs_id_t entity_id, void* ptr, void* args)	\
	{																					\
		Component* comp = static_cast<Component*>(ptr);									\
		Component* init = static_cast<Component*>(args);								\
		if(init) (*comp) = (*init);														\
	}

namespace hnd
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
				virtual JsonValue Serialize() = 0;
				virtual void Deserialize(JsonObj& obj) = 0;
				virtual ~ComponentBase() = default;
			};
			template<class CompType>
			struct Component : ComponentBase
			{
				virtual JsonValue Serialize() override
				{
					return static_cast<CompType*>(this)->Serialize();
				}

				virtual void Deserialize(JsonObj& obj) override
				{
					static_cast<CompType*>(this)->Deserialize(obj);
				}
			};

			// ------------------------------------------------------------------------
			// ------------------------------------------------------------------------
			// ------------------------------------------------------------------------

			struct Transform : public Component<Transform>
			{
				float	x = 0.0f, 
						y = 0.0f;
				float	scale = 1.0f;
				float	angle = 0.0f;

				virtual JsonValue Serialize() override final
				{
					picojson::value::object obj;
					NumbersToJson(
						obj,
						PAIR(x,		STR(x)),
						PAIR(y,		STR(y)),
						PAIR(scale, STR(scale)),
						PAIR(angle, STR(angle)));
					picojson::value val(obj);
					return val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					NumbersFromJson(
						obj,
						PAIR(REF(x),	 STR(x)),
						PAIR(REF(y),	 STR(y)),
						PAIR(REF(scale), STR(scale)),
						PAIR(REF(angle), STR(angle)));
				}
			};
			DEFINE_COMPONENT_CONSTRUCTOR(Transform);

			struct Sprite : public Component<Sprite>
			{
				uint64_t handle = 0;

				virtual JsonValue Serialize() override final
				{
					picojson::value::object obj;
					StringsToJson(
						obj,
						{
							{std::to_string(handle), STR(handle)}
						}
					);
					picojson::value val(obj);
					return val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					std::string val;
					StringsFromJson(
						obj,
						{
							{val, STR(handle)}
						}
					);
					handle = std::stoll(val);
				}
			};
			DEFINE_COMPONENT_CONSTRUCTOR(Sprite);

			struct Name : public Component<Name>
			{
				std::string name;

				virtual JsonValue Serialize() override final
				{
					picojson::value::object obj;
					StringsToJson(
						obj,
						{
							{name, STR(name)}
						}
					);
					picojson::value val(obj);
					return val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					StringsFromJson(
						obj,
						{
							{name, STR(name)}
						}
					);
				}
			};
			DEFINE_COMPONENT_CONSTRUCTOR(Name);

			struct Description : public Component<Description>
			{
				std::string desc;

				virtual JsonValue Serialize() override final
				{
					picojson::value::object obj;
					StringsToJson(
						obj,
						{
							{desc, STR(desc)}
						}
					);
					picojson::value val(obj);
					return val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					StringsFromJson(
						obj,
						{
							{desc, STR(desc)}
						}
					);
				}
			};
			DEFINE_COMPONENT_CONSTRUCTOR(Description);


			/*
			struct Layer : public Component<Layer>
			{
				int order = 0;
			};
			*/
		}
		
	}
}