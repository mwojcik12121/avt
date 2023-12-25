#include <chrono>
#include <filesystem>

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

    unpackTarCode(std::string(std::filesystem::current_path().string()+"/testfiles/" + id));
    
    std::string testdir = "/workspace/" + id;
    result.status = system(testdir.c_str());

    if(doPerf)
    {
        end = stopwatch::now();
        result.elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    }
}

void Test::unpackTarCode(std::string filepath)
{
    std::string cmd = "tar -xvf " + filepath + " -C .workspace " + std::filesystem::path(filepath).stem().string();
    system(cmd.c_str());
}
