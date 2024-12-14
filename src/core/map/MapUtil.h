#pragma once

#include <string>
#include <algorithm>
#include <filesystem>
#include <format>

#include "../../utility/Log.h"

namespace mmt
{
	namespace util
	{
		// removes spaces
		inline std::string FormatMapName(std::string mapName)
		{
			std::string::iterator end_pos = std::remove(mapName.begin(), mapName.end(), ' ');
			mapName.erase(end_pos, mapName.end());
		}
	}
}