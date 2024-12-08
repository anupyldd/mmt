#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <any>
#include <tuple>
#include <utility>
#include <type_traits>
#include <initializer_list>

#include "picojson.h"
#include "rfl.hpp"
#include "rfl/json.hpp"

namespace mmt
{
	namespace util
	{

		template<class T>
		inline void NumberToStandardType(double num, T& var)
		{
			var = static_cast<T>(num);
		}

		// -------------------------------------------------------
		// -------------------------------------------------------

		// works only with strings and numbers
		template<class... Vars>
		inline void ToJson(picojson::value::object& obj, const std::pair<Vars, const char*>&... vars)
		{
			([&]
				{
					if constexpr (std::is_arithmetic<decltype(vars.first)>::value)
					{
						obj[vars.second] = picojson::value(static_cast<double>(vars.first));
					}
					else
					{
						obj[vars.second] = picojson::value(vars.first);
					}
				}
			(), ...);
		}

		// works only with strings and numbers
		template<class... Vars>
		inline void FromJson(const picojson::object& obj, const std::pair<Vars&, const char*>&... vars)
		{
			([&]
				{
					//NumberToStandardType(obj.at(nums.second).get<double>(), nums.first);
					if constexpr (
						std::is_same<decltype(vars.first), int&>::value ||
						std::is_same<decltype(vars.first), float&>::value ||
						std::is_same<decltype(vars.first), double&>::value ||
						std::is_same<decltype(vars.first), uint8_t&>::value ||
						std::is_same<decltype(vars.first), uint16_t&>::value ||
						std::is_same<decltype(vars.first), uint32_t&>::value ||
						std::is_same<decltype(vars.first), uint64_t&>::value)
					{
						NumberToStandardType(obj.at(vars.second).get<double>(), vars.first);
					}
					else
					{
						vars.first = obj.at(vars.second).get<std::string>();
						//std::initializer_list<std::pair<std::string&, std::string>> ls = { vars.first,vars.second };
						//StringsFromJson(obj, ls);
					}
				}
			(), ...);
		}

		// -------------------------------------------------------
		// -------------------------------------------------------

	}
}