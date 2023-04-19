#include "Log.h"
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
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