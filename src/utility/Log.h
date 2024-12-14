#pragma once

#include "Defines.h"

#include "log/loguru.hpp"

#include <chrono>
#include <format>
#include <filesystem>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <sstream>

namespace mmt
{
    namespace util
    {
        class Log
        {
            MMT_SINGLETON(Log);

        public:
            void InitSession();
        };
    }
}
