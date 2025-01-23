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

		std::shared_ptr<Texture2D> Pack::GetTexture(const std::initializer_list<std::string>& path)
		{
			switch (state)
			{
			case PackState::Unloaded:
			{
				LOG_F(ERROR, "Trying to get texture [%s] from unloaded pack", path.end()->c_str());
				return std::shared_ptr<Texture2D>();
			}
			case PackState::Scanned:
			{
				break;
			}
			case PackState::Loaded:
			{
				auto& currentFolder = 
				for (const auto& p : path)
				{

				}
				break;
			}
			default: 
				return std::shared_ptr<Texture2D>();
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
				PackFolder<Texture2D>* currentFolder = &textures;
				for (size_t i = 0; i < parts.size(); ++i)
				{
					if (i == parts.size() - 1)
					{
						if(!preload)
							currentFolder->res[util::RemoveExtension(parts[i])] =
							std::make_shared<Texture2D>(std::move(LoadTexture(zip, name)));
						else
						{
							currentFolder->res[util::RemoveExtension(parts[i])] =
								std::make_shared<Texture2D>();
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
							currentFolder->subFolders[parts[i]] = std::make_shared<PackFolder<Texture2D>>();
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
				PackFolder<Texture2D>* currentFolder = &objects;
				for (size_t i = 0; i < parts.size(); ++i)
				{
					if (i == parts.size() - 1)
					{
						if (!preload)
							currentFolder->res[util::RemoveExtension(parts[i])] =
							std::make_shared<Texture2D>(std::move(LoadTexture(zip, name)));
						else
						{
							currentFolder->res[util::RemoveExtension(parts[i])] =
								std::make_shared<Texture2D>();
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
							currentFolder->subFolders[parts[i]] = std::make_shared<PackFolder<Texture2D>>();
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
				PackFolder<Font>* currentFolder = &fonts;
				for (size_t i = 0; i < parts.size(); ++i)
				{
					if (i == parts.size() - 1)
					{
						if(!preload)
							currentFolder->res[util::RemoveExtension(parts[i])] =
							std::make_shared<Font>(LoadFont(zip, name));
						else
						{
							currentFolder->res[util::RemoveExtension(parts[i])] =
								std::make_shared<Font>();
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
							currentFolder->subFolders[parts[i]] = std::make_shared<PackFolder<Font>>();
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

		Texture2D Pack::LoadTexture(util::Zip& zip, const std::string& name)
		{
			try
			{
				//auto& ostr = zip.Open(name);
				//std::string data = static_cast<std::ostringstream&>(zip.Open(name)).str();
				std::string data = zip.Read(name);
				const unsigned char* fileData = reinterpret_cast<const unsigned char*>(data.data());
				int dataSize = static_cast<int>(data.size());
				Image img = LoadImageFromMemory(util::GetExtension(name).c_str(), fileData, dataSize);
				if (!IsImageValid(img))
				{
					LOG_F(ERROR, "Failed to load resource [%s]: LoadImageFromMemory() failure", name.c_str());
					return Texture2D();
				}
				Texture2D tex = LoadTextureFromImage(img);
				if (!IsTextureValid(tex))
				{
					LOG_F(ERROR, "Failed to load resource [%s]: LoadTextureFromImage() failure", name.c_str());
					return Texture2D();
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

		Font Pack::LoadFont(util::Zip& zip, const std::string& name)
		{
			try
			{
				std::string data = static_cast<std::ostringstream&>(zip.Open(name)).str();
				const unsigned char* fileData = reinterpret_cast<const unsigned char*>(data.data());
				int dataSize = static_cast<int>(data.size());
				Font font = LoadFontFromMemory(util::GetExtension(name).c_str(), fileData, dataSize, 96, nullptr, 0);
				if (!IsFontValid(font))
				{
					LOG_F(ERROR, "Failed to load resource [%s]: LoadFontFromMemory() failure", name.c_str());
					return Font();
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
		const PackFolder<Texture2D>& Pack::GetTextureFolder() const
		{
			return textures;
		}
		const PackFolder<Texture2D>& Pack::GetObjectFolder() const
		{
			return objects;
		}
		const PackFolder<Font>& Pack::GetFontFolder() const
		{
			return fonts;
		}
	}
}
