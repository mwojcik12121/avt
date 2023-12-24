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
    std::shared_ptr<AVType> avtype;
    Preprocessor prep;
    Tester tester;

    std::list<std::string> testnames;
    std::list<Test> tests;
    
    // przygotowanie testów i obiektow do wykonywania testow
    try
    {
        prep = Preprocessor();
        avtype = prep.getAVType();
        
        for(int i = 2; i < argc; i++)
            testnames.emplace_back(argv[i]);
        
        tests = prep.prepareTests(testnames);
        tester = Tester(argv[1], argv[2], avtype);
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