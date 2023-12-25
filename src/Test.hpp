#pragma once

#include <list>
#include <memory>
#include <string>

#include "AVType.hpp"
#include "Results.hpp"

class Test
{
    std::string id = "";
    std::string type = "";
    Results result;

public:
    Test() = default;
    Test(std::string id_t, std::string type_t);
    ~Test() = default;

    void executeTest(const bool doPerf, const bool doAcc, std::shared_ptr<AVType> avtype);

    std::string getId() { return id; }
    std::string getType() { return type; }
    Results getResult() { return result; }
};