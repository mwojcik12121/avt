#pragma once

#include <string>
#include <list>

#include "Test.hpp"

class Preprocessor
{
    std::string directory;

    bool importTest(std::string file, Test &test);
    void unpackTarInfo(std::string filepath);
    bool validateLine(int index, std::string line);

public:
    Preprocessor();
    ~Preprocessor() = default;

    std::list<Test> prepareTests(std::list<std::string> &testnames);
    std::shared_ptr<AVType> getAVType();
};