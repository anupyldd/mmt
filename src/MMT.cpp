/*******************************************************************************************
*
*   raylib-extras [ImGui] example - Simple Integration
*
*	This is a simple ImGui Integration
*	It is done using C++ but with C style code
*	It can be done in C as well if you use the C ImGui wrapper
*	https://github.com/cimgui/cimgui
*
*   Copyright (c) 2021 Jeffery Myers
*
********************************************************************************************/

#include "core/Localization.h"

#define U8(txt) (const char*)u8##txt

#include "raylib.h"
#include "raymath.h"

#include "imgui.h"
#include "rlImGui.h"

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1280;
	int screenHeight = 800;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib-Extras [ImGui] example - simple ImGui Demo");
	SetTargetFPS(144);
	rlImGuiSetup(true);

	using namespace mmt::core;
	Config::GetInstance().Load("data/config.json");
	Localization::GetInstance().Load("data/loc.json");

	//ImFontConfig font_config;
	//font_config.OversampleH = 1; //or 2 is the same
	//font_config.OversampleV = 1;
	//font_config.PixelSnapH = 1;
	//
	//static const ImWchar ranges[] =
	//{
	//	0x0020, 0x00FF, // Basic Latin + Latin Supplement
	//	0x0400, 0x044F, // Cyrillic
	//	0,
	//};
	//ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontFromFileTTF("data/res/app/NotoSans-Medium.ttf", 14.0f, &font_config, ranges);
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();
	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF("data/res/app/NotoSans-Medium.ttf", 32.0f, NULL,
		ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	rlImGuiReloadFonts();
	//rlImGuiSetup(true);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		// start ImGui Conent
		rlImGuiBegin();

		// show ImGui Content
		bool open = true;
		ImGui::Begin("aaa");
		ImGui::Text(LocC("load_all_tt"));
		ImGui::End();

		// end ImGui Content
		rlImGuiEnd();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}
	rlImGuiShutdown();

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}