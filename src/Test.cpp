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
    // Utworz folder .workspace
    system("mkdir -m 755 .workspace");
    stopwatch::time_point begin;
    stopwatch::time_point end;

    // Rozpocznij test wydajnosci
    begin = stopwatch::now();

    // Wykonaj test i zapisz jego status
    int retval = avtype->executeTest(std::string(id));
    result.status = retval;

    // Zakoncz test wydajnosci
    end = stopwatch::now();

    // Zapisz wyniki do struktury
    if(doPerf) result.elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    std::string detected = avtype->verifyAVLog(std::string(".workspace/" + id));
    
    // Popraw wyniki wykonywania testu w oparciu o test wydajnosci
    if(doAcc && retval != 0) result.detected = detected;
    if(detected == "" || detected == "Not found") result.status = 0;

    system("rm -rf .workspace");
}
