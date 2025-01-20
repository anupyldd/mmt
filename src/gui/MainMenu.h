#pragma once

#include "GuiObject.h"
#include "ResourceView.h"
#include "../utility/Log.h"

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

namespace mmt
{
	namespace core
	{
		class App;
	}

	namespace gui
	{
		using namespace util;

		class MainMenu : public GuiObject
		{
		public:
			MainMenu();
			virtual void Update(core::App* app) override final;

		private:
			ResourceView resV;
		};
	}
}