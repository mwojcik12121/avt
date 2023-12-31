#pragma once

#include <string>
#include <list>

#include "Test.hpp"
#include "Log.hpp"

class Tester
{
    Log log;
    std::shared_ptr<AVType> avtype;

    bool do_perftest = false;
    bool do_acctest = false;
    
public:
    Tester() = default;
    Tester(std::string perftest, std::string acctest, std::shared_ptr<AVType> av);
    ~Tester() = default;

    void performTests(std::list<Test>& tests);
};