#include "Localization.h"
#include "Localization.h"

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
            return langMap.at(Config::GetInstance().app->language);
        }
        const std::string& MultiStr::operator()(const std::string& lang) const
        {
            return langMap.at(lang);
        }

        // -------------------

        bool Localization::Load(const std::filesystem::path& relPath)
        {
            MMT_LOG_DEBUG("Loading loc...");

            auto cwd = std::filesystem::current_path();
            std::ifstream file(cwd / relPath);
            std::stringstream contents;
            contents << file.rdbuf();

            std::string strCont = contents.str();
            picojson::value val;

            std::string err = picojson::parse(val, strCont);
            if (!err.empty()) throw std::runtime_error("Failed to parse localization file: " + err);

            MMT_LOG_DEBUG("Parsed localization file");

            if (!val.is<picojson::object>()) throw std::runtime_error("Localization json is not an object");
            const picojson::value::object& obj = val.get<picojson::object>();

            LoadLocInfo(obj);

            MMT_LOG_DEBUG("Loaded localization");
            MMT_LOG_DEBUG("Loc map size: " + std::to_string(locMap.size()));
        }
        const std::unordered_map<std::string, MultiStr>& Localization::GetMap() const
        {
            return locMap;
        }
        void Localization::LoadLocInfo(const picojson::value::object& obj)
        {
            try
            {
                const auto& langs = Config::GetInstance().meta->languages;
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
                MMT_LOG_ERROR("Failed to load localization info");
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
                MMT_LOG_ERROR("Failed to load localization entry: " + id);
            }
        }
    }
}