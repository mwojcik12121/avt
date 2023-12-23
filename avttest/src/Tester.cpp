#include <thread>
#include <vector>

#include "Tester.hpp"

Tester::Tester(std::string perftest, std::string acctest)
{
    if(perftest != "0" || perftest != "1")
        throw("Incorrect parameter for: doPerformanceTest");

    if(acctest != "0" || acctest != "1")
        throw("Incorrect parameter for: doAccuracyTest");

    do_acctest = std::stoi(acctest);
    do_perftest = std::stoi(perftest);
    log = Log();
}

void Tester::performTests(std::list<Test>& tests)
{
    log.addEntry("Testing has begun!");
    log.addEntry("");
    log.addEntry("Activating tests...!");
    log.addEntry("");
    log.addEntry("");
    
    for(auto it : tests)
    {
        log.addEntry(std::string("Test " + it.getId() + " in progress..."));
        it.executeTest(do_perftest, do_acctest, avtype);
        log.addEntry(std::string("Test " + it.getId() + " has been completed."));
        log.addSummary(it);
    }

    log.addBriefSummary(tests);
    log.printToLog();
}