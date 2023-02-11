#include "Log.h"

namespace Azazel
{
    std::unique_ptr<Log> Log::logger (new Log());

    Log::Log()
    {
    }

    Log::~Log()
    {
    }
}