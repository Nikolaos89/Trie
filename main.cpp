#include <iostream>
#include "Trie.h"



int main() {
   Trie<string> baum ;


    pair<string,string> wort;
    wort.first="hallo";
    wort.second="hola";
   baum.insert(wort);
  std::cout<<"ist root leer? " << baum.root->kids.empty()<<endl;
    pair<string,string> wort2;
    wort2.first="hart";
    wort2.second="hard";
baum.insert(wort2);
    pair<string,string> wort3;
    wort3.first="aaaber";
    wort3.second="lala";
    baum.insert(wort3);


    return 0;
}
