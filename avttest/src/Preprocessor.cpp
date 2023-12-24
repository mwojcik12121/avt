#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

#include "Preprocessor.hpp"

Preprocessor::Preprocessor()
{
    directory = std::filesystem::current_path().string() + "/testfiles";
}

std::list<Test> Preprocessor::prepareTests(std::list<std::string> &testnames)
{
    std::list<Test> testlist;
    
    for(const auto & entry : std::filesystem::directory_iterator(directory))
    {
        std::string testfile = entry.path().filename().string();
        std::string filename = entry.path().stem().string();

        if(std::find(testnames.begin(), testnames.end(), testfile) != testnames.end() &&
            std::regex_match(testfile, std::regex("[A-Z]{2}-[0-9]{4}.tar")))
        {
            unpackTar(testfile);

            if(std::filesystem::exists(std::string(".workspace/" + filename)) &&
                std::filesystem::exists(std::string(".workspace/" + filename + ".info")))
            {
                Test current;
                if(importTest(std::string(".workspace/" + filename + ".info"), current))
                    testlist.emplace_back(current);
                else std::cout << testfile << ": Invalid info file format! Test has been skipped.";
            }
            else std::cout << testfile << ": Invalid info file format! Test has been skipped.";
        }
        else std::cout << testfile << ": Invalid info file format! Test has been skipped.";
    }

    if(testlist.empty())
        throw("No valid tests detected in " + directory);

    return testlist;
}

bool Preprocessor::importTest(std::string file, Test &test)
{
    int getline_it = 0;
    std::string line, id, type; 

    std::ifstream filestream(file, std::ifstream::in);

    while(!filestream.eof())
    {
        if(getline_it>2) break;

        filestream >> line;

        if(!validateLine(getline_it, line))
            return false;

        switch(getline_it)
        {
            case 1:
                id = line;
                break;
            case 2:
                type = line;
                break;
            default:
                break;
        }
        getline_it++;
    }

    test = Test(id, type);
    return true;
}

void Preprocessor::unpackTar(std::string filepath)
{
    if(!std::filesystem::is_directory(std::string(std::filesystem::current_path().string()+"/workspace")))
        system("mkdir .workspace");

    std::string cmd = "tar -xvf " + filepath + " -C .workspace";
    system(cmd.c_str());
}

bool Preprocessor::validateLine(int index, std::string line)
{
    switch(index)
    {
        case 0:
            return line == "#TEST#";
            break;
        case 1:
            return std::regex_match(line, std::regex("[A-Z]{2}-[0-9]{4}"));
            break;
        default:
            break;
    }
}
