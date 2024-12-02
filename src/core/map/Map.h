#pragma once

#include <vector>
#include <memory>
#include <filesystem>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <optional>
#include <format>

#include "raylib.h"
#include "PicoEcsCpp.h"

#include "../../utility/Log.h"
#include "../../utility/StringUtil.h"

namespace mmt
{
	namespace core
	{
		class Map;

		struct MapData
		{
			std::unique_ptr<Map> map;
			std::string name;
			uint64_t id = 0;	// hashed name
			std::chrono::time_point<std::chrono::system_clock> creationTime;
			std::chrono::time_point<std::chrono::system_clock> lastEditTime;

		public:
			MapData(const std::string& name);

		public:
			std::string CreationTimeAsString();
			std::string LastEditTimeAsString();

			void SetPreview(Image newPreview);
		private:
			std::string TimeAsString(std::chrono::time_point<std::chrono::system_clock> timePoint);
		};

		struct MapParams
		{
			int width = 0, height = 0;
		};

		//----------------------------

		using namespace pico_ecs_cpp;

		class Map
		{
		public:
			Map() = default;

			Map& Create(MapParams par);
			Map& SetData(MapData* newData);

			void Update();

			bool CreateLayer(const std::string& name);

		private:
			MapParams params;
			MapData* data = nullptr;

		private:
			EcsInstance ecs;
		};
		
	}
}