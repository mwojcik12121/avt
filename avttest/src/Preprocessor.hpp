#pragma once

#include <string>
#include <list>

#include "Test.hpp"

class Preprocessor
{
    std::string directory;

    bool validateTestFile(std::string file);
    Test importTest(std::string file);

public:
    Preprocessor(std::string dir);
    ~Preprocessor();

    std::list<Test> prepareTests();
};