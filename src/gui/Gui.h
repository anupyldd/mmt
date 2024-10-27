#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <exception>

#include "raylib.h"
#include "rlImGui.h"

#include "MainMenu.h"
#include "../utility/Defines.h"
#include "../utility/Log.h"
#include "../utility/StateMachine.h"

namespace hnd
{
    namespace gui
    {
        class MainMenu;

        class Gui
        {
            friend class App;
            using GuiObjPtr = std::unique_ptr<GuiObject>;

        public:
            void UpdateDraw();

            void Add(GuiObjPtr obj);
            void Remove(GuiObjPtr obj);

        public:
            MainMenu mainMenu;
        };
    }
}