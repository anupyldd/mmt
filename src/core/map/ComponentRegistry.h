#pragma once

#include "../../utility/Defines.h"
#include "Components.h"

#include <unordered_map>
#include <functional>
#include <typeindex>
#include <typeinfo>
#include <sstream>
#include <string>
#include <any>

namespace mmt
{
	namespace core
	{
		class ComponentRegistry
		{
			MMT_SINGLETON(ComponentRegistry);

		public:
			ComponentRegistry();

			template<class CompType>
			std::string GetComponentCode()
			{
				return compCodes.at(typeid(CompType));
			}

			std::type_index GetComponentIndex(const std::string& code)
			{
				return compInds.at(code);
			}

			template<class CompType>
			constexpr void RegisterComponent(const std::string& code)
			{
				compCodes.insert({ typeid(CompType),code });
				compInds.insert({ code, typeid(CompType) });
			}
			
		private:
			std::unordered_map<std::type_index, std::string> compCodes;
			std::unordered_map<std::string, std::type_index> compInds;
		};

		// ---------------------------------------------

		inline ComponentRegistry::ComponentRegistry()
		{
			using namespace comps;

			RegisterComponent<Transform>	("tr");
			RegisterComponent<Object>		("ob");
			RegisterComponent<Active>		("ac");
			RegisterComponent<NotVisible>	("nv");
			RegisterComponent<Texture>		("tx");
			RegisterComponent<Canvas>		("cn");
			RegisterComponent<Name>			("nm");
			RegisterComponent<Description>	("ds");
			RegisterComponent<Nodes>		("nd");
			RegisterComponent<Layer>		("lr");
			RegisterComponent<Brush>		("br");
			RegisterComponent<Script>		("sc");
			RegisterComponent<Serializeable>("sr");
			RegisterComponent<Text>			("tt");
		}
	}
}