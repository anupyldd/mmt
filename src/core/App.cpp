#include "App.h"

namespace hnd
{
	namespace core
	{


		/********************************************************/
		Map map({ 400,400 });
		/********************************************************/

		App::App()
			: fsm(this)
		{
		}
		void App::Init()
		{
			
		}
		void App::Run()
		{
			LOG_DEBUG("App is now running");
			fsm.SetCurrentState(&initLoadState);

			while(true) fsm.Update();
		}
		void App::UpdateConfig() const
		{
			auto& conf = Config::GetInstance();

			conf.app->width = GetScreenWidth();
			conf.app->height = GetScreenHeight();
			conf.app->posX = GetWindowPosition().x;
			conf.app->posY = GetWindowPosition().y;
		}

		/************************************************/
		/********************STATES**********************/
		/************************************************/

		void App::InitLoad::Execute(App* owner)
		{
			if (IsWindowReady()) throw std::runtime_error("Attempting to open window twice");

			auto& conf = Config::GetInstance();
			if (!conf.Load("data/config.json"))
				LOG_ERROR("Error loading config, falling back to default values");

			SetConfigFlags(conf.app->flags);
			SetTraceLogLevel(LOG_WARNING);

			std::string title = conf.app->title;
			title += " - " + conf.app->version;

		#if _DEBUG
			title += " [DEBUG]";
			InitWindow(conf.app->width, conf.app->height, title.c_str());
		#else
			InitWindow(conf.app->width, conf.app->height, title.c_str());
		#endif

			SetWindowPosition(conf.app->posX, conf.app->posY);
			SetTargetFPS(conf.app->fps);
			rlImGuiSetup(true);

			owner->fsm.ChangeState(&owner->mainMenuState);
			//LOG_DEBUG(std::to_string((uint64_t) & owner->mainMenuState));
			//LOG_DEBUG(std::to_string((uint64_t) & owner->initLoadState));

			LOG_DEBUG("Switched to main menu");
		}
		//-----------------------------------
		void App::MainMenu::Enter(App* owner)
		{
			LOG_DEBUG("Main menu is now open");
		}
		void App::MainMenu::Execute(App* owner)
		{
			owner->fsm.ChangeState(&owner->mapEditState);
		}
		void App::MainMenu::Exit(App* owner)
		{
		}
		//-------------------------------------
		void App::MapEdit::Enter(App* owner)
		{
			LOG_DEBUG("Map edit is now open");
		}
		void App::MapEdit::Execute(App* owner)
		{
			while (!WindowShouldClose())
			{
				BeginDrawing();
				ClearBackground(GREEN);

				owner->appGui.UpdateDraw();
				owner->UpdateConfig();

				/*********************************************/
				if (IsKeyPressed(KEY_SPACE)) map.AddLayer("test");
				map.Update();
				map.Draw();
				/*********************************************/

				EndDrawing();
			}

			owner->fsm.ChangeState(&owner->closeState);
		}
		void App::MapEdit::Exit(App* owner)
		{
		}
		//-------------------------------------
		void App::Close::Execute(App* owner)
		{
			Config::GetInstance().Save("data/config.json");
			rlImGuiShutdown();
			CloseWindow();
			exit(0);
		}
}
}