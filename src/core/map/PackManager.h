#pragma once

#include "../../utility/Defines.h"
#include "Pack.h"

#include <filesystem>
#include <map>
#include <vector>

namespace mmt
{
	namespace core
	{
		class PackManager
		{
			MMT_SINGLETON(PackManager);

		public:
			void SetSearchPath(const std::filesystem::path& rel);
			void LoadAll();
			void PreLoadAll();
			void ClearAll();

			const std::map<std::string, Pack>& GetPackList() const;

		private:
			std::filesystem::path path;
			std::map<std::string, Pack> packs;
		};
	}
}