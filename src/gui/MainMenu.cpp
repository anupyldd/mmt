#include "MainMenu.h"
#include "../core/App.h"

namespace mmt
{
	namespace gui
	{
		MainMenu::MainMenu()
		{
		}
		void MainMenu::Update(core::App* app)
		{
			using namespace util;
			using namespace core;

			if (!visible) return;

			ImGui::Begin("Main Menu", 0, 0);

		#ifdef IMGUI_HAS_DOCK
			ImGui::DockSpaceOverViewport(0, NULL, ImGuiDockNodeFlags_PassthruCentralNode); 
		#endif
			
			if (ImGui::Button(LocC("new_map")))
			{
				DLOG_F(INFO, "Pressed button");
				app->GetFsm().ChangeState(&app->mapEditState);
			}

			ImGui::End();

			resV.Update(app);
		}
	}
}