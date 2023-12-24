#pragma once

#include <string>

struct AVType
{
    std::string logpath;

    virtual int executeTest(std::string testfile);
    virtual std::string verifyAVLog();
};

struct ClamAV : AVType
{
    int executeTest(std::string testfile) override;
    std::string verifyAVLog() override;
};

struct DrWeb : AVType
{
    int executeTest(std::string testfile) override;
    std::string verifyAVLog() override;
};

struct Sophos : AVType
{
    int executeTest(std::string testfile) override;
    std::string verifyAVLog() override;
};