#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

#include "Preprocessor.hpp"

Preprocessor::Preprocessor(std::string dir)
{
    std::filesystem::is_directory(dir) ? directory = dir : throw("Directory does not exist");
}

std::list<Test> Preprocessor::prepareTests(std::list<std::string> &testnames)
{
    std::list<Test> testlist;
    
    for(const auto & entry : std::filesystem::directory_iterator(directory))
    {
        std::string testfile = entry.path().filename().string();

        if(std::find(testnames.begin(), testnames.end(), testfile) != testnames.end() &&
            std::regex_match(testfile, std::regex("[A-Z]{2}-[0-9]{4}")))
        {
            Test current;
            if(importTest(entry.path().string(), current))
                testlist.emplace_back(current);
            else std::cout << testfile << ": Invalid info file format! Test has been skipped.";
        }
    }

    if(testlist.empty())
        throw("No valid tests detected in " + directory);

    return testlist;
}

bool Preprocessor::importTest(std::string file, Test &test)
{
    int getline_it = 0;
    std::string line, id, type;
    std::list<avt::StageMap> stages;

    std::ifstream filestream("x.txt", std::ifstream::in);

    while(!filestream.eof())
    {
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
            case 3:
                break;
            default:
                stages.emplace_back(createMapEntry(line));
                break;
        }
        getline_it++;
    }

    test = Test(id, type, stages);
    return true;
}

void Preprocessor::unpackTar(std::string file)
{
    std::string cmd = "tar -xvf " + file;
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
        case 2:
            break;
        case 3:
            break;
        default:
            std::regex_match(line, std::regex("[0-9]{2}-[0-9]{4}"));
            break;
    }
}

avt::StageMap Preprocessor::createMapEntry(std::string line)
{
    std::string nmb, stage;

    for(int i = 0; line[i] != ';'; i++)
    {
        nmb += line[i];
        line.erase(0, 1);
    }

    line.erase(0, 1);
    stage = line;
    
    return std::make_tuple(std::stoi(nmb), stage);
}