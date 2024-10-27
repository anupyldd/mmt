#pragma once

#include "../utility/Observer.h"

namespace hnd
{
    namespace gui
    {
        using namespace util;

        class GuiObject : public Subject
        {
        public:
            virtual ~GuiObject() = default;

            virtual void Update() = 0;
            bool IsVisible() const { return visible; }

        protected:
            bool visible = true;
        };
    }
}