#pragma once

#include <cstdint>

namespace hnd
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
	}
}