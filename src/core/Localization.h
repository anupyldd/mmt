#pragma once

#include "../utility/Log.h"
#include "../utility/Defines.h"
#include "Config.h"

#include "picojson.h"

#include <unordered_map>
#include <string>
#include <filesystem>

namespace mmt
{
    namespace core
    {
        class MultiStr
        {
        public:
            MultiStr() = default;

            MultiStr& Add(const std::string& lang, const std::string& str);

            const std::string& operator()() const; // get string in current app language
            const std::string& operator()(const std::string& lang) const; // get string in specified language

        private:
            std::unordered_map<std::string, std::string> langMap;
        };

        // ----------------------

        class Localization
        {
            MMT_SINGLETON(Localization);

        public:
            bool Load(const std::filesystem::path& relPath);
            const std::unordered_map<std::string, MultiStr>& GetMap() const;

        private:
            void LoadLocInfo(const picojson::value::object& obj);
            void LoadEntry(const picojson::value::object& obj, const std::string& id, const std::string& lang);

        private:
            std::unordered_map<std::string, MultiStr> locMap;
        };

        // ----------------------
        // use this for shorter syntax
        const std::string locError = "INVALID_STRING";

        inline std::string Loc(const std::string& str)
        {
            try
            {
                return Localization::GetInstance().GetMap().at(str)();
            }
            catch (...)
            {
                return locError;
            }
        }
        inline std::string Loc(const std::string& lang, const std::string& str)
        {
            try
            {
                return Localization::GetInstance().GetMap().at(str)(lang);
            }
            catch (...)
            {
                return locError;
            }
        }

        // return c-string
        inline auto LocC(const std::string& str)
        {
            try
            {
                return Localization::GetInstance().GetMap().at(str)().c_str();
            }
            catch (...)
            {
                return locError.c_str();
            }
        }
        inline auto LocC(const std::string& lang, const std::string& str)
        {
            try
            {
                return Localization::GetInstance().GetMap().at(str)(lang).c_str();
            }
            catch (...)
            {
                return locError.c_str();
            }
        }
    }
}