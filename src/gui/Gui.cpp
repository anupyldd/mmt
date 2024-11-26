#include "Gui.h"

namespace mmt
{
    namespace gui
    {
        void Gui::UpdateDraw(GuiState state)
        {
			rlImGuiBegin();

            switch (state)
            {
            case GuiState::MainMenu:
                mainMenu.Update();
                break;
            case GuiState::Editor:
                break;
            default:
                break;
            }

			rlImGuiEnd();
        }
        void Gui::Add(GuiObjPtr obj)
        {
            /*
            if (obj)
            {
                objects.emplace_back(std::move(obj));
                MMT_LOG_DEBUG("Added Gui object");
            }
            */
        }
        void Gui::Remove(GuiObjPtr obj)
        {
            /*
            try
            {
                objects.erase(std::find(objects.begin(), objects.end(), obj));
                MMT_LOG_DEBUG("Removed Gui object");
            }
            catch (const std::exception& e)
            {
                std::string msg("Could not remove Gui object: " + std::string(e.what()));
                MMT_LOG_ERROR(msg);
            }
            */
        }
    }
}