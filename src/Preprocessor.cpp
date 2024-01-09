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

        if(testfile == "README.md") continue;

        try
        {
            // Sprawdzanie formatu nazwy archiwum oraz czy istnieje w folderze testfiles
            if(std::find(testnames.begin(), testnames.end(), filename) != testnames.end() &&
                std::regex_match(testfile, std::regex("[A-Z]{2}-[0-9]{4}\.tar")))
            {
                // Wypakuj plik informacyjny
                unpackTarInfo(testfile);

                // Dodaj test do listy testow do wykonania
                if(std::filesystem::exists(std::string(".workspace/" + filename + ".info")))
                {
                    Test current;
                    if(importTest(std::string(".workspace/" + filename + ".info"), current))
                        testlist.emplace_back(current);
                    else throw std::runtime_error("Invalid .info file format!");
                }
                else throw std::runtime_error("Could not find .info file!");
            }
            else
            {
                if(std::find(testnames.begin(), testnames.end(), filename) == testnames.end()) continue;
                else std::cout << testfile << ": Skipping test..." << std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            std::cout << testfile << ": Skipping test..." << std::endl;
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

    if(!filestream) throw std::runtime_error("Could not open .info file!");

    while(!filestream.eof())
    {
        if(getline_it>2) break;

        filestream >> line;
        if(!validateLine(getline_it, line))
            return false;

        switch(getline_it)
        {
            case 1:
                id = line; break;
            case 2:
                type = line; break;
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
    // Wypakuj plik informacyjny z archiwum testu
    std::filesystem::path file = std::filesystem::path(filepath);
    int retval = system(std::string("tar -xvf ./testfiles/" + filepath + " -C .workspace " +
                        file.stem().string() + ".info > /dev/null 2> /dev/null").c_str());
    if (retval != 0) throw std::runtime_error("Could not extract .info file!");
}

bool Preprocessor::validateLine(int index, std::string line)
{
    switch(index)
    {
        case 0:
            return line == "#TEST#"; break;
        case 1:
            return std::regex_match(line, std::regex("[A-Z]{2}-[0-9]{4}")); break;
        default:
            break;
    }
    return true;
}

std::shared_ptr<AVType> Preprocessor::getAVType()
{
    bool av[3] = {0};       // av[0] - ClamAV, av[1] - DrWeb, av[2] - Sophos
    int av_count = 0;

    // Sprawdz czy istnieje plik programu ClamAV
    if(std::filesystem::exists("/var/log/clamav/clamav.log")) av[0] = 1;

    // Sprawdz czy istnieje folder programu DrWeb
    system("find / -path \*/.com.drweb.quarantine >> .workspace/drweb.path 2> /dev/null");
    std::ifstream drweb(".workspace/drweb.path");
    std::string dpath = "";
    if(drweb.peek() != std::ifstream::traits_type::eof())
    {
        drweb >> dpath;
        if(std::filesystem::exists(dpath)) av[1] = 1;
    }
    if(std::filesystem::exists("/.com.drweb.quarantine")) av[1] = 1;

    // Sprawdz czy istnieje plik programu Sophos
    system("./scripts/get_sophos_path");
    std::ifstream sophos(".workspace/sophos.path");
    std::string spath = "";
    if(sophos.peek() != std::ifstream::traits_type::eof())
    {
        sophos >> spath;
        if(std::filesystem::exists(spath)) av[2] = 1;
    }
    
    for(int i=0; i<3; i++) if(av[i]) av_count++;

    if(av_count > 1) throw std::invalid_argument("\nMore than one antivirus software detected! Please, make sure all additional antivirus software and its logs are deleted from your device");
    else if(av_count < 1) throw std::invalid_argument("\nNo compatible antivirus software detected!");
    
    std::shared_ptr<AVType> avtype;

    if(av[0])       // ClamAV
    {
        avtype = std::make_shared<ClamAV>();
        avtype->logpath = ".workspace/clamav.log";
    }
    else if(av[1])  // DrWeb
    {
        avtype = std::make_shared<DrWeb>();
        avtype->logpath = dpath;
    }
    else if(av[2])  // Sophos
    {
        avtype = std::make_shared<Sophos>();
        avtype->logpath = spath;
    }
    return avtype;
}
