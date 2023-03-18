#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace Azazel
{
    class FileUtils
    {
    public:
        static std::string readFile(const std::string& file)
        {
            std::fstream stream (file);
            if (!stream.is_open()) 
            {
                std::cout << "Could not open the file - '" << file << "'" << std::endl;
            }
            return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        }
    };
}