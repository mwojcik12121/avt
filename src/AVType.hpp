#pragma once

#include <string>

struct AVType
{
    std::string logpath;

    virtual int executeTest(std::string id) = 0;
    virtual std::string verifyAVLog(std::string testpath) = 0;
};

struct ClamAV : AVType
{
    int executeTest(std::string id) override;
    std::string verifyAVLog(std::string testpath) override;
};

struct DrWeb : AVType
{
    int executeTest(std::string id) override;
    std::string verifyAVLog(std::string testpath) override;
};

struct Sophos : AVType
{
    int executeTest(std::string id) override;
    std::string verifyAVLog(std::string testpath) override;
};