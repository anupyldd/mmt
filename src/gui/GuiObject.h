#pragma once

#include "../utility/Observer.h"
#include "../core/Localization.h"

namespace mmt
{
    namespace core
    {
        class App;
    }

    namespace gui
    {
        using namespace util;

        class GuiObject
        {
        public:
            virtual ~GuiObject() = default;

            virtual void Update(core::App* app) = 0;
            bool IsVisible() const { return visible; }

        protected:
            bool visible = true;
        };
    }
}