#include <filesystem>
#include <iostream>
#include <list>

#include "AVType.hpp"
#include "Preprocessor.hpp"
#include "Tester.hpp"

/**
 * Przyjmowane argumenty:
 * argv[0] - czy bedzie wykonywany test wydajnosci
 * argv[1] - czy bedzie wykonywany test dokladnosci
 * argv[2 ... argc-1] - nazwy plikow testowych
*/

int main(int argc, char *argv[])
{
    // Display help and verify given arguments
    if(argc == 1)
    {
        std::cout << "Welcome to AVT, antivirus test environment! Use \"-h\" or \"--help\" to get started." << std::endl;
        return 0;
    }
    if(argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h"))
    {
        std::cout << "Welcome to AVT, antivirus test environment!" << std::endl << std::endl;
        std::cout << "Syntax: ./avt [performance] [accuracy] [tests (optional)]" << std::endl << std::endl;
        std::cout << "[performance] - if performance test should be included in the program. Values: 0, 1" << std::endl;
        std::cout << "[accuracy] - if accuracy test should be included in the program. Values: 0, 1" << std::endl;
        std::cout << "[tests] - tests that should be done, separated by whitespace. Leave emply for check all tests in the folder. Example: AD-6969 SP-4780" << std::endl << std::endl;
        std::cout << "Make sure all listed tests are placed in \"testfiles\" folder" << std::endl << std::endl;
        std::cout << "Compatible with: ClamAV, DrWeb, Sophos" << std::endl << std::endl;
        return 0;
    }
    if(argc < 3)
    {
        std::cout << "Too few arguments. Use \"-h\" or \"--help\" to learn more.";
        return 1;
    }
    if(std::string(argv[1]) != "0" && std::string(argv[1]) != "1")
    {
        std::cout << "\nIncorrect parameter for: performance";
        return 1;
    }
    if(std::string(argv[2]) != "0" && std::string(argv[2]) != "1")
    {
        std::cout << "\nIncorrect parameter for: accuracy";
        return 1;
    }    

    std::shared_ptr<AVType> avtype;
    Preprocessor prep = Preprocessor();
    Tester tester;

    std::list<std::string> testnames;
    std::list<Test> tests;
    
    // prepare tests for execution
    try
    {
        system("mkdir .workspace");
        avtype = prep.getAVType();
        
        if(argc == 3)
        {
            for(const auto & entry : std::filesystem::directory_iterator("testfiles"))
                testnames.emplace_back(entry.path().stem().string());
        }  
        else for(int i = 3; i < argc; i++) testnames.emplace_back(argv[i]);
        
        tests = prep.prepareTests(testnames);
        system("rm -rf .workspace");
        tester = Tester(argv[1], argv[2], avtype);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        system("rm -rf .workspace");
        return 1;
    }

    // perform all declared tests
    tester.performTests(tests);

    // remove .workspace folder
    system("rm -rf .workspace");
    
    return 0;
}