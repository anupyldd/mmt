#pragma once

#include <string>
#include <algorithm>
#include <filesystem>
#include <format>

#include "../../utility/Log.h"

namespace hnd
{
	namespace util
	{
		// removes spaces
		inline std::string FormatMapName(std::string mapName)
		{
			std::string::iterator end_pos = std::remove(mapName.begin(), mapName.end(), ' ');
			mapName.erase(end_pos, mapName.end());
		}

		/*
		* gets path either to main save file (if copy == 0).
		* copy can be 0, 1, 2
		*/
		inline std::filesystem::path GetPathToMapSaveFile(
			const std::string& atlasName,
			const std::string& mapName, 
			int copy = 0)
		{
			auto cwd = std::filesystem::current_path();
			cwd = cwd / "data" / "maps";
			switch (copy)
			{
			case 0:
			{
				cwd = cwd / "main" / atlasName / mapName / "save.json";
				return cwd;
			}
			case 1:
			{
				cwd = cwd / "copy" / "1" / atlasName / mapName / "save.json";
				return cwd;
			}
			case 2:
			{
				cwd = cwd / "copy" / "2" / atlasName / mapName / "save.json";
				return cwd;
			}
			default:
				LOG_ERROR(std::format("Map copy {} does not exist", copy));
				return cwd;
			}
		}
	}
}