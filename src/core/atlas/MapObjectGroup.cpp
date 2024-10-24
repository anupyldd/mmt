#include "MapObjectGroup.h"

namespace hnd
{
	namespace core
	{
		std::shared_ptr<MapObjGroup> MapObjectGroupManager::GetGroupPtr(const std::string& name) const
		{
			if (GroupExists(name)) return groups.at(name);
			else return nullptr;
		}

		bool MapObjectGroupManager::GroupExists(const std::string& name) const
		{
			return groups.contains(name);
		}

		bool MapObjectGroupManager::AddGroup(const std::string& name)
		{
			if (!GroupExists(name))
			{
				groups[name] = std::make_shared<MapObjectGroup>(name, true);
				return true;
			}
			return false;
		}


	}
}