#pragma once

#include <vector>
#include <memory>
#include <filesystem>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <format>

#include "raylib.h"

#include "../ecs/EcsManager.h"
#include "../../utility/Log.h"
#include "../../utility/StringHash.h"

namespace hnd
{
	namespace core
	{
		struct MapParams;

		class Map
		{
		public:
			Map() = default;

			void Create(MapParams par);

		private:
			EcsManager ecs;
			MapParams params;
		};

		//------------------------------------

		struct MapData
		{
			std::unique_ptr<Map> map;
			std::string name;
			uint64_t id = 0;	// hashed name
			std::chrono::time_point<std::chrono::system_clock> creationTime;
			std::chrono::time_point<std::chrono::system_clock> lastEditTime;

			MapData(const std::string& name)
				:
				name(name),
				creationTime(std::chrono::system_clock::now()),
				lastEditTime(std::chrono::system_clock::now())
			{
				id = util::HashString(name.c_str());
			}

		public:
			std::string CreationTimeAsString()
			{
				return TimeAsString(creationTime);
			}
			std::string LastEditTimeAsString()
			{
				return TimeAsString(lastEditTime);
			}
		private:
			std::string TimeAsString(std::chrono::time_point<std::chrono::system_clock> timePoint)
			{
				auto in_time_t = std::chrono::system_clock::to_time_t(timePoint);
				std::stringstream ss;
				ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
				return ss.str();
			}
		};

		struct MapParams
		{
			int width = 0, height = 0,
				density = 0;
		};
	}
}