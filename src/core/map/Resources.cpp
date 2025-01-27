#include "Resources.h"
#include "../../utility/StringUtil.h"

namespace mmt
{
	namespace core
	{
		bool IsSupportedImageFormat(const std::string& ext)
		{
			if (ext == ".png" ||
				ext == ".jpg" ||
				ext == ".jpeg" ||
				ext == ".tga" ||
				ext == ".tiff") return true;
			return false;
		}
		bool IsSupportedFontFormat(const std::string& ext)
		{
			if (ext == ".ttf" || ext == ".otf") return true;
			return false;
		}
		void MmtTexture::Load(util::Zip& zip, const std::string& name)
		{
			try
			{
				std::string data = zip.Read(name);
				const unsigned char* fileData = reinterpret_cast<const unsigned char*>(data.data());
				int dataSize = static_cast<int>(data.size());
				raylib::Image img = LoadImageFromMemory(util::GetExtension(name).c_str(), fileData, dataSize);
				if (!IsImageValid(img))
				{
					LOG_F(ERROR, "Failed to load texture [%s]: LoadImageFromMemory() failure", name.c_str());
					return;
				}
				tex.Load(img);
				if (!tex.IsValid())
				{
					LOG_F(ERROR, "Failed to load texture [%s]: LoadTextureFromImage() failure", name.c_str());
					return;
				}
				DLOG_F(INFO, "Loaded texture [%s]", name.c_str());
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, "Exception while loading texture [%s]: %s", name.c_str(), e.what());
			}
		}
		const raylib::Texture2D& MmtTexture::GetPreview()
		{
			return tex;
		}
		void MmtObject::Load(util::Zip& zip, const std::string& name)
		{
			try
			{
				std::string data = zip.Read(name);
				const unsigned char* fileData = reinterpret_cast<const unsigned char*>(data.data());
				int dataSize = static_cast<int>(data.size());
				Image img = LoadImageFromMemory(util::GetExtension(name).c_str(), fileData, dataSize);
				if (!IsImageValid(img))
				{
					LOG_F(ERROR, "Failed to load object [%s]: LoadImageFromMemory() failure", name.c_str());
					return;
				}
				obj.Load(img);
				if (!obj.IsValid())
				{
					LOG_F(ERROR, "Failed to load object [%s]: LoadTextureFromImage() failure", name.c_str());
					return;
				}
				DLOG_F(INFO, "Loaded object [%s]", name.c_str());
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, "Exception while loading object [%s]: %s", name.c_str(), e.what());
			}
		}
		const raylib::Texture2D& MmtObject::GetPreview()
		{
			return obj;
		}
		void MmtFont::Load(util::Zip& zip, const std::string& name)
		{
			try
			{
				std::string data = static_cast<std::ostringstream&>(zip.Open(name)).str();
				const unsigned char* fileData = reinterpret_cast<const unsigned char*>(data.data());
				int dataSize = static_cast<int>(data.size());
				fnt.Load(util::GetExtension(name).c_str(), fileData, dataSize, 96, nullptr, 0);
				if (!fnt.IsValid())
				{
					LOG_F(ERROR, "Failed to load font [%s]: LoadFontFromMemory() failure", name.c_str());
					return;
				}
				DLOG_F(INFO, "Loaded font [%s]", name.c_str());
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, "Exception while loading font [%s]: %s", name.c_str(), e.what());
			}
		}
		const raylib::Texture2D& MmtFont::GetPreview()
		{
			return fnt.GetTexture();
		}
	}
}