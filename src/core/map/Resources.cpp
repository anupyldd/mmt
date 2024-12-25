#include "Resources.h"

namespace mmt
{
	namespace core
	{
		/*
		Folder& AddSubFolder(Folder& current, const std::string& sfName)
		{
			auto& sf = current.subFolders[sfName];
			if (sf.name.empty()) sf.name = sfName;
			return sf;
		}
		*/
		bool IsSupportedImageFormat(const std::filesystem::path& path)
		{
			if (path.extension() == ".png" ||
				path.extension() == ".jpg" ||
				path.extension() == ".jpeg" ||
				path.extension() == ".tga" ||
				path.extension() == ".tiff") return true;
			return false;
		}
		bool IsSupportedFontFormat(const std::filesystem::path& path)
		{
			if (path.extension() == ".ttf" || path.extension() == ".otf") return true;
			return false;
		}
		ResourceType GetResourceType(const std::filesystem::path& path)
		{
			std::string ps = path.string();
			if (ps.starts_with("textures") && IsSupportedImageFormat(path))
			{
				return ResourceType::Texture;
			}
			else if (ps.starts_with("objects") && IsSupportedImageFormat(path))
			{
				return ResourceType::Object;
			}
			else if (ps.starts_with("fonts") && IsSupportedFontFormat(path))
			{
				return ResourceType::Font;
			}
			else return ResourceType::None;
		}
		/*
		void Pack::Unload()
		{
			if (loaded)
			{
				textures.Unload();
				objects.Unload();
				fonts.Unload();

				loaded = false;
			}
		}
		void Folder::Unload()
		{
			textures.clear();
			objects.clear();
			fonts.clear();

			for (auto& sf : subFolders)
			{
				sf.second.Unload();
			}
		}
		*/
	}
}