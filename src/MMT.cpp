﻿// HillsAndDales.cpp : Defines the entry point for the application.
//

#include "utility/Log.h"
//#include "core/App.h"
//#include "core/map/Components.h"
//#include "utility/StringUtil.h"

#include "core/ConfigStructs.h"

#include "rfl.hpp"
#include <rfl/json.hpp>

int main()
{
	mmt::core::MapConfig mc{ .lastHeight = 123 };
	
	std::cout << rfl::json::write(mc);
	//using namespace mmt;
	//using namespace core;
	//
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
