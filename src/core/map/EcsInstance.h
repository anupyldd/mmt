#pragma once

#include <memory>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <exception>
#include <unordered_map>
#include <utility>
#include <string_view>
#include <filesystem>

#include "../../utility/Log.h"
#include "../Config.h"
#include "EcsTypes.h"
#include "Components.h"
#include "Ecs.h"

namespace hnd
{
	namespace core
	{
		using namespace components;

		class EcsInstance
		{
		public:
			~EcsInstance();

			// sets default parameters (including registering common things)
			void Init(int maxEntityCount);
			
			// removes all entities from the ECS, preserving systems and components.
			void Reset();

			void Destroy();

			// registeres components and systems that are common for all instances
			void RegisterCommon();

			// updates all systems
			void Update(double dt = 0.0);

			void Save(const std::filesystem::path& path);
			void Load(const std::filesystem::path& path);

		public: 

			template<class CompType>
			void ComponentRegister(const std::string& name, ConstructorPtr ctor = nullptr, DestructorPtr dtor = nullptr);

			ComponentId ComponentGetId(const std::string& name) const;

		public:

			void SystemRegister(
				const std::string& name, 
				SystemFuncPtr func,
				std::initializer_list<std::string_view> requireComps = {},
				std::initializer_list<std::string_view> excludeComps = {},
				SystemAddCallbackPtr addCb = nullptr, 
				SystemRemoveCallbackPtr removeCb = nullptr,
				void* cbData = nullptr);
			void SystemRequireComponents(const std::string& name, std::initializer_list<std::string_view> comps);
			void SystemExcludeComponent(const std::string& name, std::initializer_list<std::string_view> comps);

		private:
			Ecs* ecs = nullptr;

			std::unordered_map<std::string, ComponentId> components;
			std::unordered_map<std::string, SystemId> systems;
		};	

		// -------------------------------------------------------------------
		// -------------------------------------------------------------------
		// -------------------------------------------------------------------

		template<class CompType>
		inline void EcsInstance::ComponentRegister(const std::string& name, ConstructorPtr ctor, DestructorPtr dtor)
		{
			if (components.contains(name))
			{
				HND_LOG_INFO(std::format("Cannot register component {}: this name is already taken", name));
				return;
			}

			components[name] = ecs_register_component(ecs, sizeof(CompType), ctor, dtor);
		}

	}
}