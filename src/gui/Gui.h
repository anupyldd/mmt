#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <exception>

#include "raylib.h"
#include "rlImGui.h"

#include "GuiObject.h"
#include "../utility/Defines.h"
#include "../utility/Log.h"

namespace hnd
{
    namespace gui
    {
        class Gui
        {
            SINGLETON(Gui);
            using GuiObjPtr = std::unique_ptr<GuiObject>;

        public:
            void UpdateDraw();

            void Add(GuiObjPtr obj);
            void Remove(GuiObjPtr obj);

        private:
            std::vector<GuiObjPtr> objects;
        };
    }
}