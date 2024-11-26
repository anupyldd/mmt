#include "Map.h"

namespace mmt
{
	namespace core
	{
		Map& Map::Create(MapParams par)
		{
			params = std::move(par);

			return *this;
		}
		Map& Map::SetData(MapData* newData)
		{
			if(newData) data = newData;
			return *this;
		}

		void Map::Update()
		{
		}

		//-----------------------------------------

		MapData::MapData(const std::string& name)
			:
			name(name),
			creationTime(std::chrono::system_clock::now()),
			lastEditTime(std::chrono::system_clock::now())
		{
			id = util::HashString(name.c_str());
			preview = GenImageColor(100, 50, BLACK);	// just a placeholder until first save
		}
		std::string MapData::CreationTimeAsString()
		{
			return TimeAsString(creationTime);
		}
		std::string MapData::LastEditTimeAsString()
		{
			return TimeAsString(lastEditTime);
		}
		void MapData::SetPreview(Image newPreview)
		{
			preview = std::move(newPreview);
		}
		std::string MapData::TimeAsString(std::chrono::time_point<std::chrono::system_clock> timePoint)
		{
			auto in_time_t = std::chrono::system_clock::to_time_t(timePoint);
			std::stringstream ss;
			ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
			return ss.str();
		}
	}
}