#include "utility/Log.h"
#include "core/App.h"
#include "core/map/Components.h"
#include "core/map/ComponentRegistry.h"
#include "utility/StringUtil.h"

int main()
{
	using namespace mmt;
	using namespace core;
	using namespace util;

	ComponentRegistry reg{
		.tr = comps::Transform{.x = 10,.y = 9 },
		.lr = comps::Layer{.l = 1 } };

	std::cout << rfl::json::write(reg) << '\n';

	//core::App app;
	//app.Run();
	//Config::GetInstance().Load("data/config.json");

	/*
	components::Atlas at;
	at.sortBy = 4;
	at.id = 132243;
	at.name = "some atlas";

	components::Map mp;
	mp.atlasId = 132243;
	mp.creationTime = util::TimeAsString(std::chrono::system_clock::now());

	picojson::value::object obj; 

	at.Serialize(obj);
	mp.Serialize(obj);

	picojson::value mainVal(obj);
	std::cout << mainVal.serialize(true);
	*/
}
