#include <filesystem>
#include <iostream>

#include "Tester.hpp"

Tester::Tester(std::string perftest, std::string acctest, std::shared_ptr<AVType> av)
{
    do_acctest = std::stoi(acctest);
    do_perftest = std::stoi(perftest);
    log = Log();
    avtype = av;
}

void Tester::performTests(std::list<Test>& tests)
{
    log.addEntry("Activating tests...\n");
    log.addEntry("\n");
    log.addEntry("\n");

    for(auto& it : tests)
    {
        log.addEntry(std::string("Test " + it.getId() + " in progress...\n"));
        it.executeTest(do_perftest, do_acctest, avtype);
        log.addEntry(std::string("Test " + it.getId() + " has been completed.\n"));
        log.addEntry("\n");
        Results res = it.getResult();
        if(do_perftest || do_acctest) log.addSummary(it);
        log.addEntry("\n");
    }

    log.addEntry("\n");
    log.addBriefSummary(tests);
    log.printToLog();
}