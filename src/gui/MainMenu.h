#pragma once

#include "GuiObject.h"
#include "../utility/Log.h"

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

namespace hnd
{
	namespace gui
	{
		using namespace util;

		class MainMenu : public GuiObject
		{
		public:
			MainMenu();
			virtual void Update() override final;
		};
	}
}