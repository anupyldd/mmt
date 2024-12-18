#include "App.h"

#include "log/loguru.hpp"

namespace mmt
{
	namespace core
	{
		App::App()
			: fsm(this)
		{
		}
		void App::Init()
		{
			
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
				if(fsm.IsInState(&mainMenuState)) fsm.ChangeState(&mapEditState);
			}
			break;

			default: break;
			}
		}
	}
}