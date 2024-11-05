#pragma once

#include "raylib.h"

#include <cstdint>
#include <string>

namespace hnd
{
	namespace core
	{
		namespace components
		{
			struct Transform
			{
				Vector2	pos{ 0 },
						scale{ 1 };
				float	rotation = 0;
			};

			struct SizeI
			{
				int width = 0,
					height = 0;
			};

			struct SizeF
			{
				float	width = 0,
						height = 0;
			};

			struct Sprite
			{
				uint64_t handle = 0;
			};

			struct Name
			{
				std::string name;
			};

			struct Description
			{
				std::string description;
			};

			struct Group
			{
				uint64_t group = 0;
			};

			struct Layer
			{
				int		layer = 0;
				float	opacity = 1;
			};

			struct Mask
			{
				Texture2D mask;
			};

			struct Canvas
			{
				RenderTexture2D texture;
			};

			struct MapLink
			{
				uint64_t id;	// id of a map to which this entity links
			};

			struct Visible 
			{
				bool justChanged = false;
			};

			// Tag components ---------------

			struct SelectedObject {};	// actual object that is already placed on the map
			struct PathNode {};
		}
	}
}