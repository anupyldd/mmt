#pragma once

#include <string>
#include <vector>

#include "MapObject.h"

namespace hnd
{
	namespace core
	{
		struct MapObjectGroup
		{
			std::string name;
			std::vector<MapObject> objects;
		};
	}
}