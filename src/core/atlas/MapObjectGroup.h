#pragma once

#include <string>
#include <memory>
#include <map>

#include "../../utility/Defines.h"

namespace hnd
{
	namespace core
	{
		class MapObjectGroupManager
		{
			SINGLETON(MapObjectGroupManager)

		public:
			struct MapObjectGroup
			{
				std::string name;
				bool visible = true;
			};

			std::shared_ptr<MapObjectGroup> GetGroupPtr(const std::string& name) const;
			bool GroupExists(const std::string& name) const;
			bool AddGroup(const std::string& name);

		private:
			std::map<std::string, std::shared_ptr<MapObjectGroup>> groups;
		};

		//-------------
		using MapObjGroup = MapObjectGroupManager::MapObjectGroup;
	}
}