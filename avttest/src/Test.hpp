#pragma once

#include <list>
#include <string>

#include "Common.hpp"
#include "Results.hpp"

class Test
{
    std::string id = "";
    std::string type = "";
    std::list<avt::StageMap> stageinfo;
    Results result;

    void verifyAVLog(avt::AVType avtype);

public:
    Test() = default;
    Test(std::string id, std::string type, std::list<avt::StageMap> stageinfo);
    ~Test() = default;

    void executeTest(const bool doPerf, const bool doAcc, avt::AVType avtype);

    std::string getId() { return id; }
    std::string getType() { return type; }
    std::list<avt::StageMap>& getStageInfo() { return stageinfo; }
    Results getResult() { return result; }
};