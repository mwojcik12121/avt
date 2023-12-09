#include <filesystem>
#include <fstream>
#include <regex>

#include "Preprocessor.hpp"

//"[A-Z]-[0-9]"

auto list_valid = [](std::string dir)
{
    for(const auto & entry : std::filesystem::directory_iterator(dir))
    {  
         return true;
    }
};

Preprocessor::Preprocessor(std::string dir)
{
    std::filesystem::is_directory(dir) ? directory = dir: throw("Directory does not exist");
}

std::list<Test> Preprocessor::prepareTests()
{
    if(std::filesystem::is_empty(directory))
    {
        throw(directory + ": directory is empty.");
    }

    std::list<Test> testlist;
    
    for(const auto & entry : std::filesystem::directory_iterator(directory))
    {
        std::string path = entry.path().u8string();
        
        if(std::regex_match(path, std::regex("[A-Z]{2}-[0-9]{4}")))
        {
            if(validateTestFile(path))
            {
                testlist.emplace_back(importTest(path));
            }
        }
    }

    if(testlist.empty())
    {
        throw("No valid tests detected in " + directory);
    }

    return testlist;
}

bool Preprocessor::validateTestFile(std::string file)
{
    
}