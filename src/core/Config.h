#pragma once

#pragma once

#include "../utility/Defines.h"
#include "../utility/Log.h"
#include "../utility/Serialization.h"
#include "../utility/StringUtil.h"

#include "raylib.h"
#include "json/picojson.h"

#include <fstream>
#include <sstream>
#include <exception>
#include <filesystem>
#include <vector>
#include <memory>

namespace mmt
{
    namespace core
    {
        struct Settings
        {
            // app
            int appWidth = 800, appHeight = 600,
                appPosX = 100, appPosY = 100,
                appFPS = 60;

            std::vector<std::string> appFlags;

            std::string appTitle = "MMT",
                        appVersion = "v0.0",
                        appLanguage = "en";

            // gui
            std::string guiFont,
                        guiTheme;

            float       guiScale = 1.0f;

            // meta
            std::vector<std::string> metaLanguages;

            // map
            int mapLastWidth = 1000,
                mapLastHeight = 1000;
        };

        // ---------------------------

        class Config
        {
            MMT_SINGLETON(Config);

        public:
            bool Load(const std::filesystem::path& relPath);
            void Save(const std::filesystem::path& relPath);

            unsigned int GetWindowFlags() const;

        public:
            std::unique_ptr<Settings> settings;

        private:
            unsigned int WindowFlagFromStr(const std::string& str) const;
            std::string WindowFlagToStr(unsigned int flag) const;
            std::vector<std::string> WindowFlagsToVec(unsigned int flags) const;
        };
    }
}