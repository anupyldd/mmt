#include "Pack.h"
#include "../../utility/Zip.h"
#include "../../utility/StringUtil.h"
#include "../Localization.h"

#include "log/loguru.hpp"

namespace mmt
{
	namespace core
	{

		void Pack::Load(const std::filesystem::path& path)
		{
			try
			{
				LOG_F(INFO, "Attempting to load pack at [%s]", path.string().c_str());

				name = path.stem().string();
				textures.name = LocC("textures");
				objects.name = LocC("objects");
				fonts.name = LocC("fonts");

				util::Zip file;
				file.Load(path);

				const auto& names = file.NameList();
				for (const auto& name : names)
				{
					if (name.ends_with('/') || name.ends_with("txt") || name.ends_with("json")) 
						continue;	// don't load folder names or non-resource files

					if (name.starts_with("textures")) LoadResource<MmtTexture>(file, name, false);
					else if (name.starts_with("objects")) LoadResource<MmtObject>(file, name, false);
					else if (name.starts_with("fonts")) LoadResource<MmtFont>(file, name, false);
					else if (name.starts_with("scripts")) LoadResource<MmtScript>(file, name, false);
					else
					{
						LOG_F(ERROR, "Failed to load resource [%s] from pack [%s]: cannot determine type of resource",
							name.c_str(), path.filename().string().c_str());
						continue;
					}
				}
				state = PackState::Loaded;
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, "Error loading pack [%s]: %s", path.string().c_str(), e.what());
			}
		}

		void Pack::PreLoad(const std::filesystem::path& path)
		{
			try
			{
				LOG_F(INFO, "Attempting to pre-load pack at [%s]", path.string().c_str());

				name = path.stem().string();
				textures.name = LocC("textures");
				objects.name = LocC("objects");
				fonts.name = LocC("fonts");

				zip = std::make_unique<util::Zip>();
				zip->Load(path);
				const auto& names = zip->NameList();
				for (const auto& name : names)
				{
					if (name.ends_with('/') || name.ends_with("txt") || name.ends_with("json"))
						continue;	// don't preload folder names or non-resource files

					if (name.starts_with("textures")) LoadResource<MmtTexture>(*zip, name, true);
					else if (name.starts_with("objects")) LoadResource<MmtObject>(*zip, name, true);
					else if (name.starts_with("fonts")) LoadResource<MmtFont>(*zip, name, true);
					else if (name.starts_with("scripts")) LoadResource<MmtScript>(*zip, name, true);
					else
					{
						LOG_F(ERROR, "Failed to load resource [%s] from pack [%s]: cannot determine type of resource",
							name.c_str(), path.filename().string().c_str());
						continue;
					}
				}
				state = PackState::Scanned;
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, "Error preloading pack [%s]: %s", path.string().c_str(), e.what());
			}
		}

		void Pack::Clear()
		{
			textures.Clear();
			objects.Clear();
			fonts.Clear();
			if(zip) zip->Reset();
			state = PackState::Unloaded;
		}
		
		std::string Pack::GetStats() const
		{
			return std::format("tex count [{}], obj count [{}], fnt count [{}]",
				textures.Count(), objects.Count(), fonts.Count());
		}

		PackState Pack::GetState() const
		{
			return state;
		}

		void Pack::PrintLoadedResources() const
		{
			textures.Print();
			objects.Print();
			fonts.Print();
		}
		const PackFolder<MmtTexture>& Pack::GetTextureFolder() const
		{
			return textures;
		}
		const PackFolder<MmtObject>& Pack::GetObjectFolder() const
		{
			return objects;
		}
		const PackFolder<MmtFont>& Pack::GetFontFolder() const
		{
			return fonts;
		}
	}
}
