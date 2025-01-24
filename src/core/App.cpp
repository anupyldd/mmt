#include "App.h"
#include "ResourceManager.h"

#include "log/loguru.hpp"

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
		}
		void App::Init(int argc, char** argv)
		{
			loguru::init(argc, argv);			
		}
		void App::Run()
		{
			DLOG_F(INFO, "App is now running");

			fsm.SetCurrentState(&initLoadState);

			while(true) fsm.Update();
		}
		raylib::Window& App::GetWin()
		{
			return window;
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
	}
}