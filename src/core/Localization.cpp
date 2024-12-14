#include "Localization.h"

#include "log/loguru.hpp"

namespace mmt
{
    namespace core
    {
        MultiStr& MultiStr::Add(const std::string& lang, const std::string& str)
        {
            langMap[lang] = str;
            return *this;
        }
        const std::string& MultiStr::operator()() const
        {
            return langMap.at(Config::GetInstance().settings->appLanguage);
        }
        const std::string& MultiStr::operator()(const std::string& lang) const
        {
            return langMap.at(lang);
        }

        // -------------------

        bool Localization::Load(const std::filesystem::path& relPath)
        {
            try
            {
                DLOG_F(INFO, "Loading loc...");

                auto cwd = std::filesystem::current_path();
                std::ifstream file(cwd / relPath);
                std::stringstream contents;
                contents << file.rdbuf();

                std::string strCont = contents.str();
                picojson::value val;

                std::string err = picojson::parse(val, strCont);
                if (!err.empty()) throw std::runtime_error("Failed to parse localization file: " + err);

                DLOG_F(INFO, "Parsed localization file");

                if (!val.is<picojson::object>()) throw std::runtime_error("Localization json is not an object");
                const picojson::value::object& obj = val.get<picojson::object>();

                LoadLocInfo(obj);

                DLOG_F(INFO, "Loaded localization");
                DLOG_F(INFO, "Loc map size: %i", locMap.size());
            }
            catch (const std::exception& e)
            {
                LOG_F(ERROR, "Failed to load localization: %s", e.what());
            }
        }
        const std::unordered_map<std::string, MultiStr>& Localization::GetMap() const
        {
            return locMap;
        }
        void Localization::LoadLocInfo(const picojson::value::object& obj)
        {
            try
            {
                const auto& langs = Config::GetInstance().settings->metaLanguages;
                for (const auto& lang : langs)
                {
                    for (const auto& entry : obj)
                    {
                        LoadEntry(obj, entry.first, lang);
                    }
                }
            }
            catch (const std::exception& e)
            {
                LOG_F(ERROR, "Failed to load localization info");
            }
        }
        void Localization::LoadEntry(const picojson::value::object& obj, const std::string& id, const std::string& lang)
        {
            try
            {
                const auto& entry = obj.at(id).get<picojson::object>();
                std::string str = entry.at(lang).get<std::string>();
                locMap[id].Add(lang, str);
            }
            catch (const std::exception& e)
            {
                LOG_F(ERROR, "Failed to load localization entry: %s", id);
            }
        }
    }
}