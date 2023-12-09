#include <iostream>
#include <list>

#include "Preprocessor.hpp"
#include "Tester.hpp"

/**
 * Przyjmowane argumenty:
 * argv[0] - sciezka do folderu z testami
 * argv[1] - czy bedzie wykonywany test wydajnosci
 * argv[2] - czy bedzie wykonywany test dokladnosci
 * argv[3 ... argc-1] - nazwy plikow testowych w cudzyslowie
*/

int main(int argc, char *argv[])
{
    std::unique_ptr<Preprocessor> prep = std::make_unique<Preprocessor>(argv[0]);
    std::unique_ptr<Tester> tester = std::make_unique<Tester>(argv[1], argv[2]);
    
    std::list<Test> tests = prep->prepareTests();
    tester->performTests(tests);
    
    return 0;
}