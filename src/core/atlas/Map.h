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
			Map(const Vector2& size);

			void Update();
			void Draw();

			bool AddLayer(const std::string& name);

		private:
			bool LayerExists(const std::string& name) const;

		private:
			std::list<Layer>	layers;
			Vector2				size;
		};
	}
}