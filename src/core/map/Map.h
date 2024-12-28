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
#include "ecs/PicoEcsCpp.h"

#include "../../utility/Log.h"
#include "../../utility/StringUtil.h"

namespace mmt
{
	namespace core
	{
		class Map;

		// serialized
		struct MapData
		{
			std::string name = "Undefined Name",
						description = "Undefined Description",
						creationTime = "Undefined Creation Time",
						lastEditTime = "Undefined Last Edit Time";

			int width = 100,
				height = 100,
				entityCount = 1000;
		};

		//----------------------------

		using namespace pico_ecs_cpp;

		class Map
		{
		public:
			Map() = default;

			void Create(int width, int height, const std::string& name);
			void Update();

		public:
			void CreateCanvas();

		private:
			std::unique_ptr<MapData> data;

		private:
			EcsInstance ecs;
			Camera2D camera;
		};
		
	}
}