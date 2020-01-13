#include <iostream>
#include "Trie.h"



int main() {
   Trie<string> baum ;

    std::cout<<"ist root leer? " << baum.empty()<<endl;
    pair<string,string> wort;
    wort.first="sind";
    wort.second="are";
   baum.insert(wort);

    pair<string,string> wort2;
    wort2.first="weiß";
    wort2.second="know";
baum.insert(wort2);

    pair<string,string> wort3;
    wort3.first="wer";
    wort3.second="who";
    baum.insert(wort3);

    pair<string,string> wort4;
    wort4.first="wir";
    wort4.second="we";
    baum.insert(wort4);
    pair<string,string> wort5;
    wort5.first="wird";
    wort5.second="will";
    baum.insert(wort5);
    pair<string,string> wort6;
    wort6.first="wo";
    wort6.second="where";
    baum.insert(wort6);
    baum.print();

  baum.erase("wo");

baum.print();

    return 0;
}
