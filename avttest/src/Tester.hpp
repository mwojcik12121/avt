#pragma once

#include <string>
#include <list>

#include "Test.hpp"

class Tester
{
    bool do_perftest = false;
    bool do_acctest = false;

public:
    Tester(std::string perftest, std::string acctest);
    ~Tester();

    void performTests(std::list<Test>& tests);
};