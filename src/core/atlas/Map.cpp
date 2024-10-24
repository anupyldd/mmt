#include "Map.h"

namespace hnd
{
	namespace core
	{
		Map::Map(const Vector2& size)
			: size(size)
		{
		}
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
		bool Map::AddLayer(const std::string& name)
		{
			if (LayerExists(name)) return false;

			layers.emplace_back(Rectangle{ 0,0,size.x,size.y }, name);
		}
		bool Map::LayerExists(const std::string& name) const
		{
			for (const auto& l : layers)
			{
				if (l.GetName() == name) return true;
			}
			return false;
		}
	}
}