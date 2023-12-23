#pragma once

#include <string>
#include <list>

#include "Test.hpp"

class Preprocessor
{
    std::string directory;

    bool importTest(std::string file, Test &test);
    void unpackTar(std::string file);
    bool validateLine(int index, std::string line);
    avt::StageMap createMapEntry(std::string line);

public:
    Preprocessor() = default;
    Preprocessor(std::string dir);
    ~Preprocessor() = default;

    std::list<Test> prepareTests(std::list<std::string> &testnames);
};