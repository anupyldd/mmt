#pragma once

#include "../../utility/Defines.h"
#include "Pack.h"

#include <filesystem>
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

			

		private:
			std::filesystem::path path;
			std::vector<Pack> packs;
		};
	}
}