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

        if(std::find(testnames.begin(), testnames.end(), filename) != testnames.end() &&
            std::regex_match(testfile, std::regex("[A-Z]{2}-[0-9]{4}.tar")))
        {
            unpackTarInfo(testfile);

            if(std::filesystem::exists(std::string(".workspace/" + filename + ".info")))
            {
                Test current;
                if(importTest(std::string(".workspace/" + filename + ".info"), current))
                    testlist.emplace_back(current);
                else std::cout << testfile << ": Invalid info file format! Test has been skipped.\n";
            }
            else std::cout << testfile << ": Invalid info file format! Test has been skipped.\n";
        }
    }

    if(testlist.empty())
        throw std::length_error("\nNo valid tests detected in " + directory);

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

void Preprocessor::unpackTarInfo(std::string filepath)
{
    if(!std::filesystem::is_directory(std::string(std::filesystem::current_path().string()+"/.workspace")))
        system("mkdir .workspace");

    std::filesystem::path file = std::filesystem::path(filepath);
    system(std::string("tar -xvf ./testfiles/" + filepath + " -C .workspace " + file.stem().string() + ".info").c_str());
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
    return true;
}

std::shared_ptr<AVType> Preprocessor::getAVType()
{
    bool av[3] = {0};
    int av_count = 0;

    if(std::filesystem::exists("/var/log/clamav/clamav.log")) av[0] = 1;
    if(std::filesystem::exists("")) av[1] = 1;
    if(std::filesystem::exists("/opt/sophos-av/log/savd.log")) av[2] = 1;
    
    for(int i=0; i<3; i++) if(av[i]) av_count++;

    if(av_count > 1) throw std::invalid_argument("\nMore than one antivirus software detected! Please, make sure all additional antivirus software and its logs are deleted from your device");
    else if(av_count < 1) std::invalid_argument("\nNo compatible antivirus software detected!");
    
    std::shared_ptr<AVType> avtype;

    if(av[0])
    {
        avtype = std::make_shared<ClamAV>();
        avtype->logpath = ".workspace/clamav.log";
    }
    else if(av[1])
    {
        // TODO: find and add log path
        
        avtype = std::make_shared<DrWeb>();
        avtype->logpath = "";
    }
    else if(av[2])
    {
        avtype = std::make_shared<Sophos>();
        avtype->logpath = "/opt/sophos-av/log/savd.log";
    }
    return avtype;
}
