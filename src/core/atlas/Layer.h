#pragma once

#include "raylib.h"

#include "MapObject.h"
#include "Quadtree.h"
#include "../../utility/Log.h"

#include <vector>
#include <unordered_map>

namespace hnd
{
	namespace core
	{
		class Layer
		{
		public:
			Layer() = default;
			Layer(const Rectangle& rect);

			void Update();
			void Draw(const Rectangle& viewport);

			void AddObjectMouse();
			void AddObject(const MapObject& obj);

		private:
			QuadtreeNode	objectTree;

			RenderTexture2D	canvas;
			Image			mask;

			float			opacity = 1.0f;	// 0...1
			bool			visible = true;
		};
	}
}