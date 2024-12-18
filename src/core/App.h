#pragma once

#include "raylib.h"

#include "Config.h"
#include "Localization.h"
#include "../gui/Gui.h"
#include "../utility/Observer.h"
#include "ResourceManager.h"
#include "AppStates.h"

#include <exception>

namespace mmt
{
	namespace core
	{
		class App;
		using namespace util;
		using namespace gui;

		//-------------------------------------

		class App : public Observer
		{
			friend class Gui;

		public:
			App();

			void Init();
			void Run();

			util::StateMachine<App>& GetFsm();
			gui::Gui& GetGui();

			void UpdateConfig() const;
			virtual void OnNotify(const Event& evt) override final;

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