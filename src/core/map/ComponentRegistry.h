#pragma once

#include "../../utility/Defines.h"
#include "Components.h"

#include <optional>

namespace mmt
{
	namespace core
	{
		/*
		* can hold all components in an optional
		* if there's no component, it's nullopt, and is not serialized
		* serialization and deserialization goes through this struct
		*/
		struct ComponentRegistry
		{
			std::optional<comps::Transform>		tr;
			std::optional<comps::Object>		ob;
			std::optional<comps::NotVisible>	nv;
			std::optional<comps::Texture>		tx;
			std::optional<comps::Canvas>		cn;
			std::optional<comps::Name>			nm;
			std::optional<comps::Description>	ds;
			std::optional<comps::Nodes>			nd;
			std::optional<comps::Layer>			lr;
			std::optional<comps::Brush>			br;
			std::optional<comps::Text>			tt;
			std::optional<comps::Script>		sc;
		};
	}
}