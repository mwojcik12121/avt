#include <iostream>
#include <list>
#include <memory>

#include "src/Test.hpp"

/**
 * Przyjmowane argumenty:
 * argv[0] - sciezka do folderu z testami
 * argv[1] - czy bedzie wykonywany test wydajnosci
 * argv[2] - czy bedzie wykonywany test dokladnosci
 * argv[3 ... argc-1] - nazwy plikow testowych w cudzyslowie
*/

int main(int argc, char *argv[])
{
    std::list<std::shared_ptr<Test>> tests;
    
    for(int i = 3; i < argc; i++)
    {
        tests.push_back(std::make_shared<Test>(argv[0], argv[1], argv[2], argv[i]));
    }
    
    return 0;
}