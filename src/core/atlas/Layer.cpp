#include "Layer.h"

namespace hnd
{
	namespace core
	{
		void Layer::AddObjectMouse()
		{
			MapObject obj{ 0,GetMousePosition(),1,0 };
			AddObject(obj);
		}
		void Layer::AddObject(const MapObject& obj)
		{
			if (!objectTree.InsertObject(obj))
				LOG_ERROR("Failed to insert object: " + std::to_string(obj.id)); 
		}
		void Layer::Update()
		{
			if (!visible) return;

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				AddObjectMouse();
		}
		void Layer::Draw(const Rectangle& viewport)
		{
			std::vector<MapObjShrPtr> objInView;
			objectTree.Query(viewport, objInView);

			for (auto& obj : objInView)
			{
				if (obj->group->visible) obj->Draw();
			}
		}
	}
}