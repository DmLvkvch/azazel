#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Azazel
{
    class Modifier
    {
    public:
        enum class Code
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

        Modifier(Code code) : code(code) {}

        friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) 
        {
            int color = (int) mod.code;
            return os <<"\033["<< color <<"m";
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
            std::cout<<red<<"Log::Error. "<<log<<def<<std::endl;
        }

		inline void warnLog(const std::string& log) 
        { 
            std::cout<<blue<<"Log::Warn. "<<log<<def<<std::endl;
        }

		inline void infoLog(const std::string& log) 
        {
            std::cout<<green<<"Log::Info. "<<log<<def<<std::endl;
		}

        static Log* getLogger()
        {
            return Log::logger.get();
        }
        
    private:
        static std::unique_ptr<Log> logger;
        Modifier red   {Modifier::Code::FG_RED};
        Modifier green {Modifier::Code::FG_GREEN};
        Modifier blue  {Modifier::Code::FG_BLUE};
        Modifier def   {Modifier::Code::DEF};
    };
}