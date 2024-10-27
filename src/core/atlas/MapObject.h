#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <iterator>
#include <format>

#include "raylib.h"

#include "../../utility/StringHash.h"
#include "../../utility/Defines.h"
#include "../../utility/Log.h"
#include "MapObjectGroup.h"

namespace hnd
{
	namespace core
	{
		// things like stamps, icons, etc.
		struct MapObject
		{
			MapObject(uint64_t id, const Vector2& pos, float scale, float angle);

			void Draw();
			void SetGroup(const std::string& name);

			std::shared_ptr<MapObjGroup>	group;
			uint64_t						id;	// id by which texture to draw is found
			Vector2							pos;
			float							scale = 1.0f;
			float							angle = 0.0f;
		};
	}
}