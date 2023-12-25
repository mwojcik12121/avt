#include <filesystem>
#include <fstream>
#include <iostream>

#include "AVType.hpp"

int ClamAV::executeTest(std::string id)
{
    system(std::string("tar -xvf testfiles/" + id + ".tar -C .workspace " + id).c_str());
    system(std::string("clamscan --quiet -l" + logpath + " .workspace/" + id).c_str());
    if(verifyAVLog(std::string(".workspace/" + id)) != "") return 1;
    else return 0;
}

std::string ClamAV::verifyAVLog(std::string testpath)
{
    std::ifstream log(logpath, std::ios::in);
    std::string line;

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
    
    return "";
}

int DrWeb::executeTest(std::string id)
{
    system(std::string("tar -xvf ./testfiles/" + id + ".tar -C .workspace " + id).c_str());
    if(!std::filesystem::exists(std::string(std::filesystem::current_path().string()+"/.workspace/" + id))) return 1;
    else return system(std::string("." + std::string(std::filesystem::current_path().string()+"/.workspace/" + id)).c_str());
    return 0;
}

std::string DrWeb::verifyAVLog(std::string testpath)
{
    return "";
}

int Sophos::executeTest(std::string id)
{
    system(std::string("tar -xvf ./testfiles/" + id + ".tar -C .workspace " + id).c_str());
    if(!std::filesystem::exists(std::string(std::filesystem::current_path().string()+"/.workspace/" + id))) return 1;
    else return system(std::string("." + std::string(std::filesystem::current_path().string()+"/.workspace/" + id)).c_str());
    return 0;
}

std::string Sophos::verifyAVLog(std::string testpath)
{
    std::string logline;
    return "";
}
