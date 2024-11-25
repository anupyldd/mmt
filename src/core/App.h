#pragma once

#include "raylib.h"

#include "Config.h"
#include "Localization.h"
#include "../gui/Gui.h"
#include "../utility/StateMachine.h"
#include "../utility/Observer.h"
#include "ResourceManager.h"

#include <exception>

namespace hnd
{
	namespace core
	{
		class App;
		using namespace util;
		using namespace gui;

		class AppState : public util::State<App>
		{
			virtual void Enter(App* owner) = 0;
			virtual void Execute(App* owner) = 0;
			virtual void Exit(App* owner) = 0;
		};

		//-------------------------------------

		class App : public Observer
		{
			friend class Gui;

		public:
			App();

			void Init();
			void Run();

		private:
			void UpdateConfig() const;
			virtual void OnNotify(const Event& evt) override final;

		private:
			gui::Gui appGui;
			util::StateMachine<App> fsm;

		private:
			class InitLoad : public AppState
			{
				virtual void Enter(App* owner) override final {};
				virtual void Execute(App* owner) override final ;
				virtual void Exit(App* owner) override final {};
			};
			InitLoad initLoadState;

			class MainMenu : public AppState
			{
				virtual void Enter(App* owner) override final;
				virtual void Execute(App* owner) override final;
				virtual void Exit(App* owner) override final;

				bool menuOpen = false;
			};
			MainMenu mainMenuState;

			class MapEdit : public AppState
			{
				virtual void Enter(App* owner) override final;
				virtual void Execute(App* owner) override final;
				virtual void Exit(App* owner) override final;

				bool editOpen = false;
			};
			MapEdit mapEditState;

			class Close : public AppState
			{
				virtual void Enter(App* owner) override final {};
				virtual void Execute(App* owner) override final;
				virtual void Exit(App* owner) override final {};
			};
			Close closeState;
		};
	}
}