#include "Resources.h"

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
	}
}