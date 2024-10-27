#include "Layer.h"

namespace hnd
{
	namespace core
	{
		Layer::Layer(const Rectangle& rect, const std::string& name)
			: objectTree(rect), name(name)
		{
			canvas = LoadRenderTexture(rect.width, rect.height);

			BeginTextureMode(canvas);
			ClearBackground(WHITE);
			EndTextureMode();
		}
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
		std::string Layer::GetName() const
		{
			return name;
		}
		void Layer::Update()
		{
			if (!visible) return;

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				AddObjectMouse();
		}
		void Layer::Draw(const Rectangle& viewport)
		{
			DrawTexture(canvas.texture, 0, 0, Color{ 0,0,0,0 });
			objectTree.DrawCells();

			std::vector<MapObjShrPtr> objInView;
			objectTree.Query(viewport, objInView);

			DrawRectangleLines(viewport.x, viewport.y, viewport.width, viewport.height, MAGENTA);

			for (auto& obj : objInView)
			{
				if (obj) obj->Draw();
			}
		}
	}
}