#include "Config.h"

#include "rfl.hpp"
#include "rfl/json.hpp"
#include "log/loguru.hpp"

namespace mmt
{
    namespace core
    {
        using namespace util;

        bool Config::Load(const std::filesystem::path& relPath)
        {
            settings = std::make_unique<Settings>();

            try
            {
                auto cwd = std::filesystem::current_path();
                std::ifstream file(cwd / relPath);

                DLOG_F(INFO, (cwd / relPath).string().c_str());

                std::stringstream contents;
                contents << file.rdbuf();

                std::string strCont = contents.str();
                
                (*settings) = rfl::json::read<Settings>(strCont).value();

                return true;
            }
            catch (const std::exception& e)
            {
                LOG_F(ERROR, "Failed to load config: %s", std::string(e.what()));
            }
        }

        void Config::Save(const std::filesystem::path& relPath)
        {
            try
            {
                auto cwd = std::filesystem::current_path();
                std::ofstream file(cwd / relPath);

                std::string str = rfl::json::write(*settings, YYJSON_WRITE_PRETTY);

                file << str;

                DLOG_F(INFO, "Saved config");
            }
            catch (const std::exception& e)
            {
                LOG_F(ERROR, "Failed to save config: %s", std::string(e.what()));
            }
        }

        unsigned int Config::GetWindowFlags() const
        {
            if (!settings) return 0;

            unsigned int flags = 0;
            for (const auto& f : settings->appFlags)
            {
                flags |= WindowFlagFromStr(f);
            }
            return flags;
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