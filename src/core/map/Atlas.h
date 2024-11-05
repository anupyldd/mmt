#pragma once

#include <vector>
#include <memory>
#include <filesystem>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <format>
#include <algorithm>
#include <optional>
#include <exception>

#include "Map.h"
#include "../../utility/Log.h"
#include "../../utility/StringHash.h"

namespace hnd
{
	namespace core
	{
		/// <summary>
		/// ~Asc: earliest first (date), A-Z (alpha) | 
		/// ~Desc: latest first (date), Z-A (alpha)
		/// </summary>
		enum class MapSort
		{
			CreatedAsc, CreatedDesc,
			LastEditAsc, LastEditDesc,
			AlphaAsc, AlphaDesc 
		};

		//---------------------

		class Atlas
		{
		public:
			Atlas() = default;

			bool Load(const std::filesystem::path& relPath);
			bool CreateMap(const std::string& name);
			bool DeleteMap(const std::string& name);
			bool OpenMap(const std::string& name);

			void UpdateActiveMap(); // active - the one currently on screen

			void SortMaps(MapSort by);
			bool RenameMap(const std::string& name, const std::string& newName);

		private:
			bool UpdateLastEditTime(const std::string& name);
			std::optional<MapData&> GetMapByName(const std::string& name);

		private:
			MapSort currentSort = MapSort::LastEditDesc;	// need for re-sorting on creation/deletion
			std::vector<MapData> maps;
			Map* activeMap = nullptr;
		};
	}
}