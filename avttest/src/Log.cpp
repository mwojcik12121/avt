#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>

#include "Common.hpp"
#include "Log.hpp"

Log::Log()
{
    path = std::filesystem::current_path().string() + generateLogName();
    addEntry("### AVT TEST CASE ###");
}

std::string Log::getTimestamp()
{
    std::chrono::time_point<avt::clock> datetime = avt::clock::now();
    return std::format("[ %Y-%m-%d %H:%M:%S ] ", datetime);
}

void Log::addEntry(std::string entry)
{
    std::string line = getTimestamp() + entry;
    std::cout << line << std::endl;
    entries.emplace_back(line);
}

void Log::addSummary(Test &test)
{
    Results res = test.getResult();
    
    addEntry(std::string("Test: "+test.getId()));
    addEntry(std::string("Status: "+res.nstage==0?"FAILED":"SUCCESS"));
    addEntry(std::string("Elapsed time: "+res.elapsed>0?std::to_string(res.elapsed):"N/A"));
    addEntry(std::string("Threat (expected): "+test.getType()));
    addEntry(std::string("Threat (detected): "+test.getType()!=""?test.getType():"N/A"));
}

void Log::addBriefSummary(std::list<Test> &tests)
{
    Results res;

    addEntry("TEST SUMMARY");
    addEntry("");
    addEntry("");
    
    for(auto t : tests)
    {
        res = t.getResult();
        addEntry(std::string("\t\t"+t.getId()+"("+t.getType()+"): "+(res.nstage==0?"FAILED":"SUCCESS")));
        addEntry("");
    }
}

void Log::printToLog()
{
    addEntry("### END OF TEST CASE ###");
    
    std::ofstream logfile(path);
    for (auto ent : entries) logfile << ent;
}

std::string Log::generateLogName()
{
    std::string filename = "/logs/test_";

    std::chrono::time_point<avt::clock> datetime = avt::clock::now();
    filename += std::format("%Y%m%d%H%M%S", datetime);

    return filename + ".log";
}
