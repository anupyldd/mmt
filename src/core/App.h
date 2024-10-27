#pragma once

#include "raylib.h"

#include "../gui/Gui.h"
#include "../utility/StateMachine.h"
#include "Config.h"
#include "atlas/Map.h"
#include "AppStates.h"

#include <exception>

namespace hnd
{
	namespace core
	{
		class App
		{
		public:
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
				virtual void Enter(std::shared_ptr<App> owner) override final;
				virtual void Execute(std::shared_ptr<App> owner) override final {};
				virtual void Exit(std::shared_ptr<App> owner) override final {};
			};
			InitLoad initLoadState;

			class MainMenu : public AppState
			{
				virtual void Enter(std::shared_ptr<App> owner) override final;
				virtual void Execute(std::shared_ptr<App> owner) override final;
				virtual void Exit(std::shared_ptr<App> owner) override final;
			};
			MainMenu mainMenuState;

			class MapEdit : public AppState
			{
				virtual void Enter(std::shared_ptr<App> owner) override final;
				virtual void Execute(std::shared_ptr<App> owner) override final;
				virtual void Exit(std::shared_ptr<App> owner) override final;
			};
			MapEdit mapEditState;

			class Close : public AppState
			{
				virtual void Enter(std::shared_ptr<App> owner) override final;
				virtual void Execute(std::shared_ptr<App> owner) override final {};
				virtual void Exit(std::shared_ptr<App> owner) override final {};
			};
			Close closeState;
		};

		class AppState : public State<App>
		{
			virtual void Enter(std::shared_ptr<App> owner) = 0;
			virtual void Execute(std::shared_ptr<App> owner) = 0;
			virtual void Exit(std::shared_ptr<App> owner) = 0;
		};
	}
}