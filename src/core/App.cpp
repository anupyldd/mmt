#include "App.h"
#include "ResourceManager.h"

#include "log/loguru.hpp"
#include "physfs.h"

#include <filesystem>

namespace mmt
{
	namespace core
	{
		App::App()
			: fsm(this)
		{
		}
		App::~App()
		{
			//PHYSFS_deinit();
		}
		void App::Init(int argc, char** argv)
		{
			loguru::init(argc, argv);
			//PHYSFS_init(argv[0]);
			//
			//const std::filesystem::path writeDir = std::filesystem::current_path() / "data" / "maps";
			//PHYSFS_setWriteDir(writeDir.string().c_str());
			
		}
		void App::Run()
		{
			DLOG_F(INFO, "App is now running");

			appGui.mainMenu.AddObserver(this);
			fsm.SetCurrentState(&initLoadState);

			while(true) fsm.Update();
		}
		util::StateMachine<App>& App::GetFsm()
		{
			return fsm;
		}
		gui::Gui& App::GetGui()
		{
			return appGui;
		}
		void App::UpdateConfig() const
		{
			auto& conf = Config::GetInstance();

			conf.settings->appWidth = GetScreenWidth();
			conf.settings->appHeight = GetScreenHeight();
			conf.settings->appPosX = GetWindowPosition().x;
			conf.settings->appPosY = GetWindowPosition().y;
		}

		void App::OnNotify(const Event& evt)
		{
			using namespace util;

			switch (evt.type)
			{
			case EventType::GUI_FROM_MAIN_TO_EDIT:
			{
				if (fsm.IsInState(&mainMenuState))
				{
					//ResourceManager::GetInstance().Load();
					fsm.ChangeState(&mapEditState);
				}
			}
			break;

			default: break;
			}
		}
	}
}