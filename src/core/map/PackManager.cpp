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
		void PackManager::LoadSelected(const std::unordered_map<std::string, bool>& sel)
		{
			for (auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.path().extension() != ".mmtres") continue;

				std::string stem = entry.path().stem().string();
				if (sel.contains(stem) && sel.at(stem))
				{
					packs[stem].Load(entry.path());
				}
			}
		}
		void PackManager::PreLoadSelected(const std::unordered_map<std::string, bool>& sel)
		{
			for (auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.path().extension() != ".mmtres") continue;

				std::string stem = entry.path().stem().string();
				if (sel.contains(stem) && sel.at(stem))
				{
					packs[stem].PreLoad(entry.path());
				}
			}
		}
		void PackManager::ClearSelected(const std::unordered_map<std::string, bool>& sel)
		{
			for (auto& p : packs)
			{
				if (sel.contains(p.first) && sel.at(p.first))
					p.second.Clear();
			}
		}
		void PackManager::FindAvailable()
		{
			for (auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.path().extension() != ".mmtres") continue;

				packs[entry.path().stem().string()];
			}
		}
		const std::map<std::string, Pack>& PackManager::GetPackList() const
		{
			return packs;
		}
	}
}