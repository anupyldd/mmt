#include "Config.h"

namespace hnd
{
    namespace core
    {
        bool Config::Load(const std::filesystem::path& relPath)
        {
            try
            {
                auto cwd = std::filesystem::current_path();
                std::ifstream file(cwd / relPath);
                std::stringstream contents;
                contents << file.rdbuf();

                std::string strCont = contents.str();
                picojson::value val;

                std::string err = picojson::parse(val, strCont);
                if (!err.empty()) throw std::runtime_error("Failed to parse config file: " + err);

                LOG_DEBUG("Parsed config file");

                if (!val.is<picojson::object>()) throw std::runtime_error("Config json is not an object");
                const picojson::value::object& obj = val.get<picojson::object>();

                try
                {
                    LoadAppConfig(obj);
                    LoadMetaConfig(obj);
                    LoadGuiConfig(obj);
                }
                catch (const std::exception& e)
                {
                    LOG_ERROR(e.what());
                }

                return true;
            }
            catch (const std::exception& e)
            {
                LOG_ERROR("Failed to load config file: " + std::string(e.what()));
            }
        }

        void Config::Save(const std::filesystem::path& relPath)
        {
            try
            {
                auto cwd = std::filesystem::current_path();
                std::ofstream file(cwd / relPath);

                picojson::value::object obj;

                SaveAppConfig(obj);
                SaveGuiConfig(obj);
                SaveMetaConfig(obj);

                picojson::value mainVal(obj);

                std::string str = mainVal.serialize(true);
                file << str;

                LOG_DEBUG("Saved config");
            }
            catch (const std::exception& e)
            {
                LOG_ERROR("Failed to save config: " + std::string(e.what()));
            }
        }

        // ------------------

        void Config::LoadAppConfig(const picojson::value::object& obj)
        {
            try
            {
                const auto& ap = obj.at("pApp").get<picojson::object>();

                pApp->width = static_cast<int>(ap.at("width").get<double>());
                pApp->height = static_cast<int>(ap.at("height").get<double>());
                pApp->posX = static_cast<int>(ap.at("posX").get<double>());
                pApp->posY = static_cast<int>(ap.at("posY").get<double>());
                pApp->fps = static_cast<int>(ap.at("fps").get<double>());
                pApp->title = ap.at("title").get<std::string>();

                const auto& flags = ap.at("flags").get<picojson::array>();
                for (const auto& f : flags)
                {
                    pApp->flags |= WindowFlagFromStr(f.get<std::string>());
                }

                pApp->language = ap.at("language").get<std::string>();
                pApp->version = ap.at("version").get<std::string>();

                LOG_DEBUG("Loaded pApp config");
            }
            catch (const std::exception& e)
            {
                LOG_ERROR("Failed to load pApp config: " + std::string(e.what()));
            }
        }

        void Config::SaveAppConfig(picojson::value::object& obj)
        {
            picojson::value::object appObj;

            appObj["width"] = picojson::value(static_cast<double>(pApp->width));
            appObj["height"] = picojson::value(static_cast<double>(pApp->height));
            appObj["posX"] = picojson::value(static_cast<double>(pApp->posX));
            appObj["posY"] = picojson::value(static_cast<double>(pApp->posY));
            appObj["fps"] = picojson::value(static_cast<double>(pApp->fps));
            appObj["title"] = picojson::value(pApp->title);

            picojson::value::array flags;
            auto strFlags = WindowFlagsToVec(pApp->flags);
            for (const auto& f : strFlags)
            {
                flags.emplace_back(picojson::value(f));
            }
            appObj["flags"] = picojson::value(flags);

            appObj["language"] = picojson::value(pApp->language);
            appObj["version"] = picojson::value(pApp->version);

            picojson::value val(appObj);
            obj["pApp"] = val;
        }

