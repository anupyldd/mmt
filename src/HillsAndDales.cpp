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

	components::Transform tr;
	tr.angle = 2;
	tr.scale = 3;
	tr.x = 5;

	components::Sprite sp;
	sp.handle = 987654;

	picojson::value::object obj;
	tr.Serialize(obj);
	sp.Serialize(obj);

	picojson::value v(obj);

	std::cout << v.serialize(true);
}
