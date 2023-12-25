#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>

#include "Log.hpp"

using clock_c = std::chrono::system_clock;

Log::Log()
{
    path = std::filesystem::current_path().string() + generateLogName();
    addEntry("### AVT TEST CASE ###\n");
    addEntry("\n");
}

std::string Log::getTimestamp()
{
    std::chrono::time_point<clock_c> datetime = clock_c::now();
    return std::format("[ {:%Y-%m-%d %H:%M:%S} ] ", floor<std::chrono::seconds>(datetime));
}

void Log::addEntry(std::string entry)
{
    std::string line = getTimestamp() + entry;
    entries.emplace_back(line);
}

void Log::addSummary(Test &test)
{
    Results res = test.getResult();
    
    addEntry(std::string("Test: "+test.getId()+"\n"));
    if(res.status > 0)
    {
        addEntry(std::string("\t\t\tStatus: SUCCESS\n"));
        addEntry(std::string("\t\t\tElapsed time: " + (res.elapsed > 0 ? (std::to_string(res.elapsed) + "ms\n") : "N/A\n")));
        addEntry(std::string("\t\t\tDetected threat: " + (res.detected != "" ? (res.detected + "\n") : "N/A\n")));
    }
    if(res.status == 0) addEntry(std::string("\t\t\tStatus: FAILED\n"));

    addEntry("\n");
}

void Log::addBriefSummary(std::list<Test> &tests)
{
    Results res;

    addEntry("TEST SUMMARY\n");
    addEntry("\n");
    
    for(auto t : tests)
    {
        res = t.getResult();
        if(res.status == 0) addEntry(std::string("\t\t\t"+t.getId()+" ("+t.getType()+"): FAILED\n"));
        if(res.status > 0) addEntry(std::string("\t\t\t"+t.getId()+" ("+t.getType()+"): SUCCESS\n"));
        if(res.status < 0) addEntry(std::string("\t\t\t"+t.getId()+" ("+t.getType()+"): UNDEFINED\n"));
    }
}

void Log::printToLog()
{
    addEntry("\n");
    addEntry("### END OF TEST CASE ###");
    
    std::ofstream logfile(path);
    for (auto ent : entries) logfile << ent;
}

std::string Log::generateLogName()
{
    std::string filename = "/logs/test_";

    std::chrono::time_point<clock_c> datetime = clock_c::now();
    filename += std::format("{:%Y%m%d_%H%M%S}", floor<std::chrono::seconds>(datetime));

    return filename + ".log";
}
