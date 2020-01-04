//
//
//

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <iostream>
#include <iterator>
#include <map>
#include <list>

using namespace std;


// (vergl. map in der STL)
template<class T, class E=char>
class Trie {

    // typedefs
public:
    // Die Daten sind Paare, bestehend aus einem String als Schlüssel und beliebigen Nutzdaten T
    typedef basic_string<E> key_type; // string=basic_string<char>
    typedef pair<const key_type, T> value_type;
    typedef T mapped_type;


    // ----------------------------------------------------------------------------------------
    // KNOTENKLASSE
    // abstrakte Knotenklasse als innere Klasse von Trie

    class Node {

    public:
        // default Constructor um Liste von Nodes nutzen zu können
        Node();

        Node(const bool *);

        Node(char c);

        key_type key;
        value_type value;
        bool isLeaf;

        virtual void print(string prefix = "");

        virtual void addChild(Node toadd);


    };


    // Blätter und innere Knoten sind Spezialisierung der Knotenklasse & haben unterschiedlichen Typ
    // innere Knoten : haben markierte Kindzeiger
    // Sohnzeiger eines Knoten als geordete lineare Liste ( VL oder STL-Klasse) -> Blätter sind aufsteigend sortiert
    class innerNode : Node {
    public:

        innerNode(const char *c) : Node(c) {
            isLeaf = false;
            val = c;
        }

        std::list<Node *> children;
        list<char>::iterator itr;

        bool isLeaf = false;
        key_type val;

        void addChild(Node add) {

            children.push_front(new Node(add.key));

        }

//            void print(string prefix = ""){
//                string my_prefix = prefix;
//
//                for(itr = children.begin(); itr != children.end(); itr++){
//                    cout << prefix << itr->first() << endl;
//                    my_prefix += " ";
//                    itr->second.print(my_prefix);
//                }
//            }

    };

    // Blätter: haben Record
    class leaf : Node {
    public :
        leaf(const value_type *match) : Node(match) {
            isLeaf = true;
            value = match;
        }

        bool isLeaf = true;
        value_type value;


    };

    //---------------------------------------------------------------------------------------------
//TRIE
    Node root;

    Trie() {
        root = new Node;
        root.isLeaf = true;
    }

    /*  1.Set a current node as a root node
        2. Set the current letter as the first letter of the word
        3.If the current node has already an existing reference to the current letter (through one of the elements in the “children” field),
            then set current node to that referenced node.
            Otherwise, create a new node, set the letter equal to the current letter, and also initialize current node to this new node
        4. Repeat step 3 until the key is traversed*/
    void insert(key_type key, value_type val) {
        //1
        Node *crawler = root;
        //2.
        for (int j = 0; j < key.length()-1; j++) {
            //  3.
            char current = key.at(j);
            list < Node * > liste;
            liste = crawler->children;
            bool found = false;
            for (int i = 0; i < liste.size() - 1; i++) {
                Node what = liste.front();
                if (what.key.compare(current) == 0) {
                    found = true;
                    *crawler = what;
                    break;
                }
                liste.pop_front();
                // es fehlt was ist wenn letzter buchstabe dann leaf
            }
            if (!found) {

                Node insertletter = new Node(current);
                crawler->addChild(insertletter);
                *crawler= insertletter;
            }


        }
    }


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