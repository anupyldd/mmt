#pragma once

#include <cstdint>
#include <string>
#include <algorithm>

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
	}
}