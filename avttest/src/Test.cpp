#include <chrono>

#include "Test.hpp"

using stopwatch = std::chrono::steady_clock;

Test::Test(std::string id, std::string type)
{
    id = id;
    type = type;
}

void Test::executeTest(const bool doPerf, const bool doAcc, std::shared_ptr<AVType> avtype)
{
    stopwatch::time_point begin;
    stopwatch::time_point end;

    if(doPerf) begin = stopwatch::now();
    
    std::string testdir = "/workspace/" + id;
    result.nstage = system(testdir.c_str());

    if(doPerf)
    {
        end = stopwatch::now();
        result.elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    }
}
