#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <thread>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "AVType.hpp"

int ClamAV::executeTest(std::string id)
{
    system(std::string("tar -xvf testfiles/" + id + ".tar -C .workspace " + id + " > /dev/null").c_str());
    system(std::string("clamscan --quiet -l " + logpath + " .workspace/" + id + " > /dev/null").c_str());
    
    std::string line = "";
    std::ifstream clamlog(logpath);

    if(clamlog)
    {
        while(!clamlog.eof())
        {
            clamlog >> line;
            if(line == "Infected")
            {
                clamlog >> line;
                if(line == "files:")
                {
                    clamlog >> line;
                    if(std::stoi(line) > 0) return 1;
                    else return 0;
                }
            }
        }
    }
    return 0;
}

std::string ClamAV::verifyAVLog(std::string testpath)
{
    std::ifstream log(logpath, std::ios::in);
    std::string line;

    if(log)
    {
        while(!log.eof())
        {
            log >> line;
            size_t found = line.find(testpath);
            if(found != std::string::npos)
            {
                log >> line;
                return line;
            }
        }
        return "Not found";
    }
    return "";
}

int DrWeb::executeTest(std::string id)
{
    
    
    // system(std::string("tar -xvf testfiles/" + id + ".tar -C .workspace " + id + " > /dev/null").c_str());
    // std::this_thread::sleep_for(std::chrono::milliseconds(250));
    // if(!std::filesystem::exists(std::string(std::filesystem::current_path().string()+"/.workspace/" + id))) return 1;
    // int retval = system(std::string(std::filesystem::current_path().string()+"/.workspace/" + id + " > /dev/null").c_str());
    // return retval;
    return 0;
}

std::string DrWeb::verifyAVLog(std::string testpath)
{
    system(std::string("ls -t " + logpath + "/*.i2 | head -n1 >> .workspace/newest").c_str());
    std::ifstream drweblog(".workspace/newest", std::ios::in | std::ios::binary);
    std::string lpath = "";
    while(!drweblog.eof()) drweblog >> lpath;

    std::ifstream log(std::string(lpath), std::ios::in | std::ios::binary);
    std::string line = "", detected = "";
    int count = 0;

    if(log)
    {
        while(!log.eof())
        {
            if(count == 3) break;
            std::getline(log, line);
            count++;
        }

        if(!line.empty())
        {
            size_t found = line.find(testpath);
            if(found != std::string::npos)
            {
                for(int i=found+testpath.length()+8;; i++)
                {
                    detected += line[i];
                    if(line[i+1] == 'X' && line[i+3] == 'r') break;
                }
                return detected;
            }
        }
        return "Not found";
    }
    return "";
}

int Sophos::executeTest(std::string id)
{
    system(std::string("tar -xvf testfiles/" + id + ".tar -C .workspace " + id + " > /dev/null").c_str());
    if(!std::filesystem::exists(std::string(std::filesystem::current_path().string()+"/.workspace/" + id))) return 1;
    int retval = system(std::string(std::filesystem::current_path().string()+"/.workspace/" + id + " > /dev/null").c_str());
    return retval;
}

std::string Sophos::verifyAVLog(std::string testpath)
{
    system(std::string("./scripts/get_sophos_logs " + logpath).c_str());
    
    std::ifstream log(".workspace/savd.log", std::ios::in);
    std::string line = "", detected = "", tmp = "";

    if(log)
    {
        while(!log.eof())
        {
            std::getline(log, tmp);
            if(!tmp.empty()) line = tmp;
        }

        if(!line.empty())
        {
            size_t found = line.find(testpath);
            if(found != std::string::npos)
            {
                for(int i=found+testpath.length()+11; line[i] != '<'; i++) detected += line[i];
                return detected;
            }
        }
        return "Not found";
    }
    return "";
}
