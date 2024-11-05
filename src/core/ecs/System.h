#pragma once

#include "Types.h"
#include "EcsManager.h"

#include <set>

namespace hnd
{
	namespace core
	{
		class System
		{
		public:
			std::set<Entity> entities;
		};
	}
}