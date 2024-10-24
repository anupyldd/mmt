#include "Quadtree.h"

namespace hnd
{
	namespace core
	{
		QuadtreeNode::QuadtreeNode(const Rectangle& bound)
			: boundary(bound)
		{
		}
		bool QuadtreeNode::InsertObject(MapObject obj)
		{
			if (!CheckCollisionPointRec(obj.pos, boundary)) return false;

			if (objects.size() < QuadtreeNodeCapacity)
			{
				objects.at(objects.size()) = std::make_shared<MapObject>(obj.id, obj.pos, obj.scale, obj.angle);
				return true;
			}
			else
			{
				if (!divided) Subdivide();
				return ( northWest->InsertObject(obj) || northEast->InsertObject(obj) ||
						 southWest->InsertObject(obj) || southEast->InsertObject(obj) );
			}
		}
		std::vector<MapObjShrPtr> QuadtreeNode::Query(const Rectangle& rect, std::vector<MapObjShrPtr> found) const
		{
			if (!CheckCollisionRecs(boundary, rect)) return found;

			for (const auto& obj : objects)
			{
				if (CheckCollisionPointRec(obj->pos, rect)) 
					found.push_back(obj);
			}
			if (divided)
			{
				northWest->Query(rect, found);
				northEast->Query(rect, found);
				southWest->Query(rect, found);
				southEast->Query(rect, found);
			}

			return found;
		}
		void QuadtreeNode::Subdivide()
		{
			const float x = boundary.x;
			const float y = boundary.y;
			const float w = boundary.width / 2;
			const float h = boundary.height / 2;

			const Rectangle nw{ x, y, w, h };
			const Rectangle ne{ x + w, y, w, h };
			const Rectangle sw{ x, y + h, w, h };
			const Rectangle se{ x + w, y + h, w, h };

			northWest = std::make_unique<QuadtreeNode>(nw);
			northEast = std::make_unique<QuadtreeNode>(ne);
			southWest = std::make_unique<QuadtreeNode>(sw);
			southEast = std::make_unique<QuadtreeNode>(se);

			divided = true;
		}
	}
}

