#include "Map.h"

namespace hnd
{
	namespace core
	{
		void Map::Create(MapParams par)
		{
			params = std::move(par);
			ecs.Init();
			ecs.RegisterCommon();
		}
	}
}