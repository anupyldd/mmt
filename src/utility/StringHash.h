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
	}
}