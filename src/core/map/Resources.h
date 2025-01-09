#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <filesystem>
#include <cstdint>
#include <variant>

#include "raylib.h"

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

		// ------------------------------------------

		struct PackRegistry
		{
			std::map<std::string, bool> shouldLoad;
		};

		bool IsSupportedImageFormat(const std::string& ext);

		bool IsSupportedFontFormat(const std::string& ext);

		ResourceType GetResourceType(const std::string& ext);
		
	}
}