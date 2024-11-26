// HillsAndDales.cpp : Defines the entry point for the application.
//

#include "utility/Log.h"
#include "core/App.h"
#include "core/map/Components.h"

int main()
{
	using namespace mmt;
	using namespace core;

	core::App app;
	app.Run();
	//Config::GetInstance().Load("data/config.json");
}
