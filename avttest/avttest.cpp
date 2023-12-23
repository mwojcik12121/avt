#include <iostream>
#include <list>

#include "Preprocessor.hpp"
#include "Tester.hpp"

/**
 * Przyjmowane argumenty:
 * argv[0] - sciezka do folderu z testami
 * argv[1] - czy bedzie wykonywany test wydajnosci
 * argv[2] - czy bedzie wykonywany test dokladnosci
 * argv[3 ... argc-1] - nazwy plikow testowych
*/

int main(int argc, char *argv[])
{
    Preprocessor prep;
    Tester tester;

    std::list<std::string> testnames;
    std::list<Test> tests;
    
    try
    {
        prep = Preprocessor(argv[0]);
        
        for(int i = 3; i < argc; i++)
            testnames.emplace_back(argv[i]);
        
        tests = prep.prepareTests(testnames);
        tester = Tester(argv[1], argv[2]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    tester.performTests(tests);
    
    return 0;
}