#include "AVType.hpp"

int ClamAV::executeTest(std::string testfile)
{
    system(std::string("clamscan -l workspace/clamav.log " + testfile).c_str());
    return 0;
}

std::string ClamAV::verifyAVLog()
{
    return "";
}

int DrWeb::executeTest(std::string testfile)
{
    return 0;
}

std::string DrWeb::verifyAVLog()
{
    return "";
}

int Sophos::executeTest(std::string testfile)
{
    int retval = system(std::string("." + testfile).c_str());
    return 0;
}

std::string Sophos::verifyAVLog()
{
    std::string logline;
    return "";
}
