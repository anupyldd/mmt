#include "Atlas.h"

namespace hnd
{
	namespace core
	{
		bool Atlas::RenameMap(const std::string& name, const std::string& newName)
		{
			try
			{
				GetMapByName(name).value().name = newName;
			}
			catch (const std::exception& e)
			{
				LOG_ERROR(std::format("Failed to rename map {}: {}", name, e.what()));
			}
		}
		bool Atlas::UpdateLastEditTime(const std::string& name)
		{
			try
			{
				GetMapByName(name).value().lastEditTime = std::chrono::system_clock::now();
			}
			catch (const std::exception& e)
			{
				LOG_ERROR(std::format("Failed to update last edit time for map {}: {}", name, e.what()));
			}
		}
		std::optional<MapData&> Atlas::GetMapByName(const std::string& name)
		{
			auto iter = std::find_if(maps.begin(), maps.end(), 
				[name](const MapData& data) { return data.name == name; });
			if (iter == maps.end()) return std::nullopt;
			else return (*iter);
		}
	}
}