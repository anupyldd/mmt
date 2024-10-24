#pragma once

#include "MapObject.h"

#include "raylib.h"

#include <vector>
#include <memory>
#include <array>

namespace hnd
{
	namespace core
	{
		constexpr int QuadtreeNodeCapacity = 4;
		using MapObjShrPtr = std::shared_ptr<MapObject>;
		
		class QuadtreeNode
		{
		public:
			QuadtreeNode() = default;
			QuadtreeNode(const Rectangle& bound);

			bool InsertObject(MapObject obj);
			std::vector<MapObjShrPtr> Query(const Rectangle& rect, std::vector<MapObjShrPtr> found) const;

		private:
			void Subdivide();

		private:
			Rectangle	boundary;
			bool		divided = false;

			std::vector<MapObjShrPtr>		objects;

			std::unique_ptr<QuadtreeNode>	northWest,
											northEast,
											southWest,
											southEast;
		};
	}
}