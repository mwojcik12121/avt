#pragma once

#include <string>

#include "TestInfo.hpp"
class Test
{
    std::string id = "";
    std::list<unsigned> code;
    std::list<StageMap> stageinfo;

public:
    Test(std::string id, std::list<unsigned> code, std::list<StageMap> stageinfo);
    ~Test();

    int executeTest(const bool doPerf, const bool doAcc);

    std::string getId();
    std::list<unsigned> getCode();
    std::list<StageMap> getStageInfo();
};