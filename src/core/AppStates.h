#pragma once

#include "../utility/StateMachine.h"

namespace mmt
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

		// --------------------------------------

		class AppInitLoadState : public AppState
		{
			virtual void Enter(App* owner) override final;
			virtual void Execute(App* owner) override final;
			virtual void Exit(App* owner) override final;

			void LoadRes();
		};

		class AppMainMenuState : public AppState
		{
			virtual void Enter(App* owner) override final;
			virtual void Execute(App* owner) override final;
			virtual void Exit(App* owner) override final;

			bool menuOpen = false;
		};

		class AppMapEditState : public AppState
		{
			virtual void Enter(App* owner) override final;
			virtual void Execute(App* owner) override final;
			virtual void Exit(App* owner) override final;

			bool editOpen = false;
		};

		class AppCloseState : public AppState
		{
			virtual void Enter(App* owner) override final;
			virtual void Execute(App* owner) override final;
			virtual void Exit(App* owner) override final;
		};
	}
}