#include <filesystem>

#include "Tester.hpp"

Tester::Tester(std::string perftest, std::string acctest, std::shared_ptr<AVType> av)
{
    if(perftest != "0" || perftest != "1")
        throw std::invalid_argument("\nIncorrect parameter for: doPerformanceTest");

    if(acctest != "0" || acctest != "1")
        throw std::invalid_argument("\nIncorrect parameter for: doAccuracyTest");

    do_acctest = std::stoi(acctest);
    do_perftest = std::stoi(perftest);
    log = Log();
    avtype = av;
}

void Tester::performTests(std::list<Test>& tests)
{
    log.addEntry("Activating tests...");
    log.addEntry("");
    log.addEntry("");
    
    for(auto it : tests)
    {
        log.addEntry(std::string("Test " + it.getId() + " in progress..."));
        it.executeTest(do_perftest, do_acctest, avtype);
        log.addEntry(std::string("Test " + it.getId() + " has been completed."));
        log.addEntry("");
        log.addSummary(it);
        log.addEntry("");
    }

    log.addEntry("");
    log.addEntry("");
    log.addEntry("");
    log.addBriefSummary(tests);
    log.printToLog();
}