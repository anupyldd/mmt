#include "App.h"

namespace hnd
{
	namespace core
	{


		/********************************************************/
		Map map({ 400,400 });
		/********************************************************/
		void App::Init()
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
			/***********************************/
			map.AddLayer("l");
			/***********************************/
		}
		void App::Run()
		{
			while (!WindowShouldClose())
			{
				BeginDrawing();
				ClearBackground(GREEN);

				gui::Gui::GetInstance().UpdateDraw();
				UpdateConfig();

				/*********************************************/
				
				map.Update();
				map.Draw();
				/*********************************************/

				EndDrawing();
			}

			Config::GetInstance().Save("data/config.json");
			rlImGuiShutdown();
			CloseWindow();
		}
		void App::UpdateConfig() const
		{
			auto& conf = Config::GetInstance();

			conf.app->width = GetScreenWidth();
			conf.app->height = GetScreenHeight();
			conf.app->posX = GetWindowPosition().x;
			conf.app->posY = GetWindowPosition().y;
		}
	}
}