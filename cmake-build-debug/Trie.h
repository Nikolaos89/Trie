//
// Created by nikol on 10.12.2019.
//

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <iostream>
#include <iterator>
#include <map>

using namespace std;

// Size = constant setting maximum list size
template<class T, class E = char>

class Trie {

public:
    typedef basic_string<E> key_type;
    typedef pair<const key_type, T> value_type;
    typedef T mapped_type;

    class trie_iterator{

    };

    typedef trie_iterator Trie_iterator;

    struct Trie_object{
        virtual void print(string prefix = "");
    };

    struct Knot: Trie_object{
        map<char, Trie_object> kids;

        void print(string prefix = ""){
            string my_prefix = prefix;
            map<char, Trie_object>::iterator itr;
            for(itr = kids.begin(); itr != kids.end(); itr++){
                cout << prefix << itr->first() << endl;
                my_prefix += " ";
                itr->second.print(my_prefix);
            }
        }
    };

    struct Leaf: Trie_object{
        string value;

        void print(string prefix = ""){
            cout << prefix << value << endl;
        }
    };

};
#endif //TRIE_TRIE_H
