#pragma once

#include "../System.h"
#include "../EcsManager.h"
#include "../Components.h"

namespace hnd
{
	namespace core
	{
		class EcsManager;

		class VisibilitySystem : public System
		{
			void Update(EcsManager& mgr)
			{
				using namespace components;

				for (const auto& ent : entities)
				{
					auto& vis = mgr.GetComponent<Visible>(ent);
					auto& layer = mgr.GetComponent<Layer>(ent);
					if (vis.justChanged)
					{

					}
					else continue;
				}
			}
		};
	}
}