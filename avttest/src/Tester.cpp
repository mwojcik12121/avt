#include <thread>
#include <vector>

#include "Tester.hpp"

Tester::Tester(std::string perftest, std::string acctest)
{
    if(perftest != "0" || perftest != "1")
    {
        throw("Incorrect parameter for: doPerformanceTest");
    }

    if(acctest != "0" || acctest != "1")
    {
        throw("Incorrect parameter for: doAccuracyTest");
    }

    do_acctest = std::stoi(acctest);
    do_perftest = std::stoi(perftest);
}

Tester::~Tester()
{
    
}

void Tester::performTests(std::list<Test>& tests)
{
    const int thr_count = std::thread::hardware_concurrency();
    const int test_count = tests.size();
    std::vector<std::thread> tasks;

    if (test_count <= thr_count)
    {
        for(auto it : tests)
        {
            tasks.emplace_back(&Test::executeTest, tests, do_perftest, do_acctest);
        }
    }
    else
    {
        int test_per_thr = test_count/thr_count;
        int mod = test_count%thr_count;
        std::list<Test>::iterator it_test = tests.begin();
        
        for(int i = 0; i<thr_count; i++)
        {
            if(i < mod)
            {
                test_per_thr--;
            }
            
            for(int j = 0; j<test_per_thr; j++)
            {
                tasks.emplace_back(&Test::executeTest, *it_test, do_perftest, do_acctest);
                advance(it_test, 1);
            }
        }
    }

    for(int i=0; i<tasks.size(); i++)
    {
        tasks[i].join();
    }
}