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
			Layer(const Rectangle& rect, const std::string& name);

			void Update();
			void Draw(const Rectangle& viewport);

			void AddObjectMouse();
			void AddObject(const MapObject& obj);

			std::string GetName() const;

		private:
			QuadtreeNode	objectTree;

			RenderTexture2D	canvas;
			Image			mask;

			std::string		name;

			float			opacity = 1.0f;	// 0...1
			bool			visible = true;
		};
	}
}