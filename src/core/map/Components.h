#pragma once

#include <string>
#include <type_traits>
#include <format>
#include <typeinfo>
#include <tuple>

#include "picojson.h"
#include "raylib.h"

#include "../../utility/StringUtil.h"
#include "../../utility/Defines.h"
#include "../../utility/Serialization.h"
#include "EcsTypes.h"

/*
defines a component constructor that takes in an instance of the component object as argument,
then copies it into the actual component. Final constructor has a name "<Component>Constructor"
*/
#define DEFINE_COMPONENT_CONSTRUCTOR(Component)													\
	inline void Component##Constructor (ecs_t* ecs, ecs_id_t entity_id, void* ptr, void* args)	\
	{																							\
		Component* comp = static_cast<Component*>(ptr);											\
		Component* init = static_cast<Component*>(args);										\
		if(init) (*comp) = (*init);																\
	}

/*
* using this assumes that all ecs instances on all maps use the same components.
* final id looks like "<Component>Id"
*/
#define GENERATE_COMPONENT_ID(Component) \
	ecs_id_t Component##Id = util::HashString32(#Component);

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

			struct Transform : public Component<Transform>
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
			DEFINE_COMPONENT_CONSTRUCTOR(Transform);

			struct Sprite : public Component<Sprite>
			{
				uint64_t handle = 0;

				virtual void Serialize(JsonValObj& valObj) override final
				{
					picojson::value::object obj;
					std::string v = std::to_string(handle);
					ToJson(
						obj,
						MMT_SERIALIZE_EX(v, handle)
					);
					picojson::value val(obj);
					valObj[STR(Sprite)] = val;
				}
				virtual void Deserialize(JsonObj& obj) override final
				{
					std::string val;
					FromJson(
						obj,
						MMT_DESERIALIZE_EX(val, handle)
					);
					handle = std::stoll(val);
				}
			};
			DEFINE_COMPONENT_CONSTRUCTOR(Sprite);

			struct Name : public Component<Name>
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
			DEFINE_COMPONENT_CONSTRUCTOR(Name);

			struct Description : public Component<Description>
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
			DEFINE_COMPONENT_CONSTRUCTOR(Description);

			struct Visible : Component<Visible>
			{
				virtual void Serialize(JsonValObj& valObj) override final 
				{
					valObj[STR(Visible)] = picojson::value();
				}
				virtual void Deserialize(JsonObj& obj) override final { }
			};

			/*
			struct Layer : public Component<Layer>
			{
				int order = 0;
			};
			*/
		}
		
	}
}