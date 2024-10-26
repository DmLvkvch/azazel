#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Azazel
{
    enum class Code : uint32_t
    {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49,
        DEF         = 0
    };

    class Modifier
    {
    public:

        Modifier(Code code) : code(code) {}

        friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) 
        {
            return os <<"\033["<< (int) mod.code <<"m";
        }

    private:
        Code code;
    };

    class Log
    {
    public:
        Log();

        ~Log();

        inline void errorLog(const std::string& log) 
        {
            std::cout<<red<<"Log::Error:: "<<log<<def<<std::endl;
        }

		inline void warnLog(const std::string& log) 
        { 
            std::cout<<blue<<"Log::Warn:: "<<log<<def<<std::endl;
        }

		inline void infoLog(const std::string& log) 
        {
            std::cout<<green<<"Log::Info:: "<<log<<def<<std::endl;
		}

        static Log& getLogger()
        {
            static Log logger;
            return logger;
        }
        
    private:
        Modifier red   {Code::FG_RED};
        Modifier green {Code::FG_GREEN};
        Modifier blue  {Code::FG_BLUE};
        Modifier def   {Code::DEF};
    };
}