        void Config::LoadGuiConfig(const picojson::value::object& obj)
        {
            try
            {
                const auto& ui = obj.at("pGui").get<picojson::object>();

                pGui->fontSize = static_cast<int>(ui.at("fontSize").get<double>());
                pGui->scale = static_cast<float>(ui.at("scale").get<double>());

                LOG_DEBUG("Loaded pGui config");
            }
            catch (const std::exception& e)
            {
                LOG_ERROR("Failed to load pGui config: " + std::string(e.what()));
            }
        }

        void Config::SaveGuiConfig(picojson::value::object& obj)
        {
            picojson::value::object uiObj;

            uiObj["fontSize"] = picojson::value(static_cast<double>(pGui->fontSize));
            uiObj["scale"] = picojson::value(static_cast<double>(pGui->scale));

            picojson::value val(uiObj);
            obj["pGui"] = val;
        }

        void Config::LoadMetaConfig(const picojson::value::object& obj)
        {
            try
            {
                const auto& mt = obj.at("pMeta").get<picojson::object>();

                const auto& langs = mt.at("available_languages").get<picojson::array>();
                for (const auto& l : langs)
                {
                    pMeta->languages.push_back(l.get<std::string>());
                }

                LOG_DEBUG("Loaded pMeta config: " + std::to_string(pMeta->languages.size()));
            }
            catch (const std::exception& e)
            {
                LOG_ERROR("Failed to load pMeta config: " + std::string(e.what()));
            }
        }

        void Config::SaveMetaConfig(picojson::value::object& obj)
        {
            picojson::value::object metaObj;

            picojson::value::array langs;
            for (const auto& l : pMeta->languages)
            {
                langs.emplace_back(picojson::value(l));
            }
            metaObj["available_languages"] = picojson::value(langs);

            picojson::value val(metaObj);
            obj["pMeta"] = val;
        }

        // ------------------

        unsigned int Config::WindowFlagFromStr(const std::string& str) const
        {
            if (str == "FLAG_VSYNC_HINT") return FLAG_VSYNC_HINT;
            if (str == "FLAG_FULLSCREEN_MODE") return FLAG_FULLSCREEN_MODE;
            if (str == "FLAG_WINDOW_RESIZABLE") return FLAG_WINDOW_RESIZABLE;
            if (str == "FLAG_WINDOW_UNDECORATED") return FLAG_WINDOW_UNDECORATED;
            if (str == "FLAG_WINDOW_HIDDEN") return FLAG_WINDOW_HIDDEN;
            if (str == "FLAG_WINDOW_MINIMIZED") return FLAG_WINDOW_MINIMIZED;
            if (str == "FLAG_WINDOW_MAXIMIZED") return FLAG_WINDOW_MAXIMIZED;
            if (str == "FLAG_WINDOW_UNFOCUSED") return FLAG_WINDOW_UNFOCUSED;
            if (str == "FLAG_WINDOW_TOPMOST") return FLAG_WINDOW_TOPMOST;
            if (str == "FLAG_WINDOW_ALWAYS_RUN") return FLAG_WINDOW_ALWAYS_RUN;
            if (str == "FLAG_WINDOW_TRANSPARENT") return FLAG_WINDOW_TRANSPARENT;
            if (str == "FLAG_WINDOW_HIGHDPI") return FLAG_WINDOW_HIGHDPI;
            if (str == "FLAG_WINDOW_MOUSE_PASSTHROUGH") return FLAG_WINDOW_MOUSE_PASSTHROUGH;
            if (str == "FLAG_BORDERLESS_WINDOWED_MODE") return FLAG_BORDERLESS_WINDOWED_MODE;
            if (str == "FLAG_MSAA_4X_HINT") return FLAG_MSAA_4X_HINT;
            if (str == "FLAG_INTERLACED_HINT") return FLAG_INTERLACED_HINT;

        }

