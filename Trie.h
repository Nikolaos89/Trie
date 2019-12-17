//
//
//

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H#include <iostream>
// (vergl. map in der STL)
template<class T, class E=char>
class Trie {

    // typedefs
public:
    // Die Daten sind Paare, bestehend aus einem String als Schlüssel und beliebigen Nutzdaten T
    typedef basic_string <E> key_type; // string=basic_string<char>
    typedef pair<const key_type, T> value_type;
    typedef T mapped_type;





    // ----------------------------------------------------------------------------------------
    // KNOTENKLASSE
    // abstrakte Knotenklasse als innere Klasse von Trie




    class Node{
        // Blätter und innere Knoten sind Spezialisierung der Knotenklasse & haben unterschiedlichen Typ
        // innere Knoten : haben markierte Kindzeiger
        // Sohnzeiger eines Knoten als innere Liste ( VL oder STL-Klasse) -> Blätter sind aufsteigend sortiert
        class innerNode{


        };
        // Blätter: haben Record
        class leaf{

        };

    };
//---------------------------------------------------------------------------------------------
//ITERATOR

    // „...“ im folgenden typedef: keine C/C++ Ellipse, sondern von Ihnen
    // - am besten als innere Klasse - zu entwickeln…


/*  typedef ... iterator;
    bool empty() const;
    iterator insert(const value_type& value);

    void erase(const key_type& value);
    void clear(); // erase all
    iterator lower_bound(const key_type& testElement); // first element >= testElement
    iterator upper_bound(const key_type& testElement); // first element > testElement
    iterator find(const key_type& testElement); // first element == testElement
    iterator begin(); // returns end() if not found
    iterator end();*/
//----------------------------------------------------------------------------------------
};

#endif //TRIE_TRIE_H