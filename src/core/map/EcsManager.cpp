#define PICO_ECS_MAX_COMPONENTS 32
#define PICO_ECS_MAX_SYSTEMS 16

#define PICO_ECS_IMPLEMENTATION

#include "EcsManager.h"

namespace hnd
{
	namespace core
	{
		void EcsManager::Init(EntityDensity mapSize)
		{
			auto& conf = Config::GetInstance().map;

			switch (mapSize)
			{
			case EntityDensity::Low:
				ecs = ecs_new(conf->maxEntityNumberLow, NULL);
				break;
			case EntityDensity::Medium:
				ecs = ecs_new(conf->maxEntityNumberMedium, NULL);
				break;
			case EntityDensity::High:
				ecs = ecs_new(conf->maxEntityNumberHigh, NULL);
				break;
			default: 
				ecs = ecs_new(conf->maxEntityNumberMedium, NULL);
				break;
			}

			RegisterCommon();
		}
		EcsManager::~EcsManager()
		{
			ecs_free(ecs);
		}
		void EcsManager::Reset()
		{
			ecs_reset(ecs);
		}
		void EcsManager::RegisterCommon()
		{
			LOG_DBG("TODO: RegisterCommon()");
		}
		void EcsManager::Update(double dt)
		{
			// some systems will probably be updated manually? like saving maybe?
			ecs_update_systems(ecs, dt);
		}
		
		void EcsManager::SystemRegister(
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
				LOG_ERROR(std::format("Cannot register system {}: this name is already taken", name));
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
		void EcsManager::SystemRequireComponents(const std::string& name, std::initializer_list<std::string_view> comps)
		{
			SystemId id = systems.at(name);

			for (auto& c : comps)
			{
				ecs_require_component(ecs, id, components.at(std::string(c)));
			}
		}
		void EcsManager::SystemExcludeComponent(const std::string& name, std::initializer_list<std::string_view> comps)
		{
			SystemId id = systems.at(name);

			for (auto& c : comps)
			{
				ecs_exclude_component(ecs, id, components.at(std::string(c)));
			}
		}
	}
}