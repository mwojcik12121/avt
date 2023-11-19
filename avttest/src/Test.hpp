#pragma once

#include <string>

class Test
{
    std::string fullpath = "";
    std::string executable = "";

    
    void importTest(std::string path, bool doPerfTest, bool doPrecTest, std::string file);

public:
    Test(std::string path, bool doPerfTest, bool doPrecTest, std::string file);
    ~Test();

    void performTest();
};