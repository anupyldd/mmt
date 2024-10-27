#include "MainMenu.h"

namespace hnd
{
	namespace gui
	{
		MainMenu::MainMenu()
		{
		}
		void MainMenu::Update()
		{
			using namespace util;

			if (!visible) return;

			ImGui::Begin("Main Menu", 0, 0);

			if (ImGui::Button("Go to map editing"))
			{
				LOG_DBG("Pressed button");
				Notify({ .type = EventType::GUI_FROM_MAIN_TO_EDIT });
			}

			ImGui::End();
		}
	}
}