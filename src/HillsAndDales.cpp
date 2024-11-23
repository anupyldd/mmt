// HillsAndDales.cpp : Defines the entry point for the application.
//

#include "utility/Log.h"
#include "core/App.h"
#include "core/ResourceManager.h"
#include "core/map/Components.h"

int main()
{
	using namespace hnd;
	using namespace core;

	//core::App app;
	//app.Run();
	Config::GetInstance().Load("data/config.json");
	ResourceManager::GetInstance().Load();
}
