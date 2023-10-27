#include "Log.h"

namespace Azazel
{
    std::unique_ptr<Log> Log::logger (new Log());

    Log::Log()
    {
        std::cout << "Logger constructor" << std::endl;
    }

    Log::~Log()
    {
        std::cout << "Logger destructor" << std::endl;
    }
}