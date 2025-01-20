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
				
				packs[entry.path().stem().string()].Load(entry.path());
			}
		}
		void PackManager::PreLoadAll()
		{
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
		}
		const std::map<std::string, Pack>& PackManager::GetPackList() const
		{
			return packs;
		}
	}
}