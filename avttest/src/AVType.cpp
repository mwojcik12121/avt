#include "AVType.hpp"

int ClamAV::executeTest(std::string testfile)
{
    system(std::string("clamscan -l workspace/clamav.log " + testfile).c_str());
}

std::string ClamAV::verifyAVLog()
{
    
}

int DrWeb::executeTest(std::string testfile)
{
    
}

std::string DrWeb::verifyAVLog()
{
    
}

int Sophos::executeTest(std::string testfile)
{
    int retval = system(std::string("." + testfile).c_str());
    
}

std::string Sophos::verifyAVLog()
{
    std::string logline;
}
