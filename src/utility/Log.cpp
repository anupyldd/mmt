#include "Log.h"

namespace mmt
{
	namespace util
	{
		void Log::InitSession()
        {
            auto path = std::filesystem::current_path() / "data" / "session";
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            std::stringstream dtstr;
            dtstr << std::put_time(&tm, "%Y-%m-%d %H-%M-%S");
            path = path / (dtstr.str() + ".log");
            loguru::add_file(path.string().c_str(), loguru::FileMode::Truncate, loguru::Verbosity_MAX);
        }
	}
}