#include "AppStates.h"
#include "App.h"
#include "../utility/Log.h"
#include "Localization.h"
#include "ResourceManager.h"
#include "map/PackManager.h"

#include "raylib-cpp.hpp"
#include "imgui.h"
#include "rlImGui.h"

namespace mmt
{
	namespace core
	{
		void AppInitLoadState::Enter(App* owner)
		{
			LOG_F(INFO, "Starting app initialization");
		}

		void AppInitLoadState::Execute(App* owner)
		{
			util::Log::GetInstance().InitSession();
			owner->GetGui().SetOwner(owner);
			
			if (raylib::Window::IsReady()) throw std::runtime_error("Attempting to open window twice");

			auto& conf = Config::GetInstance();
			if (!conf.Load("data/config.json"))
				LOG_F(ERROR, "Error loading config, falling back to default values");

			Localization::GetInstance().Load("data/loc.json");
			
			std::string title = conf.settings->appTitle;
			title += " - " + conf.settings->appVersion;

		#if _DEBUG
			title += " [DEBUG]";
		#endif

			owner->GetWin().Init(
				conf.settings->appWidth,
				conf.settings->appHeight,
				title,
				conf.GetWindowFlags());

			owner->GetWin()
				.SetPosition(Vector2{ 
					static_cast<float>(conf.settings->appPosX), 
					static_cast<float>(conf.settings->appPosY) })
				.SetTargetFPS(conf.settings->appFPS)
				.SetExitKey(KEY_NULL);


			//InitWindow(conf.settings->appWidth, conf.settings->appHeight, title.c_str());
			//SetConfigFlags(conf.GetWindowFlags());
			//SetTraceLogLevel(LOG_TRACE);
			//SetWindowPosition(conf.settings->appPosX, conf.settings->appPosY);
			//SetTargetFPS(conf.settings->appFPS);
			//SetExitKey(KEY_NULL);

			rlImGuiSetup(true);

			LoadRes();
			auto& pmgr = PackManager::GetInstance();
			pmgr.SetSearchPath(std::filesystem::path("data") / "res" / "packs");
			pmgr.FindAvailable();


		#ifdef IMGUI_HAS_DOCK
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		#endif

			owner->GetFsm().ChangeState(&owner->mainMenuState);
		}

		void AppInitLoadState::Exit(App* owner)
		{
			LOG_F(INFO, "Finishing app initialization");
		}

		void AppInitLoadState::LoadRes()
		{
			raylib::Image icon("data/res/app/icon.png");
			//Image icon = LoadImage("data/res/app/icon.png");
			SetWindowIcon(icon);
			//UnloadImage(icon);

			ImGuiIO& io = ImGui::GetIO();
			io.Fonts->Clear();
			io.Fonts->AddFontFromFileTTF("data/res/app/NotoSans-Medium.ttf", 32.0f, NULL,
				ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			rlImGuiReloadFonts();
		}

		// -----------------------------------------------------

		void AppMainMenuState::Enter(App* owner)
		{
			menuOpen = true;
			DLOG_F(INFO, "Main menu is now open");
		}

		void AppMainMenuState::Execute(App* owner)
		{
			while (!WindowShouldClose() && menuOpen)
			{
				owner->GetWin().BeginDrawing();
				owner->GetWin().ClearBackground(BLUE);

				owner->GetGui().UpdateDraw(GuiState::MainMenu);
				owner->UpdateConfig();

				owner->GetWin().EndDrawing();
			}

			if (WindowShouldClose()) owner->GetFsm().ChangeState(&owner->closeState);
		}

		void AppMainMenuState::Exit(App* owner)
		{
			menuOpen = false;
			DLOG_F(INFO, "Exiting main menu");
		}

		// -----------------------------------------------------

		void AppMapEditState::Enter(App* owner)
		{
			editOpen = true;
			DLOG_F(INFO, "Map edit is now open");
		}

		void AppMapEditState::Execute(App* owner)
		{
			while (!WindowShouldClose() && editOpen)
			{
				BeginDrawing();
				ClearBackground(GREEN);

				owner->GetGui().UpdateDraw(GuiState::Editor);
				owner->UpdateConfig();

				/*********************************************/
				if (IsKeyPressed(KEY_ESCAPE))
				{
					DLOG_F(INFO, "Going back to menu");
					owner->GetFsm().ChangeState(&owner->mainMenuState);
				}
				/*********************************************/

				EndDrawing();
			}

			if (WindowShouldClose()) owner->GetFsm().ChangeState(&owner->closeState);
		}

		void AppMapEditState::Exit(App* owner)
		{
			editOpen = false;
			DLOG_F(INFO, "Exiting map editing");
		}

		// -----------------------------------------------------


		void AppCloseState::Enter(App* owner)
		{
			DLOG_F(INFO, "Starting to close the app");
		}

		void AppCloseState::Execute(App* owner)
		{
			Config::GetInstance().Save("data/config.json");
			rlImGuiShutdown();
			CloseWindow();
			exit(0);
		}

		void AppCloseState::Exit(App* owner)
		{
			DLOG_F(WARNING, "You should not see this");
		}
	}
}