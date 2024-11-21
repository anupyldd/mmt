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
            HND_SINGLETON(Log);

        public:
            void ConsoleDebug(const std::string& msg);
            void ConsoleInfo(const std::string& msg);
            void ConsoleError(const std::string& msg);

        private:
            std::mutex mtx;
        };
    }
    
    #define HND_LOG util::Log::GetInstance()
    #define HND_LOG_DEBUG(msg) util::Log::GetInstance().ConsoleDebug(msg)
    #define HND_LOG_INFO(msg) util::Log::GetInstance().ConsoleInfo(msg)
    #define HND_LOG_ERROR(msg) util::Log::GetInstance().ConsoleError(msg)
}
