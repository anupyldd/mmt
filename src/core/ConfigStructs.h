#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "raylib.h"

namespace hnd
{
	namespace core
	{
        struct AppConfig
        {
            int width = 600, height = 400,
                posX = 100, posY = 100,
                fps = 60;

            unsigned int flags = 0;

            std::string title = "Hills and Dales",
                        version = "0.0",
                        language = "en";

        };

        struct GuiConfig
        {
            int         fontSize = 24;
            float       scale = 1.0f;
            Font        font;
        };

        struct MetaConfig
        {
            std::vector<std::string> languages;
        };
	}
}