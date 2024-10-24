#include "Gui.h"

namespace hnd
{
    namespace gui
    {
        void Gui::UpdateDraw()
        {
			rlImGuiBegin();

            for (auto& obj : objects)
            {
                if(obj->IsVisible()) obj->Update();
            }

			rlImGuiEnd();
        }
        void Gui::Add(GuiObjPtr obj)
        {
            if (obj)
            {
                objects.emplace_back(std::move(obj));
                LOG_DEBUG("Added Gui object");
            }
        }
        void Gui::Remove(GuiObjPtr obj)
        {
            try
            {
                objects.erase(std::find(objects.begin(), objects.end(), obj));
                LOG_DEBUG("Removed Gui object");
            }
            catch (const std::exception& e)
            {
                std::string msg("Could not remove Gui object: " + std::string(e.what()));
                LOG_ERROR(msg);
            }
        }
    }
}