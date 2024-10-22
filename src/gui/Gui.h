#pragma once

#include <vector>
#include <memory>

#include "raylib.h"
#include "rlImGui.h"

#include "GuiObject.h"
#include "../utility/Defines.h"

namespace hnd
{
    namespace gui
    {
        class Gui
        {
            SINGLETON(Gui);

        public:


        private:
            std::vector<std::shared_ptr<GuiObject>> objects;
        };
    }
}