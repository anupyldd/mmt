#pragma once

#include <list>

#include "Layer.h"

namespace hnd
{
	namespace core
	{
		class Map
		{
		public:
			Map() = default;

			void Update();
			void Draw();

		private:
			std::list<Layer> layers;
		};
	}
}