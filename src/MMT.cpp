#include "core/App.h"

#include "core/map/Pack.h"

int main(int argc, char** argv)
{
	mmt::core::App app;
	app.Init(argc, argv);
	app.Run();
}
