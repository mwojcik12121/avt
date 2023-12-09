#pragma once

#include <list>
#include <string>
#include <tuple>

using StageMap = std::tuple<int, std::string>;

class TestInfo
{
    std::string id = "";
    std::list<std::string> tags;
    std::string description = "";

public:
    TestInfo(std::string id, std::list<std::string> tags,
    std::string description);
    ~TestInfo();

    std::string getId();
    std::list<std::string> getTags();
    
};