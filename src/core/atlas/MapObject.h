#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <iterator>

#include "raylib.h"

#include "../../utility/StringHash.h"
#include "../../utility/Defines.h"

namespace hnd
{
	namespace core
	{
		// things like stamps, icons, etc.
		struct MapObject
		{
			MapObject(uint64_t id, const Vector2& pos, float scale, float angle)
				: id(id), pos(pos), scale(scale), angle(angle) { }

			void Draw();

			//Texture2D	img;
			uint64_t	id;	// id by which texture to draw is found
			Vector2		pos;
			float		scale = 1.0f;
			float		angle = 0.0f;
		};

		// object draw group
		struct MapObjGroup
		{
			bool visible = true;
			std::vector<MapObject> objects;
		};
	}
}