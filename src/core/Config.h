#pragma once

#pragma once

#include "ConfigStructs.h"
#include "../utility/Defines.h"
#include "../utility/Log.h"

#include "raylib.h"
#include "picojson.h"

#include <fstream>
#include <sstream>
#include <exception>
#include <filesystem>
#include <vector>
#include <memory>

namespace hnd
{
    namespace core
    {
        class Config
        {
            SINGLETON(Config);

        public:
            bool Load(const std::filesystem::path& relPath);    // loads values from config file
            void Save(const std::filesystem::path& relPath);

        public:
            std::unique_ptr<AppConfig>     pApp;
            std::unique_ptr<GuiConfig>     pGui;
            std::unique_ptr<MetaConfig>    pMeta;

        private:
            void LoadAppConfig(const picojson::value::object& obj);
            void SaveAppConfig(picojson::value::object& obj);

            void LoadMetaConfig(const picojson::value::object& obj);
            void SaveMetaConfig(picojson::value::object& obj);

            void LoadGuiConfig(const picojson::value::object& obj);
            void SaveGuiConfig(picojson::value::object& obj);

        private:
            unsigned int WindowFlagFromStr(const std::string& str) const;
            std::string WindowFlagToStr(unsigned int flag) const;
            std::vector<std::string> WindowFlagsToVec(unsigned int flags) const;
        };
    }
}