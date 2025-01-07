#include "Pack.h"
#include "../../utility/Zip.h"
#include "../../utility/StringUtil.h"

#include "log/loguru.hpp"

namespace mmt
{
	namespace core
	{

		void Pack::Load(const std::filesystem::path& path)
		{
			try
			{
				util::Zip file;
				file.Load(path);

				const auto& names = file.NameList();
				for (const auto& name : names)
				{
					auto parts = util::SplitByDelimiter(name, '/');
					if (parts.size() == 0)
					{
						LOG_F(ERROR, "Failed to load resource [%s] from pack [%s]: resource path could not be split",
							name.c_str(), path.filename().string().c_str());
					}

					ResourceType type;
					if (parts[0] == "textures") type = ResourceType::Texture;
					else if (parts[0] == "objects") type = ResourceType::Object;
					else if (parts[0] == "fonts") type = ResourceType::Font;
					else if (parts[0] == "scripts") type = ResourceType::Script;
					else
					{
						LOG_F(ERROR, "Failed to load resource [%s] from pack [%s]: cannot determine type of resource",
							name.c_str(), path.filename().string().c_str());
						continue;
					}

					parts.erase(parts.begin());
					LoadResource(type, file, parts);
				}
			}
			catch (const std::exception& e)
			{
				LOG_F(ERROR, "Error loading pack [%s]: %s", path.string().c_str(), e.what());
			}
		}

		void Pack::LoadResource(ResourceType type, util::Zip& zip, const std::vector<std::string>& parts)
		{
			switch (type)
			{
			case ResourceType::Texture:
			{
				
				break;
			}
			case ResourceType::Object:
			{

				break;
			}
			case ResourceType::Font:
			{

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

	}
}
