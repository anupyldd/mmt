#define PICO_ECS_MAX_COMPONENTS 32
#define PICO_ECS_MAX_SYSTEMS 16

#define PICO_ECS_IMPLEMENTATION

#include "EcsInstance.h"

namespace mmt
{
	namespace core
	{
		void EcsInstance::Init(int maxEntityCount)
		{
			ecs = ecs_new(maxEntityCount, NULL);
			RegisterCommon();
		}
		EcsInstance::~EcsInstance()
		{
			ecs_free(ecs);
		}
		void EcsInstance::Reset()
		{
			ecs_reset(ecs);
		}
		void EcsInstance::Destroy()
		{
			ecs_free(ecs);
		}
		void EcsInstance::RegisterCommon()
		{
			MMT_LOG_DEBUG("TODO: Finish RegisterCommon()");

			using namespace components;

			ComponentRegister<Transform>(STR(Transform), TransformConstructor);
			ComponentRegister<Sprite>(STR(Sprite), SpriteConstructor);
			ComponentRegister<Culled>(STR(Culled), nullptr);

			SystemRegister(STR(RenderSpriteSystem), RenderSpriteSystem,
				{ STR(Transform), STR(Sprite) },
				{ STR(Culled) });
		}
		void EcsInstance::Update(double dt)
		{
			// some systems will probably be updated manually? like saving maybe?
			//ecs_update_systems(ecs, dt);
			ecs_update_system(ecs, systems["RenderSpriteSystem"], 0.0f);
		}

		void EcsInstance::Save(const std::filesystem::path& path)
		{
		}

		void EcsInstance::Load(const std::filesystem::path& path)
		{
		}

		Ecs* EcsInstance::GetEcs()
		{
			return ecs;
		}
		
		ComponentId EcsInstance::ComponentGetId(const std::string& name) const
		{
			try
			{
				return components.at(name);
			}
			catch (const std::exception& e)
			{
				MMT_LOG_ERROR(std::format("Failed to get ID of component {}: {}", name, e.what()));
				return ECS_NULL;
			}
		}

		void EcsInstance::SystemRegister(
			const std::string& name,
			SystemFuncPtr func,
			std::initializer_list<std::string_view> requireComps,
			std::initializer_list<std::string_view> excludeComps, 
			SystemAddCallbackPtr addCb, 
			SystemRemoveCallbackPtr removeCb, 
			void* cbData)
		{
			if (systems.contains(name))
			{
				MMT_LOG_ERROR(std::format("Cannot register system {}: this name is already taken", name));
				return;
			}

			SystemId id = ecs_register_system(ecs, func, addCb, removeCb, cbData);
			systems[name] = id;

			for (auto& c : requireComps)
			{
				ecs_require_component(ecs, id, components.at(std::string(c)));
			}
			for (auto& c : excludeComps)
			{
				ecs_exclude_component(ecs, id, components.at(std::string(c)));
			}
		}
		void EcsInstance::SystemRequireComponents(const std::string& name, std::initializer_list<std::string_view> comps)
		{
			SystemId id = systems.at(name);

			for (auto& c : comps)
			{
				ecs_require_component(ecs, id, components.at(std::string(c)));
			}
		}
		void EcsInstance::SystemExcludeComponent(const std::string& name, std::initializer_list<std::string_view> comps)
		{
			SystemId id = systems.at(name);

			for (auto& c : comps)
			{
				ecs_exclude_component(ecs, id, components.at(std::string(c)));
			}
		}
	}
}