#pragma once

#include <cstdint>
#include <string>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <vector>

namespace mmt
{
	namespace util
	{
        constexpr uint64_t HashString(const char* input)
        {
            uint64_t hash = 5381;
            while (*input)
            {
                hash = static_cast<uint64_t>(*input++) + 33 * hash;
            }
            return hash;
        }

        // uint32 version
        constexpr uint32_t HashString32(const char* input)
        {
            uint32_t hash = 5381;
            while (*input)
            {
                hash = static_cast<uint32_t>(*input++) + 33 * hash;
            }
            return hash;
        }

        // gets name after '.' or '->'. e.g. gets "name" from "app->name"
        constexpr std::string GetMemberName(const char* name)
        {
            std::string str(name);
            if (str.find('.') != str.npos)
                return str.substr(str.find_last_of('.') + 1);
            else
                return str.substr(str.find_last_of('>') + 1);
        }

        inline std::string TimeAsString(std::chrono::time_point<std::chrono::system_clock> timePoint)
        {
            auto in_time_t = std::chrono::system_clock::to_time_t(timePoint);
            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
            return ss.str();
        }

        inline std::vector<std::string> SplitByDelimiter(const std::string& str, const char delim)
        {
            std::vector<std::string> split;
            std::stringstream sstr(str);
            std::string part;
            while (std::getline(sstr, part, delim))
            {
                split.push_back(part);
            }
            return split;
        }

        inline std::string GetExtension(const std::string& str)
        {
            return str.substr(str.find_last_of('.'));
        }

        inline std::string RemoveExtension(const std::string& str)
        {
            return str.substr(0, str.find_last_of('.'));
        }
	}
}