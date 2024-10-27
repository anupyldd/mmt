#include "MapObject.h"


namespace hnd
{
	namespace core
	{
		/*
		void MapObjGroups::AddGroup(const std::string& str)
		{
			if (CanAddGroup()) groups.emplace_back(str);
		}
		bool MapObjGroups::CanAddGroup() const
		{
			return groups.size() < 60;
		}
		const std::list<MapObjGroup>& MapObjGroups::GetGroups() const
		{
			return groups;
		}
		size_t MapObjGroups::GetGroupIndex(const std::string& groupName) const
		{
			return std::distance(std::find_if(groups.begin(), groups.end(),
				[groupName](const MapObjGroup& group) {group.name == groupName; }), groups.begin());
		}
		std::vector<std::string> MapObjGroups::GetNameList() const
		{
			std::vector<std::string> res;
			for (const auto& g : groups)
				res.push_back(g.name);
			return res;
		}*/
		// -----------------------------------
		

		MapObject::MapObject(uint64_t id, const Vector2& pos, float scale, float angle)
			: id(id), pos(pos), scale(scale), angle(angle)
		{
			LOG_DBG(std::format("Created map object (id:{},x:{},y:{})", id, pos.x, pos.y));
		}

		void MapObject::Draw()
		{
			if (group && !group->visible) return;

			DrawCircle(pos.x, pos.y, 5, RED);
			//LOG_DBG("IMPLEMENT DRAWING THE OBJECT");
		}

		void MapObject::SetGroup(const std::string& name)
		{
			group = MapObjectGroupManager::GetInstance().GetGroupPtr(name);
		}

	}
}