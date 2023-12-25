#include <chrono>
#include <filesystem>
#include <iostream>

#include "Test.hpp"

using stopwatch = std::chrono::steady_clock;

Test::Test(std::string id_t, std::string type_t)
{
    id = id_t;
    type = type_t;
}

void Test::executeTest(const bool doPerf, const bool doAcc, std::shared_ptr<AVType> avtype)
{
    stopwatch::time_point begin;
    stopwatch::time_point end;

    if(doPerf) begin = stopwatch::now();

    int retval = avtype->executeTest(std::string(id));
    result.status = retval;

    if(doPerf)
    {
        end = stopwatch::now();
        result.elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
    }

    if(doAcc && retval != 0) result.detected = avtype->verifyAVLog(std::string(".workspace/" + id));
}