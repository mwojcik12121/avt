

#include "Test.hpp"

Test::Test(std::string id, std::list<unsigned> code, std::list<StageMap> stageinfo)
{
    id = id;
    code = code;
    stageinfo = stageinfo;
}

Test::~Test()
{

}

std::string Test::getId()
{
    return id;
}

std::list<unsigned> Test::getCode()
{
    return code;
}

std::list<StageMap> Test::getStageInfo()
{
    return stageinfo;
}

int Test::executeTest(const bool doPerf, const bool doAcc)
{
    
}