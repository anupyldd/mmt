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
			ClearAll();
			for (auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.path().extension() != ".mmtres") continue;
				
				packs[entry.path().stem().string()].Load(entry.path());
			}
		}
		void PackManager::PreLoadAll()
		{
			ClearAll();
			for (auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.path().extension() != ".mmtres") continue;

				packs[entry.path().stem().string()].PreLoad(entry.path());
			}
		}
		void PackManager::ClearAll()
		{
			for (auto& p : packs)
			{
				p.second.Clear();
			}
			packs.clear();
		}
		const std::map<std::string, Pack>& PackManager::GetPackList() const
		{
			return packs;
		}
	}
}