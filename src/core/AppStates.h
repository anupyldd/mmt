#pragma once

#include "../utility/StateMachine.h"
#include "App.h"

namespace hnd
{
	namespace core
	{
		using namespace util;
		class App;

		class InitLoadAppState : public State<App>
		{
			virtual void Enter(std::shared_ptr<App> owner) override final;
			virtual void Execute(std::shared_ptr<App> owner) override final {};
			virtual void Exit(std::shared_ptr<App> owner) override final {};
		};

		class MainMenuAppState : public State<App>
		{
		public:
			virtual void Enter(std::shared_ptr<App> owner) override final;
			virtual void Execute(std::shared_ptr<App> owner) override final;
			virtual void Exit(std::shared_ptr<App> owner) override final;
		};

		class MapEditAppState : public State<App>
		{
		public:
			virtual void Enter(std::shared_ptr<App> owner) override final;
			virtual void Execute(std::shared_ptr<App> owner) override final;
			virtual void Exit(std::shared_ptr<App> owner) override final;
		};

		class CloseAppState : public State<App>
		{
		public:
			virtual void Enter(std::shared_ptr<App> owner) override final;
			virtual void Execute(std::shared_ptr<App> owner) override final;
			virtual void Exit(std::shared_ptr<App> owner) override final;
		};
	}
}