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

					ResourceType type;
					if (name.starts_with("textures")) type = ResourceType::Texture;
					else if (name.starts_with("objects")) type = ResourceType::Object;
					else if (name.starts_with("fonts")) type = ResourceType::Font;
					else if (name.starts_with("scripts")) type = ResourceType::Script;
					else
					{
						LOG_F(ERROR, "Failed to load resource [%s] from pack [%s]: cannot determine type of resource",
							name.c_str(), path.filename().string().c_str());
						continue;
					}

					LoadResource(type, file, name, false);
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

					ResourceType type;
					if (name.starts_with("textures")) type = ResourceType::Texture;
					else if (name.starts_with("objects")) type = ResourceType::Object;
					else if (name.starts_with("fonts")) type = ResourceType::Font;
					else if (name.starts_with("scripts")) type = ResourceType::Script;
					else
					{
						LOG_F(ERROR, "Failed to preload resource [%s] from pack [%s]: cannot determine type of resource",
							name.c_str(), path.filename().string().c_str());
						continue;
					}

					LoadResource(type, *zip, name, true);
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

		void Pack::LoadResource(ResourceType type, util::Zip& zip, const std::string& name, bool preload)
		{
			auto parts = util::SplitByDelimiter(name, '/');
			if (parts.size() == 0)
			{
				LOG_F(ERROR, "Failed to load resource [%s]: resource path could not be split",
					name.c_str());
				return;
			}
			parts.erase(parts.begin()); // remove first part since type is already known

			switch (type)
			{
			case ResourceType::Texture:
			{
				if (!IsSupportedImageFormat(util::GetExtension(name)))
				{
					LOG_F(ERROR, "Failed to load texture [%s]: image format [%s] is not supported",
						name.c_str(), util::GetExtension(name).c_str());
					return;
				}
				PackFolder<MmtTexture>* currentFolder = &textures;
				for (size_t i = 0; i < parts.size(); ++i)
				{
					if (i == parts.size() - 1)
					{
						if(!preload)
							currentFolder->res[util::RemoveExtension(parts[i])] =
							std::make_shared<MmtTexture>(std::move(LoadTexture(zip, name)));
						else
						{
							currentFolder->res[util::RemoveExtension(parts[i])] =
								std::make_shared<MmtTexture>();
							LOG_F(INFO, "Pre-Loaded texture [%s]", name.c_str());
						}
					}
					else
					{
						if (currentFolder->subFolders.contains(parts[i]))
						{
							currentFolder = currentFolder->subFolders.at(parts[i]).get();
						}
						else
						{
							currentFolder->subFolders[parts[i]] = std::make_shared<PackFolder<MmtTexture>>();
							auto sfp = currentFolder->subFolders[parts[i]];
							sfp->name = parts[i];
							currentFolder = sfp.get();
						}
					}
				}
				break;
			}
			case ResourceType::Object:
			{
				if (!IsSupportedImageFormat(util::GetExtension(name)))
				{
					LOG_F(ERROR, "Failed to load object [%s]: image format [%s] is not supported",
						name.c_str(), util::GetExtension(name).c_str());
					return;
				}
				PackFolder<MmtObject>* currentFolder = &objects;
				for (size_t i = 0; i < parts.size(); ++i)
				{
					if (i == parts.size() - 1)
					{
						if (!preload)
							currentFolder->res[util::RemoveExtension(parts[i])] =
							std::make_shared<MmtObject>(std::move(LoadObject(zip, name)));
						else
						{
							currentFolder->res[util::RemoveExtension(parts[i])] =
								std::make_shared<MmtObject>();
							LOG_F(INFO, "Pre-Loaded object [%s]", name.c_str());
						}
					}
					else
					{
						if (currentFolder->subFolders.contains(parts[i]))
						{
							currentFolder = currentFolder->subFolders.at(parts[i]).get();
						}
						else
						{
							currentFolder->subFolders[parts[i]] = std::make_shared<PackFolder<MmtObject>>();
							auto sfp = currentFolder->subFolders[parts[i]];
							sfp->name = parts[i];
							currentFolder = sfp.get();
						}
					}
				}
				break;
			}
			case ResourceType::Font:
			{
				if (!IsSupportedFontFormat(util::GetExtension(name)))
				{
					LOG_F(ERROR, "Failed to load font [%s]: font format [%s] is not supported",
						name.c_str(), util::GetExtension(name).c_str());
					return;
				}
				PackFolder<MmtFont>* currentFolder = &fonts;
				for (size_t i = 0; i < parts.size(); ++i)
				{
					if (i == parts.size() - 1)
					{
						if (!preload)
						{
							MmtFont fnt = LoadFont(zip, name);
							currentFolder->res[util::RemoveExtension(parts[i])] =
								std::make_shared<MmtFont>(std::move(fnt));
						}
						else
						{
							currentFolder->res[util::RemoveExtension(parts[i])] =
								std::make_shared<MmtFont>();
							LOG_F(INFO, "Pre-Loaded font [%s]", name.c_str());
						}
					}
					else
					{
						if (currentFolder->subFolders.contains(parts[i]))
						{
							currentFolder = currentFolder->subFolders.at(parts[i]).get();
						}
						else
						{
							currentFolder->subFolders[parts[i]] = std::make_shared<PackFolder<MmtFont>>();
							auto sfp = currentFolder->subFolders[parts[i]];
							sfp->name = parts[i];
							currentFolder = sfp.get();
						}
					}
				}
				break;
			}
			case ResourceType::Script:
			{
				LOG_F(WARNING, "Scripts are not yet implemented");
				break;
			}
			case ResourceType::None:
			default: break;
			}
		}

		MmtTexture Pack::LoadTexture(util::Zip& zip, const std::string& name)
		{
			try
			{
				std::string data = zip.Read(name);
				const unsigned char* fileData = reinterpret_cast<const unsigned char*>(data.data());
				int dataSize = static_cast<int>(data.size());
				Image img = LoadImageFromMemory(util::GetExtension(name).c_str(), fileData, dataSize);
				if (!IsImageValid(img))
				{
					LOG_F(ERROR, "Failed to load resource [%s]: LoadImageFromMemory() failure", name.c_str());
					return MmtTexture();
				}
				MmtTexture tex(LoadTextureFromImage(img));
				if (!tex.IsValid())
				{
					LOG_F(ERROR, "Failed to load resource [%s]: LoadTextureFromImage() failure", name.c_str());
					return MmtTexture();
				}
				UnloadImage(img);
				DLOG_F(INFO, "Loaded texture [%s]", name.c_str());
				return tex;
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, "Exception while loading texture [%s]: %s", name.c_str(), e.what());
			}
		}

		MmtObject Pack::LoadObject(util::Zip& zip, const std::string& name)
		{
			try
			{
				std::string data = zip.Read(name);
				const unsigned char* fileData = reinterpret_cast<const unsigned char*>(data.data());
				int dataSize = static_cast<int>(data.size());
				Image img = LoadImageFromMemory(util::GetExtension(name).c_str(), fileData, dataSize);
				if (!IsImageValid(img))
				{
					LOG_F(ERROR, "Failed to load resource [%s]: LoadImageFromMemory() failure", name.c_str());
					return MmtObject();
				}
				MmtObject obj(LoadTextureFromImage(img));
				if (!obj.IsValid())
				{
					LOG_F(ERROR, "Failed to load resource [%s]: LoadTextureFromImage() failure", name.c_str());
					return MmtObject();
				}
				UnloadImage(img);
				DLOG_F(INFO, "Loaded texture [%s]", name.c_str());
				return obj;
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, "Exception while loading texture [%s]: %s", name.c_str(), e.what());
			}
		}

		MmtFont Pack::LoadFont(util::Zip& zip, const std::string& name)
		{
			try
			{
				std::string data = static_cast<std::ostringstream&>(zip.Open(name)).str();
				const unsigned char* fileData = reinterpret_cast<const unsigned char*>(data.data());
				int dataSize = static_cast<int>(data.size());
				MmtFont font(LoadFontFromMemory(util::GetExtension(name).c_str(), fileData, dataSize, 96, nullptr, 0));
				if (!font.IsValid())
				{
					LOG_F(ERROR, "Failed to load resource [%s]: LoadFontFromMemory() failure", name.c_str());
					return MmtFont();
				}
				DLOG_F(INFO, "Loaded font [%s]", name.c_str());
				return font;
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, "Exception while loading font [%s]: %s", name.c_str(), e.what());
			}
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