        std::string Config::WindowFlagToStr(unsigned int flag) const
        {
            if (flag & FLAG_VSYNC_HINT) return "FLAG_VSYNC_HINT";
            if (flag & FLAG_FULLSCREEN_MODE) return "FLAG_FULLSCREEN_MODE";
            if (flag & FLAG_WINDOW_RESIZABLE) return "FLAG_WINDOW_RESIZABLE";
            if (flag & FLAG_WINDOW_UNDECORATED) return "FLAG_WINDOW_UNDECORATED";
            if (flag & FLAG_WINDOW_HIDDEN) return "FLAG_WINDOW_HIDDEN";
            if (flag & FLAG_WINDOW_MINIMIZED) return "FLAG_WINDOW_MINIMIZED";
            if (flag & FLAG_WINDOW_MAXIMIZED) return "FLAG_WINDOW_MAXIMIZED";
            if (flag & FLAG_WINDOW_UNFOCUSED) return "FLAG_WINDOW_UNFOCUSED";
            if (flag & FLAG_WINDOW_TOPMOST) return "FLAG_WINDOW_TOPMOST";
            if (flag & FLAG_WINDOW_ALWAYS_RUN) return "FLAG_WINDOW_ALWAYS_RUN";
            if (flag & FLAG_WINDOW_TRANSPARENT) return "FLAG_WINDOW_TRANSPARENT";
            if (flag & FLAG_WINDOW_HIGHDPI) return "FLAG_WINDOW_HIGHDPI";
            if (flag & FLAG_WINDOW_MOUSE_PASSTHROUGH) return "FLAG_WINDOW_MOUSE_PASSTHROUGH";
            if (flag & FLAG_BORDERLESS_WINDOWED_MODE) return "FLAG_BORDERLESS_WINDOWED_MODE";
            if (flag & FLAG_MSAA_4X_HINT) return "FLAG_MSAA_4X_HINT";
            if (flag & FLAG_INTERLACED_HINT) return "FLAG_INTERLACED_HINT";
        }

        std::vector<std::string> Config::WindowFlagsToVec(unsigned int flags) const
        {
            std::vector<std::string> res;

            if (flags & FLAG_VSYNC_HINT) res.emplace_back("FLAG_VSYNC_HINT");
            if (flags & FLAG_FULLSCREEN_MODE) res.emplace_back("FLAG_FULLSCREEN_MODE");
            if (flags & FLAG_WINDOW_RESIZABLE) res.emplace_back("FLAG_WINDOW_RESIZABLE");
            if (flags & FLAG_WINDOW_UNDECORATED) res.emplace_back("FLAG_WINDOW_UNDECORATED");
            if (flags & FLAG_WINDOW_HIDDEN) res.emplace_back("FLAG_WINDOW_HIDDEN");
            if (flags & FLAG_WINDOW_MINIMIZED) res.emplace_back("FLAG_WINDOW_MINIMIZED");
            if (flags & FLAG_WINDOW_MAXIMIZED) res.emplace_back("FLAG_WINDOW_MAXIMIZED");
            if (flags & FLAG_WINDOW_UNFOCUSED) res.emplace_back("FLAG_WINDOW_UNFOCUSED");
            if (flags & FLAG_WINDOW_TOPMOST) res.emplace_back("FLAG_WINDOW_TOPMOST");
            if (flags & FLAG_WINDOW_ALWAYS_RUN) res.emplace_back("FLAG_WINDOW_ALWAYS_RUN");
            if (flags & FLAG_WINDOW_TRANSPARENT) res.emplace_back("FLAG_WINDOW_TRANSPARENT");
            if (flags & FLAG_WINDOW_HIGHDPI) res.emplace_back("FLAG_WINDOW_HIGHDPI");
            if (flags & FLAG_WINDOW_MOUSE_PASSTHROUGH) res.emplace_back("FLAG_WINDOW_MOUSE_PASSTHROUGH");
            if (flags & FLAG_BORDERLESS_WINDOWED_MODE) res.emplace_back("FLAG_BORDERLESS_WINDOWED_MODE");
            if (flags & FLAG_MSAA_4X_HINT) res.emplace_back("FLAG_MSAA_4X_HINT");
            if (flags & FLAG_INTERLACED_HINT) res.emplace_back("FLAG_INTERLACED_HINT");

            return res;
        }
    }
}