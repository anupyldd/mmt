#include "ResourceManager.h"

#include "raylib.h"
#include "log/loguru.hpp"
/*
namespace mmt
{
	namespace core
	{
		ResourceManager::~ResourceManager()
		{
			Unload();
		}
		void ResourceManager::PreLoad()
		{
			LOG_F(INFO, "Checking available packs at %s", packPath.string().c_str());

			// load in pack registry to access info about what should be loaded
			LoadPackRegistry();

			std::vector<std::string> existingPacks;

			for (const auto& e : std::filesystem::directory_iterator(packPath))
			{
				if (e.is_regular_file() && e.path().extension() == ".mmtres")
				{
					std::string stem = e.path().stem().string();
					//packs[stem] = Pack(stem, packReg->shouldLoad.at(stem));
					packs.emplace(stem, PackFolder(stem));
					// save what packs are in the folder
					existingPacks.push_back(stem);

					LOG_F(INFO, "Found pack: %s", stem.c_str());
				}
			}

			// check what packs are in the registry but not in the folder,
			// delete them from the registry
			for (auto it = packReg->shouldLoad.cbegin(); it != packReg->shouldLoad.cend(); )
			{
				if (std::ranges::find(existingPacks, it->first) == existingPacks.end())
				{
					LOG_F(INFO, "Removing pack from registry: %s", it->first);
					packReg->shouldLoad.erase(it++);
				}
				else ++it;
			}
		}
		const std::unordered_map<std::string, PackFolder>& ResourceManager::GetPackMap() const
		{
			return packs;
		}
		void ResourceManager::SetPackLoad(const std::string& pack, bool load)
		{
			LOG_F(INFO, "Set shouldLoad value of pack [%s] to [%s]", pack.c_str(), (load ? "true" : "false"));
			packReg->shouldLoad.at(pack) = load;
		}
		void ResourceManager::Load()
		{
			if (!packReg)
			{
				LOG_F(WARNING, "Cannot load resource packs: pack registry is not yet loaded");
				return;
			}

			LOG_F(INFO, "Started loading packs");

			for (const auto& e : std::filesystem::directory_iterator(packPath))
			{
				if (e.is_regular_file() && e.path().extension() == ".mmtres")
				{
					std::string stem = e.path().stem().string();
					if (packReg->shouldLoad.at(stem))
					{
						LOG_F(INFO, "Start loading pack: %s", stem.c_str());
						PackFolder& current = packs.at(stem);
						miniz_cpp::zip_file zip(e.path().string());
						for (const auto& f : zip.infolist())
						{
							current.LoadFile(f.filename, zip);
						}
					}
				}
			}
		}
		void ResourceManager::LoadApp()
		{
			auto path = std::filesystem::current_path() / "data" / "resources" / "app";

			LOG_F(INFO, "Loading app resources at %s", path.string().c_str());
			
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
		//
		//void ResourceManager::LoadPack(const std::filesystem::path& path)
		//{
		//	miniz_cpp::zip_file file(path.string());
		//	for (const auto& i : file.infolist())
		//	{
		//
		//		file.open(i);
		//	}
		//}
		
		void ResourceManager::LoadPackRegistry()
		{
			LOG_F(INFO, "Loading pack registry");

			try
			{
				packReg = std::make_unique<PackRegistry>();

				auto path = packPath / "pack_registry.json";
				std::ifstream reg(path);
				std::stringstream contents;
				contents << reg.rdbuf();
				(*packReg) = rfl::json::read<PackRegistry>(contents.str()).value();
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, e.what());
			}
		}
		void ResourceManager::SavePackRegistry()
		{
			LOG_F(INFO, "Saving pack registry");

			std::ofstream reg(packPath / "pack_registry.json");
			reg << rfl::json::write(*packReg, YYJSON_WRITE_PRETTY);
		}
	}
}*/