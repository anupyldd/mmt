#include "PackManager.h"

namespace mmt
{
	namespace core
	{
		void PackManager::SetSearchPath(const std::filesystem::path& rel)
		{
			path = std::filesystem::path() / rel;
		}
		void PackManager::LoadAll()
		{
			for (auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.path().extension() != ".mmtres") continue;
				
				packs.emplace_back();
				packs.back().Load(entry.path());
			}
		}
		void PackManager::PreLoadAll()
		{
			for (auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.path().extension() != ".mmtres") continue;

				packs.emplace_back();
				packs.back().PreLoad(entry.path());
			}
		}
	}
}