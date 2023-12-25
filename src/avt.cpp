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
    if(argc == 1)
    {
        std::cout << "Welcome to AVT, antivirus test environment! Use \"-h\" or \"--help\" to get started." << std::endl;
        return 0;
    }
    if(argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h"))
    {
        std::cout << "Welcome to AVT, antivirus test environment!" << std::endl << std::endl;
        std::cout << "Syntax: ./avt [performance] [accuracy] [tests]" << std::endl << std::endl;
        std::cout << "[performance] - if performance test should be included in the program. Values: 0, 1" << std::endl;
        std::cout << "[accuracy] - if accuracy test should be included in the program. Values: 0, 1" << std::endl;
        std::cout << "[tests] - tests that should be done, separated by whitespace. Example: AD-6969 SP-4780" << std::endl << std::endl;
        std::cout << "Make sure all listed tests are placed in \"testfiles\" folder" << std::endl << std::endl;
        std::cout << "Compatible with: ClamAV, DrWeb, Sophos" << std::endl << std::endl;
        return 0;
    }
    if(argc < 4)
    {
        std::cout << "Too few arguments. Use \"-h\" or \"--help\" to learn more.";
        return 1;
    }
    
    std::shared_ptr<AVType> avtype;
    Preprocessor prep = Preprocessor();
    Tester tester;

    std::list<std::string> testnames;
    std::list<Test> tests;
    
    // przygotowanie testów i obiektow do wykonywania testow
    try
    {
        avtype = prep.getAVType();
        
        for(int i = 3; i < argc; i++)
            testnames.emplace_back(argv[i]);
        
        tests = prep.prepareTests(testnames);
        tester = Tester(std::string(argv[1]), std::string(argv[2]), avtype);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    // wykonanie testow antywirusow
    tester.performTests(tests);

    // usun przestrzen robocza
    system("rm -rf .workspace");
    
    return 0;
}