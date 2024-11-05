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
            std::string font,
                        theme;
            int         fontSize = 24;
            float       scale = 1.0f;
        };

        struct MetaConfig
        {
            std::vector<std::string> languages;
        };

        struct MapConfig
        {
            float previewQuality = 0.5; // 0...1, quality multiplier

            // remembers last values used in map creation for convenience
            int lastWidth = 1920,
                lastHeight = 1080;
        };
	}
}