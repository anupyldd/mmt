#include "Log.h"

namespace mmt
{
    namespace util
    {
        void Log::ConsoleDebug(const std::string& msg)
        {
#if _DEBUG
            std::unique_lock lock{ mtx };
            std::cout << std::format("[DEBUG]\t{}\n", msg);
#endif
        }
        void Log::ConsoleInfo(const std::string& msg)
        {
            std::unique_lock lock{ mtx };
            std::cout << std::format("[INFO]\t{}\n", msg);
        }
        void Log::ConsoleError(const std::string& msg)
        {
            std::unique_lock lock{ mtx };
            std::cout << std::format("[ERROR]\t{}\n", msg);
        }
    }
}