#pragma once

#include <string>

#include "Test.hpp"

class Log
{
    std::string path;
    std::list<std::string> entries;

    std::string generateLogName();
    std::string getTimestamp();

public:
    Log();
    ~Log() = default;

    void addEntry(std::string entry);
    void addSummary(Test &test);
    void addBriefSummary(std::list<Test> &tests);
    void printToLog();
};