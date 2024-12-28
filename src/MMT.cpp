#include "core/App.h"

int main(int argc, char** argv)
{
	loguru::init(argc, argv);

	mmt::core::App app;
	app.Run();
}
