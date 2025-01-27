#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <filesystem>
#include <cstdint>
#include <variant>

#include "../../utility/Zip.h"

#include "raylib-cpp.hpp"
#include "log/loguru.hpp"

namespace mmt
{
	namespace core
	{
		enum class ResourceType { Texture, Object, Font, Script, None };

		struct MmtResource
		{
			virtual ~MmtResource() = default;

			virtual void Load(util::Zip& zip, const std::string& name) = 0;
			virtual const raylib::Texture2D& GetPreview() = 0;
		};

		struct MmtTexture : public MmtResource
		{
			raylib::Texture2D tex;
			
			MmtTexture() = default;
			MmtTexture(const Texture2D& src) { tex = src; }
			MmtTexture(const std::string& path)
			{
				raylib::Image img(path);
				tex.Load(img);
			}
			bool IsValid() const { return tex.IsValid(); }

			virtual void Load(util::Zip& zip, const std::string& name) override final;
			virtual const raylib::Texture2D& GetPreview() override final;
		};

		struct MmtObject : public MmtResource
		{
			raylib::Texture2D obj;

			MmtObject() = default;
			MmtObject(const Texture2D& src) { obj = src; }
			MmtObject(const std::string& path)
			{
				raylib::Image img(path);
				obj.Load(img);
			}
			bool IsValid() const { return obj.IsValid(); }

			virtual void Load(util::Zip& zip, const std::string& name) override final;
			virtual const raylib::Texture2D& GetPreview() override final;
		};

		struct MmtFont : public MmtResource
		{
			raylib::Font fnt;

			MmtFont() = default;
			MmtFont(const Font& src) { fnt = src; }
			MmtFont(const std::string& path) { fnt.Load(path); }
			bool IsValid() const { return fnt.IsValid(); }
		
			virtual void Load(util::Zip& zip, const std::string& name) override final;
			virtual const raylib::Texture2D& GetPreview() override final;
		};

		struct MmtScript : public MmtResource
		{
			virtual void Load(util::Zip& zip, const std::string& name) override final { }
			virtual const raylib::Texture2D& GetPreview() override final { return raylib::Texture2D(); }
		};

		// ------------------------------------------

		bool IsSupportedImageFormat(const std::string& ext);

		bool IsSupportedFontFormat(const std::string& ext);		
	}
}