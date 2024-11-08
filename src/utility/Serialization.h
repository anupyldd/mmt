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
					vals.emplace_back(picojson::value(v));
				}
			}
			else
			{
				for (const auto& v : vec)
				{
					vals.emplace_back(picojson::value(static_cast<double>(v)));
				}
			}
			obj[name] = picojson::value(vals);
		}

		//--------------------------------------------------------------------

		template<class T>
		inline void NumberFromJson(const picojson::object& obj, T var, const char* name)
		{
			var = static_cast<T>(obj.at(name).get<double>());
		}

		template<class T>
		inline void NumberToStandardType(double num, T& var)
		{
			var = static_cast<T>(num);
		}


		// non-const obj version
		template<class... Nums>
		inline void NumbersFromJson(picojson::object& obj, const std::pair<Nums&, const char*>&... nums)
		{
			([&]
				{
					NumberToStandardType(obj.at(nums.second).get<double>(), nums.first);
				}
			(), ...);
		}

		// const obj version
		template<class... Nums>
		inline void NumbersFromJson(const picojson::object& obj, const std::pair<Nums&, const char*>&... nums)
		{
			([&]
				{
					NumberToStandardType(obj.at(nums.second).get<double>(), nums.first);
				}
			(), ...);
		}

		// (non-const) first - value, second - name
		inline void StringsFromJson(picojson::value::object& obj,
			const std::initializer_list<std::pair<std::string&, std::string>>& strs)
		{
			for (const auto& str : strs)
			{
				str.first = obj.at(str.second).get<std::string>();
			}
		}

		// (const) first - value, second - name
		inline void StringsFromJson(const picojson::value::object& obj,
			const std::initializer_list<std::pair<std::string&, std::string>>& strs)
		{
			for (const auto& str : strs)
			{
				str.first = obj.at(str.second).get<std::string>();
			}
		}
	}
}