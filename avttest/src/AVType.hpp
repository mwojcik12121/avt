#pragma once

#include <string>

class AVType
{
    std::string logpath;

public:
    AVType(std::string lp) {logpath = lp;};
    ~AVType() = default;

    virtual int executeTest(std::string testfile) {}
    virtual std::string verifyAVLog() {}
};

class ClamAV : public AVType
{
public:
    ClamAV(std::string lp) : AVType(lp) {}
    ~ClamAV() = default;

    int executeTest(std::string testfile) override;
    std::string verifyAVLog() override;
};

class DrWeb : public AVType
{
public:
    DrWeb(std::string lp) : AVType(lp) {}
    ~DrWeb() = default;

    int executeTest(std::string testfile) override;
    std::string verifyAVLog() override;
};

class Sophos : public AVType
{
public:
    Sophos(std::string lp) : AVType(lp) {}
    ~Sophos() = default;

    int executeTest(std::string testfile) override;
    std::string verifyAVLog() override;
};