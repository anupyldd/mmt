#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <filesystem>
#include <cstdint>
#include <variant>

#include "raylib.h"
#include "log/loguru.hpp"

namespace mmt
{
	namespace core
	{
		enum class ResourceType { Texture, Object, Font, Script, None };

		template<class ResType>
		struct Resource
		{
			Resource() = default;
			Resource(std::shared_ptr<ResType> res)
				: res(res) { }

			std::shared_ptr<ResType> res;
		};

		struct MmtTexture
		{
			Texture2D tex = { 0 };

			MmtTexture() = default;
			MmtTexture(const MmtTexture& src) { tex = src.tex; }
			MmtTexture(const Texture2D& src) { tex = src; }
			MmtTexture(const std::string& path)
			{
				Image img = LoadImage(path.c_str());
				tex = LoadTextureFromImage(img);
				UnloadImage(img);
			}
			~MmtTexture() { UnloadTexture(tex); }
			bool IsValid() const { return IsTextureValid(tex); }
		};

		struct MmtObject 
		{
			Texture2D obj = { 0 };

			MmtObject() = default;
			MmtObject(MmtObject&& src) = default;
			MmtObject(const MmtObject& src) = default;
			explicit MmtObject(const Texture2D& src) { obj = src; }
			explicit MmtObject(const std::string& path)
			{
				Image img = LoadImage(path.c_str());
				obj = LoadTextureFromImage(img);
				UnloadImage(img);
			}
			~MmtObject() { UnloadTexture(obj); }
			bool IsValid() const { return IsTextureValid(obj); }
		};

		struct MmtFont
		{
			Font fnt;

			MmtFont() = default;
			MmtFont(const MmtFont& src) { fnt = src.fnt; }
			MmtFont(const Font& src) { fnt = src; }
			MmtFont(const std::string& path) { fnt = LoadFont(path.c_str()); }
			~MmtFont() { if (fnt.baseSize != 0) { UnloadFont(fnt); fnt.baseSize = 0; } }
			bool IsValid() const { return IsFontValid(fnt); }
		};

		struct MmtScript
		{
			// TODO
		};

		// ------------------------------------------

		bool IsSupportedImageFormat(const std::string& ext);

		bool IsSupportedFontFormat(const std::string& ext);

		ResourceType GetResourceType(const std::string& ext);
		
	}
}