#pragma once

#include <string>
#include <list>

#include "Test.hpp"
#include "Log.hpp"

class Tester
{
    Log log;
    avt::AVType avtype = avt::AVType::None;

    bool do_perftest = false;
    bool do_acctest = false;

    std::string testdir;

    bool verifyAVLogs(std::string expected);
    
public:
    Tester() = default;
    Tester(std::string perftest, std::string acctest);
    ~Tester() = default;

    void performTests(std::list<Test>& tests);
};