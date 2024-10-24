#include "Map.h"

namespace hnd
{
	namespace core
	{
		void Map::Update()
		{
			for (auto& l : layers)
			{
				l.Update();
			}
		}
		void Map::Draw()
		{
			Rectangle viewport{ 0,0,static_cast<float>(GetScreenWidth()),
						static_cast<float>(GetScreenHeight()) };
			for (auto& l : layers)
			{
				l.Draw(viewport);
			}
		}
	}
}