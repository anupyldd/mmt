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
		namespace res
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
			/*
			struct Pack
			{
				Pack() = default;
				Pack(const std::string& name, bool shouldLoad)
					: name(name), shouldLoad(shouldLoad) { };

			public:

				bool shouldLoad = false;
				bool loaded = false;

				std::string
					name = "Undefined",
					author = "Undefined",
					license = "Undefined",
					version = "Undefined",
					description = "Undefined";

				Folder
					textures,
					objects,
					fonts;

			public:

				void Unload();
			};

			struct PackRegistry
			{
				std::map<std::string, bool> shouldLoad;
			};
			// --------------------------------------------

			Folder& AddSubFolder(Folder& current, const std::string& sfName);
			*/

			bool IsSupportedImageFormat(const std::filesystem::path& path);

			bool IsSupportedFontFormat(const std::filesystem::path& path);

			ResourceType GetResourceType(const std::filesystem::path& path);

			template<class ResType>
			void AddResource(Folder& folder, ResourceType type, const std::string& resName, const Resource<ResType>& res)
			{
				switch (type)
				{
				case ResourceType::Texture:
					folder.textures[resName] = res;
					break;
				case ResourceType::Object:
					folder.objects[resName] = res;
					break;
				case ResourceType::Font:
					folder.fonts[resName] = res;
					break;
				case ResourceType::Script:
					DLOG_F(WARNING, "Script loading is not yet implenented");
					break;
				case ResourceType::None:
				default:
					DLOG_F(WARNING, "Invalid resource type");
					break;
				}
			}

			void PopulateFolder(Folder& root, const std::vector<std::string>& entries);
		}
	}
}