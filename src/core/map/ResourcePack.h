#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <cstdint>

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

		struct Folder
		{
			std::string name;
			std::map<std::string, Folder> subFolders;
			
			std::map<std::string, Resource<Texture2D>> textures;
			std::map<std::string, Resource<Texture2D>> objects;
			std::map<std::string, Resource<Font>> fonts;

		public:

			void Unload()
			{
				textures.clear();
				objects.clear();
				fonts.clear();

				for (auto& sf : subFolders)
				{
					sf.second.Unload();
				}
			}
		};
		
		// ------------------------------------------

		struct Pack
		{
			Pack() = default;
			Pack(const std::string& name, bool shouldLoad)
				: name(name), shouldLoad(shouldLoad) { };

		public:

			bool shouldLoad = false;
			bool loaded = false;

			std::string 
				name			= "Undefined",
				author			= "Undefined",
				license			= "Undefined",
				version			= "Undefined",
				description		= "Undefined";

			Folder
				textures,
				objects,
				fonts;

		public:

			void Unload()
			{
				if (loaded)
				{
					textures.Unload();
					objects.Unload();
					fonts.Unload();

					loaded = false;
				}
			}
		};

		struct PackRegistry
		{
			std::map<std::string, bool> shouldLoad;
		};
	}
}