#include "MainMenu.h"

namespace mmt
{
	namespace gui
	{
		MainMenu::MainMenu()
		{
		}
		void MainMenu::Update()
		{
			using namespace util;
			using namespace core;

			if (!visible) return;

			ImGui::Begin("Main Menu", 0, 0);

			if (ImGui::Button(LocC("new_map")))
			{
				MMT_LOG_DEBUG("Pressed button");
				Notify({ .type = EventType::GUI_FROM_MAIN_TO_EDIT });
			}

			ImGui::End();
		}
	}
}