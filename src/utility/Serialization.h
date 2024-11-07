#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <any>
#include <tuple>
#include <utility>
#include <initializer_list>

#include "picojson.h"

namespace hnd
{
	namespace util
	{
		template<class... Nums>
		inline void NumbersToJson(picojson::value::object& obj, const std::pair<Nums, const char *>&... nums)
		{
			([&]
				{
					obj[nums.second] = picojson::value(static_cast<double>(nums.first));
				} 
			(), ...);
		}

		// first - value, second - name
		inline void StringsToJson(picojson::value::object& obj, 
			const std::initializer_list<std::pair<std::string, std::string>>& strs)
		{
			for (const auto& str : strs)
			{
				obj[str.second] = picojson::value(str.first);
			}
		}

		template<class T>
		inline void VectorToJson(const std::vector<T>& vec, const std::string& name, picojson::value::object& obj)
		{
			picojson::value::array vals;
			if (typeid(T) == typeid(std::string))
			{
				for (const auto& v : vec)
				{
					vals.emplace_back(picojson::value(f));
				}
			}
			else
			{
				for (const auto& v : vec)
				{
					vals.emplace_back(picojson::value(static_cast<double>(f)););
				}
			}
			obj[name] = picojson::value(vals);
		}

		template<class T>
		void NumberFromJson(const picojson::object& obj, T var, const char* name)
		{
			var = static_cast<T>(obj.at(name).get<double>());
		}

	}
}