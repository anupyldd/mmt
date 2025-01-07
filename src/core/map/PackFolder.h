#pragma once

#include <string>
#include <map>
#include <memory>
#include <filesystem>
#include <optional>

#include "Resources.h"
#include "../../utility/Zip.h"

#include "log/loguru.hpp"

namespace mmt
{
	namespace core
	{

		template<class ResType>
		struct PackFolder
		{
			std::string name;
			std::map<std::string, std::shared_ptr<ResType>> res;
			std::map<std::string, std::shared_ptr<PackFolder>> subFolders;
		};
		
	}
}
