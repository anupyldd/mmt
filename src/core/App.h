#pragma once

#include "raylib.h"

#include "../gui/Gui.h"
#include "../utility/StateMachine.h"
#include "Config.h"
#include "atlas/Map.h"

#include <exception>

namespace hnd
{
	namespace core
	{
		class App;

		class AppState : public util::State<App>
		{
			virtual void Enter(App* owner) = 0;
			virtual void Execute(App* owner) = 0;
			virtual void Exit(App* owner) = 0;
		};

		//-------------------------------------

		class App
		{
		public:
			App();

			void Init();
			void Run();

		private:
			void UpdateConfig() const;

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