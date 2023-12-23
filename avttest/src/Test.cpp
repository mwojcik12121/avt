#include "Common.hpp"
#include "Test.hpp"

Test::Test(std::string id, std::string type, std::list<avt::StageMap> stageinfo)
{
    id = id;
    type = type;
    stageinfo = stageinfo;
}

void Test::executeTest(const bool doPerf, const bool doAcc, avt::AVType avtype)
{
    avt::stopwatch::time_point begin;
    avt::stopwatch::time_point end;

    if(doPerf) begin = avt::stopwatch::now();
    
    std::string testdir = "./workspace/" + id;
    result.nstage = system(testdir.c_str());

    if(doPerf)
    {
        end = avt::stopwatch::now();
        result.elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    }

    verifyAVLog(avtype);
}

void Test::verifyAVLog(avt::AVType avtype)
{
    switch(avtype)
    {
        case avt::AVType::ClamAV:
            break;
        case avt::AVType::Comodo:
            break;
        case avt::AVType::DrWeb:
            break;
        case avt::AVType::Sophos:
            break;
        default:
            result.detected = "N/A";
            break;
    }
}
