#include <string>

/*
Tagger - rozmnazajacy sie program

Autor: Marta Wojcik

Parametr wejsciowy: next (integer)
*/

int main(int argc, char *argv[])
{
    int next = 1;

    if(argc == 2) next = std::stoi(std::string(argv[1]));

    // Zakoncz prace dla 1000 kopii
    if(next == 1001) return 0;
    
    // Utworz i wykonaj kolejny program
    std::string nextfile = "tagger" + std::to_string(next);
    system(std::string("touch " + nextfile).c_str());
    system(std::string("cat " + std::string(argv[0]) + " > " + nextfile).c_str());
    system(std::string("chmod +x " + nextfile).c_str());
    system(std::string("./" + nextfile + " " + std::to_string(next + 1)).c_str());
    return 0;
}
