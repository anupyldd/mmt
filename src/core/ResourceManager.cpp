#include "ResourceManager.h"

#include "raylib.h"
#include "log/loguru.hpp"

namespace mmt
{
	namespace core
	{
		void ResourceManager::View()
		{
			DLOG_F(INFO, "Checking available packs at %s", packPath.string().c_str());

			std::ifstream reg(packPath);
			PackRegistry pr = rfl::json::read<PackRegistry>(reg).value();

			for (const auto& e : std::filesystem::directory_iterator(packPath))
			{
				if (e.is_regular_file() && e.path().extension() == ".mmtres")
				{
					std::string stem = e.path().stem().string();
					packs[stem] = Pack(stem, pr.shouldLoad.at(stem));
				}
			}
		}
		const std::unordered_map<std::string, Pack>& ResourceManager::GetPackMap() const
		{
			return packs;
		}
		void ResourceManager::LoadApp()
		{
			auto path = std::filesystem::current_path() / "data" / "resources" / "app";

			DLOG_F(INFO, "Loading app resources at %s", path.string().c_str());
			
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.path().extension().string() == ".ttf")
				{
					defaultFont = LoadFont(entry.path().string().c_str());
				}
				else if (entry.path().extension().string() == ".png")
				{
					appIcon = LoadImage(entry.path().string().c_str());
				}
			}
			if (!IsFontValid(defaultFont)) LOG_F(ERROR, "Invalid default font");
			if (IsImageValid(appIcon)) SetWindowIcon(appIcon);
		}
	}
}