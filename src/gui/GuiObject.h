#pragma once

namespace hnd
{
    namespace gui
    {
        class GuiObject
        {
            virtual void Update() = 0;
            bool IsVisible() const { return visible; }

        protected:
            bool visible = true;
        };
    }
}