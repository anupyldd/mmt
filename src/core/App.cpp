#include "App.h"

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
			MMT_LOG_DEBUG("App is now running");

			appGui.mainMenu.AddObserver(this);
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

		void App::OnNotify(const Event& evt)
		{
			using namespace util;

			switch (evt.type)
			{
			case EventType::GUI_FROM_MAIN_TO_EDIT:
			{
				MMT_LOG_DEBUG("handling notification");
				if(fsm.IsInState(&mainMenuState)) fsm.ChangeState(&mapEditState);
			}
			break;

			default: break;
			}
		}

		/************************************************/
		/********************STATES**********************/
		/************************************************/

		void App::InitLoad::Execute(App* owner)
		{
			if (IsWindowReady()) throw std::runtime_error("Attempting to open window twice");

			auto& conf = Config::GetInstance();
			if (!conf.Load("data/config.json"))
				MMT_LOG_ERROR("Error loading config, falling back to default values");

			Localization::GetInstance().Load("data/loc.json");

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
			SetExitKey(KEY_NULL);
			rlImGuiSetup(true);

			/********************************/
			ResourceManager::GetInstance().Load();
			/********************************/

		#ifdef IMGUI_HAS_DOCK
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		#endif

			owner->fsm.ChangeState(&owner->mainMenuState);
		}
		//-----------------------------------
		void App::MainMenu::Enter(App* owner)
		{
			menuOpen = true;
			MMT_LOG_DEBUG("Main menu is now open");
		}
		void App::MainMenu::Execute(App* owner)
		{
			// -------------
			//EcsMgr().CreateInstance("atlas1", "map1", 5000);
			// -------------

			while (!WindowShouldClose() && menuOpen)
			{
				BeginDrawing();
				ClearBackground(BLUE);

				//EcsMgr().UpdateActive();
				owner->appGui.UpdateDraw(GuiState::MainMenu);
				owner->UpdateConfig();

				EndDrawing();
			}

			if (WindowShouldClose()) owner->fsm.ChangeState(&owner->closeState);
		}
		void App::MainMenu::Exit(App* owner)
		{
			menuOpen = false;
			MMT_LOG_DEBUG("Exiting main menu");
		}
		//-------------------------------------
		void App::MapEdit::Enter(App* owner)
		{
			editOpen = true;
			MMT_LOG_DEBUG("Map edit is now open");
		}
		void App::MapEdit::Execute(App* owner)
		{
			while (!WindowShouldClose() && editOpen)
			{
				BeginDrawing();
				ClearBackground(GREEN);

				owner->appGui.UpdateDraw(GuiState::Editor);
				owner->UpdateConfig();

				/*********************************************/
				if (IsKeyPressed(KEY_ESCAPE))
				{
					MMT_LOG_DEBUG("Going back to menu");
					owner->fsm.ChangeState(&owner->mainMenuState);
				}
				/*********************************************/

				EndDrawing();
			}

			if(WindowShouldClose()) owner->fsm.ChangeState(&owner->closeState);
		}
		void App::MapEdit::Exit(App* owner)
		{
			editOpen = false;
			MMT_LOG_DEBUG("Exiting map editing");
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