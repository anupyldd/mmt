#include "Atlas.h"

namespace hnd
{
	namespace core
	{
		void Atlas::UpdateActiveMap()
		{
			activeMap->Update();
		}
		void Atlas::SortMaps(MapSort by)
		{
			currentSort = by;

			switch (by)
			{
			case MapSort::CreatedAsc:
			{
				std::ranges::sort(maps, [](const MapData& a, const MapData& b)
					{ return a.creationTime < b.creationTime; });
				break;
			} 
			case MapSort::CreatedDesc:
			{
				std::ranges::sort(maps, [](const MapData& a, const MapData& b)
					{ return a.creationTime > b.creationTime; });
				break;
			}
			case MapSort::LastEditAsc:
			{
				std::ranges::sort(maps, [](const MapData& a, const MapData& b)
					{ return a.lastEditTime < b.lastEditTime; });
				break;
			}
			case MapSort::LastEditDesc:
			{
				std::ranges::sort(maps, [](const MapData& a, const MapData& b)
					{ return a.lastEditTime > b.lastEditTime; });
				break;
			}
			case MapSort::AlphaAsc:
			{
				std::ranges::sort(maps, [](const MapData& a, const MapData& b)
					{ return a.name < b.name; });
				break;
			}
			case MapSort::AlphaDesc:
			{
				std::ranges::sort(maps, [](const MapData& a, const MapData& b)
					{ return a.name > b.name; });
				break;
			}
			default:
				break;
			}
		}
		bool Atlas::RenameMap(const std::string& name, const std::string& newName)
		{
			try
			{
				//GetMapByName(name).value().name = newName;
				return true;
			}
			catch (const std::exception& e)
			{
				HND_LOG_ERROR(std::format("Failed to rename map {}: {}", name, e.what()));
				return false;
			}
		}
		bool Atlas::UpdateLastEditTime(const std::string& name)
		{
			try
			{
				//GetMapByName(name).value().lastEditTime = std::chrono::system_clock::now();
				return true;
			}
			catch (const std::exception& e)
			{
				HND_LOG_ERROR(std::format("Failed to update last edit time for map {}: {}", name, e.what()));
				return false;
			}
		}
		/*
		std::optional<MapData&> Atlas::GetMapByName(const std::string& name)
		{
			auto iter = std::find_if(maps.begin(), maps.end(), 
				[name](const MapData& data) { return data.name == name; });
			if (iter == maps.end()) return std::nullopt;
			else return (*iter);
		}
		*/
	}
}