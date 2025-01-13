#pragma once

#include "raylib.h"

#include "Config.h"
#include "Localization.h"
#include "../gui/Gui.h"
#include "../utility/Observer.h"
#include "AppStates.h"

#include <exception>

namespace mmt
{
	namespace core
	{
		class AppInitLoadState;
		class AppMainMenuState;
		class AppMapEditState;
		class AppCloseState;

		using namespace util;
		using namespace gui;

		//-------------------------------------

		class App
		{
			friend class Gui;

		public:
			App();
			~App();

			void Init(int argc, char** argv);
			void Run();

			util::StateMachine<App>& GetFsm();
			gui::Gui& GetGui();

			void UpdateConfig() const;

		private:
			gui::Gui appGui;
			util::StateMachine<App> fsm;

		public:
			AppInitLoadState initLoadState;
			AppMainMenuState mainMenuState;
			AppMapEditState mapEditState;
			AppCloseState closeState;
		};
	}
}