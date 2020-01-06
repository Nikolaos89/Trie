

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <iostream>
#include <iterator>
#include <map>
#include <set>

using namespace std;
/* Email Fischer:
 Eine Anmerkung noch:

Wie im Code vermerkt, würde ich Ihnen (noch einfacher und lehrreicher) eine std::map empfehlen, die E (also Buchstaben) auf Node* abbildet. Node* kann dabei entweder auf
einen inneren
Knoten (z.B. InnerNode) oder ein Blatt (Leaf) zeigen, die jeweils per new auf dem Heap alloziert werden. Ein Leaf wird dabei (s. Grafiken auf der Angabe) immer nur mit
einem Terminalzeichen (z.B. '\0') assoziiert.

Trie::insert könnte sich dann auf innerNode::insert(key_type key,const& mapped_type val) abstützen, der die Arbeit rekursiv erledigt:
Ist key leer, wird ein Leaf erzeugt und in der Map unter '\0' eingetragen.
Ansonsten kümmert sich insert nur um den ersten Buchstaben von key: Gibts den noch nicht in der Map, wird ein neuer innerNode unter diesem Buchstaben eingetragen, ansonsten
der gefundene innerNode verwendet, um mit einem Aufruf von insert sich um den Rest des key (bis auf den ersten Buchstaben) zu kümmern.*/
// kommentare welche mit MF anfangen sind von ihm

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
        key_type key;
        value_type value;
        bool isLeaf;
//MF        Node();
        Node(){};

        Node(const bool *);

        Node(char c);



//MF        virtual void print();
//MF da Sie print hier nicht implementieren wollen, sondern nur im Sinne eines Interfaces "versprechen", dass ableitende Klassen print implementieren,
//MF sollten Sie print als "pure virtual" deklarieren (... =0;)
        virtual void print() = 0;

        bool operator<(const Node &n) const {
            return (this->key < n.key);
        }




    };


    // Blätter und innere Knoten sind Spezialisierung der Knotenklasse & haben unterschiedlichen Typ
    // innere Knoten : haben markierte Kindzeiger
    // Sohnzeiger eines Knoten als geordete lineare Liste ( VL oder STL-Klasse) -> Blätter sind aufsteigend sortiert
//MF bitte public ableiten!!!    class innerNode : Node {
    class innerNode : public Node {
    public:

        //MF in Zeile 124 verwenden Sie den Default-Konstruktor. Der automatisch generierte wird gelöscht, wenn Sie einen speziellen anbieten
        //MF somit müssen Sie ihn selber implementieren
        innerNode(){}

        //MF den werden Sie nicht brauchen: Wenn Sie eine Map verwenden, wissen Sie schon im Elternknoten, unter welchem Zeichen Sie zum jeweiligen Kind gelangen -> val weg; isLeaf: Da Sie ohnehin im Typ innerNode sind, weg. Sie wissen, dass unter dem Terminalzeichen immer ein Leaf kommt, also müssen Sie nicht mehr fragen
        innerNode(const char c) : Node(c) {
            isLeaf = false;
            val = c;
        }
//MF besser wäre hier eine map<E,Node*> , die jeweils ein Zeichen auf den zugehörigen Pointer zum Kind (innerNode oder leaf) abbildet
//MF mindestens aber Node* statt Node (s.o.)       std::set<Node> children;
        std::set<Node*> children;


        bool isLeaf = false;
        key_type val;



        void print(){
            cout<<"IsLeaf="<<this->isLeaf<<endl;
//MF type           cout<<"val="<<this->val<endl;
            cout<<"val="<<this->val<<endl;
        }


        /*     void print(string prefix = ""){
                 string my_prefix = prefix;

                 for(itr = children.begin(); itr != children.end(); itr++){
                     cout << prefix << itr->first() << endl;
                     my_prefix += " ";
                     itr->second.print(my_prefix);
                 }*/

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
        void print(){
            cout<<"IsLeaf="<<this->isLeaf<<endl;
            cout<<"value="<<this->value.first<<" "<< this->value.second<<endl;
        }

    };

    //---------------------------------------------------------------------------------------------
//TRIE
    Node* root;

    Trie() {
//MF Node ist - da es mindestens eine pure virtual Methode enthält - eine abstrakte Klasse (Interface), von der Sie kein Objekt anlegen können.
//MF Sie wissen es ja ohnehin besser: Es ist ein InnerNode
        //MF root = new Node();
        root = new innerNode;

    }

    /*  1.Set a current node as a root node
        2. Set the current letter as the first letter of the word
        3.If the current node has already an existing reference to the current letter (through one of the elements in the “children” field),
            then set current node to that referenced node.
            Otherwise, create a new node, set the letter equal to the current letter, and also initialize current node to this new node
        4. Repeat step 3 until the key is traversed*/


    void insert(Node *root, value_type val) {
        //1
        innerNode *crawler =root;
        //2.
        string current;


        std::set<Node>::iterator;
        std::pair<set<int>::iterator,bool> ret;
        for (int j = 0; j < val.first.key.length(); j++) {

            current=val.first.key.at(j);

            // insert prüft ob element bereits vorhanden, wenn nein hinzugefügen und return pointer wennn ja returnt pointer dort hin
            // pair:first von ret ist entweder oben genannter pointer oder das equivalente element im set
            Node insertletter = new innerNode(current);
            ret=crawler->children.insert(insertletter);
            crawler= ret.first;

        }
        // leaf an abschlusszeichen inneren Knoten hängen
        innerNode insertletter = new innerNode("$");
        leaf lastOne=new leaf(*val);
        insertletter.children.insert(lastOne);
        //inneren an vorherigen knoten hängen
        crawler->children.insert(insertletter);



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