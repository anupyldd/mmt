#pragma once

#include <string>
#include <map>
#include <memory>
#include <filesystem>
#include <iostream>
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
			std::map<std::string, std::shared_ptr<PackFolder<ResType>>> subFolders;

			void Print() const
			{
				std::cout << "Folder name: " << name << '\n';
				for (const auto& r : res)
				{
					std::cout << r.first << " - " << r.second.get();
				}
				for (const auto& sf : subFolders)
				{
					sf.second->Print();
				}
			}
		};
		
	}
}
