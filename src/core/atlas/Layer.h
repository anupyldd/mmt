#pragma once

#include "raylib.h"

#include "MapObject.h"

#include <vector>
#include <unordered_map>

namespace hnd
{
	namespace core
	{
		class Layer
		{
		public:


		private:
			

			RenderTexture2D	canvas;
			Image			mask;

			float			opacity = 1.0f;	// 0...1
			bool			visible = true;
		};
	}
}