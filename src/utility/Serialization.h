#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <any>

namespace hnd
{
	namespace util
	{
		// takes in a string of format value1|value2|...|valueN and returns a vector of individual value strings
		std::vector<std::string> DeserializeComponent(const std::string& str)
		{
			std::vector<std::string> res;
			std::stringstream sstr(str);
			std::string val;
			while (std::getline(sstr,val,'|'))
			{
				res.push_back(val);
			}
			return res;
		}
	}
}