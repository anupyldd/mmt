#include "Config.h"

namespace mmt
{
    namespace core
    {
        using namespace util;

        bool Config::Load(const std::filesystem::path& relPath)
        {
            app = std::make_unique<AppConfig>();
            gui = std::make_unique<GuiConfig>();
            meta = std::make_unique<MetaConfig>();
            map = std::make_unique<MapConfig>();

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

                MMT_LOG_DEBUG("Parsed config file");

                if (!val.is<picojson::object>()) throw std::runtime_error("Config json is not an object");
                const picojson::value::object& obj = val.get<picojson::object>();

                try
                {
                    LoadAppConfig(obj);
                    LoadMetaConfig(obj);
                    LoadGuiConfig(obj);
                    LoadMapConfig(obj);
                }
                catch (const std::exception& e)
                {
                    MMT_LOG_ERROR(e.what());
                }

                return true;
            }
            catch (const std::exception& e)
            {
                MMT_LOG_ERROR("Failed to load config file: " + std::string(e.what()));
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
                SaveMapConfig(obj);

                picojson::value mainVal(obj);

                std::string str = mainVal.serialize(true);
                file << str;

                MMT_LOG_DEBUG("Saved config");
            }
            catch (const std::exception& e)
            {
                MMT_LOG_ERROR("Failed to save config: " + std::string(e.what()));
            }
        }

        // ------------------

        void Config::LoadAppConfig(const picojson::value::object& obj)
        {
            try
            {
                auto& ap = obj.at("app").get<picojson::object>();

                MMT_LOG_DEBUG(util::GetMemberName(STR(app->width)));

                FromJson(
                    ap,
                    MMT_DESERIALIZE(app->width),
                    MMT_DESERIALIZE(app->height),
                    MMT_DESERIALIZE(app->posX),
                    MMT_DESERIALIZE(app->posY),
                    MMT_DESERIALIZE(app->fps),

                    MMT_DESERIALIZE(app->title),
                    MMT_DESERIALIZE(app->version),
                    MMT_DESERIALIZE(app->language)
                );

                const auto& flags = ap.at("flags").get<picojson::array>();
                for (const auto& f : flags)
                {
                    app->flags |= WindowFlagFromStr(f.get<std::string>());
                }

                MMT_LOG_DEBUG("Loaded app config");
            }
            catch (const std::exception& e)
            {
                MMT_LOG_ERROR("Failed to load app config: " + std::string(e.what()));
            }
        }

        void Config::SaveAppConfig(picojson::value::object& obj)
        {
            picojson::value::object appObj;

            ToJson(
                appObj,
                MMT_SERIALIZE(app->width),
                MMT_SERIALIZE(app->height),
                MMT_SERIALIZE(app->posX),
                MMT_SERIALIZE(app->posY),
                MMT_SERIALIZE(app->fps),

                MMT_SERIALIZE(app->title),
                MMT_SERIALIZE(app->version),
                MMT_SERIALIZE(app->language)
            );

            picojson::value::array flags;
            auto strFlags = WindowFlagsToVec(app->flags);
            for (const auto& f : strFlags)
            {
                flags.emplace_back(picojson::value(f));
            }
            appObj["flags"] = picojson::value(flags);

            picojson::value val(appObj);
            obj["app"] = val;
        }

        void Config::LoadGuiConfig(const picojson::value::object& obj)
        {
            try
            {
                const auto& ui = obj.at("gui").get<picojson::object>();

                FromJson(
                    ui,
                    MMT_DESERIALIZE(gui->font),
                    MMT_DESERIALIZE(gui->fontSize),
                    MMT_DESERIALIZE(gui->scale),
                    MMT_DESERIALIZE(gui->theme)
                );
                
                MMT_LOG_DEBUG("Loaded gui config");
            }
            catch (const std::exception& e)
            {
                MMT_LOG_ERROR("Failed to load gui config: " + std::string(e.what()));
            }
        }

        void Config::SaveGuiConfig(picojson::value::object& obj)
        {
            picojson::value::object uiObj;

            ToJson(
                uiObj,
                MMT_SERIALIZE(gui->font),
                MMT_SERIALIZE(gui->fontSize),
                MMT_SERIALIZE(gui->scale),
                MMT_SERIALIZE(gui->theme)
            );

            picojson::value val(uiObj);
            obj["gui"] = val;
        }

        void Config::LoadMapConfig(const picojson::value::object& obj)
        {
            try
            {
                const auto& mp = obj.at("map").get<picojson::object>();

                FromJson(
                    mp,
                    MMT_DESERIALIZE(map->lastHeight),
                    MMT_DESERIALIZE(map->lastWidth)
                );

                MMT_LOG_DEBUG("Loaded map config");
            }
            catch (const std::exception& e)
            {
                MMT_LOG_ERROR("Failed to load map config: " + std::string(e.what()));
            }
        }

        void Config::SaveMapConfig(picojson::value::object& obj)
        {
            picojson::value::object mpObj;

            ToJson(
                mpObj,
                MMT_SERIALIZE(map->lastHeight),
                MMT_SERIALIZE(map->lastWidth)
            );

            picojson::value val(mpObj);
            obj["map"] = val;
        }

        void Config::LoadMetaConfig(const picojson::value::object& obj)
        {
            try
            {
                const auto& mt = obj.at("meta").get<picojson::object>();

                FromJson(
                    mt,
                    MMT_DESERIALIZE(meta->resourceRelPath)
                );

                const auto& langs = mt.at("available_languages").get<picojson::array>();
                for (const auto& l : langs)
                {
                    meta->languages.push_back(l.get<std::string>());
                }

                MMT_LOG_DEBUG("Loaded meta config: " + std::to_string(meta->languages.size()));
            }
            catch (const std::exception& e)
            {
                MMT_LOG_ERROR("Failed to load meta config: " + std::string(e.what()));
            }
        }

        void Config::SaveMetaConfig(picojson::value::object& obj)
        {
            picojson::value::object metaObj;

            ToJson(
                metaObj,
                MMT_SERIALIZE(meta->resourceRelPath)
            );

            picojson::value::array langs;
            for (const auto& l : meta->languages)
            {
                langs.emplace_back(picojson::value(l));
            }
            metaObj["available_languages"] = picojson::value(langs);

            picojson::value val(metaObj);
            obj["meta"] = val;
        }

        // -----------------------------------------------------------------

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