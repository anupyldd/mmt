#pragma once

#include "Defines.h"

#include <string>
#include <mutex>
#include <chrono>
#include <format>
#include <iostream>

namespace hnd
{
    namespace util
    {
        class Log
        {
            SINGLETON(Log);

        public:
            void ConsoleDebug(const std::string& msg);
            void ConsoleInfo(const std::string& msg);
            void ConsoleError(const std::string& msg);

        private:
            std::mutex m_mtx;
        };
    }
    
    #define LOG util::Log::GetInstance()
    #define LOG_DEBUG(msg) util::Log::GetInstance().ConsoleDebug(msg)
    #define LOG_INFO(msg) util::Log::GetInstance().ConsoleInfo(msg)
    #define LOG_ERROR(msg) util::Log::GetInstance().ConsoleError(msg)
}
