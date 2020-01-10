



#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <vector>

using namespace std;


template<class T, class E=char>
class Trie {

public:
    typedef basic_string<E> key_type;
    typedef pair<const key_type, T> value_type;
    typedef T mapped_type;

    const key_type terminator = "#";

    class trie_iterator {

    };


    class Node {
    public:

        virtual Node *insert(char c) = 0;
      virtual void insert(value_type sol)=0;

        //     virtual void print(string prefix = "");

        //    virtual bool operator<(const Node &n);
    };
    class Leaf : public Node {
    public:
        mapped_type val;


        Leaf(){}
         Node *insert(char c) {
            return nullptr;
        }
         void insert(value_type sol){

        };

        void print(string prefix = "") {
            cout << prefix << val << endl;
        }

    };
    class Knot : public Node {
    public:
        map<key_type, Node *> kids;

        Knot() {

        }

        Knot *getNewKnot() {
            Knot *node = new Knot();

            return node;
        }

        typedef typename map<key_type, Node *>::iterator map_iterator;

        void insert(value_type sol) {
            pair<map_iterator, bool> ret;
            typedef pair<key_type, Node *> entry;


          Leaf ende=Leaf();



ende.val=sol.second;

            entry eintrag;
            eintrag.first = "#";
            eintrag.second = &ende;

            kids.insert(eintrag);

            std::cout << "# and in Leaf inserted = " << eintrag.first<< ende.val<< endl;

        }

        Node *insert(char c) {

std::cout << " -----------------------------------------------------------------"<< endl;
            pair<map_iterator, bool> ret;
            typedef pair<key_type, Node *> entry;

            Node *neuer = getNewKnot();
            std::cout <<  "neuer adresse "<<neuer<< endl;
            entry eintrag;
            eintrag.first = c;
            eintrag.second = neuer;
            std::cout << "ist kids empty? "<< kids.empty()<< endl;
            ret = kids.insert(eintrag);



            std::cout << " eingetragen ? " << ret.second <<" ist kids empty? " <<kids.empty()<< endl;
            std::cout << "erster key von kids=  "  << kids.begin()->first << endl;
            map_iterator neu = ret.first;
            std::cout << " -----------------------------------------------------------------"<< endl;
            Node* heler= neu->second;
            return heler;
        }

  /*      void printChildren(string prefix = "") {
            for (auto itr = kids.begin(); itr != kids.end(); itr++) {
                if (itr->first != terminator) {
                    cout << prefix << itr->first() << endl;
                }
                itr->second.print(prefix + " ");
            }
        }*/

    };



    Knot *root;

    Trie() {
root= new Knot();
    }

/*
       class TrieIterator {
        typedef TrieIterator iterator;
        typedef typename map<key_type, Node*>::iterator map_iterator;
    private:

        typedef pair<map_iterator, map_iterator> breadcrumb;
        Trie *myTrie;
        Node *myCursor;
        stack<breadcrumb> parents;

        TrieIterator(Trie *myTree){
            this->myTrie = myTree;
            myCursor = nullptr;
        }
    public:

        TrieIterator(Trie *myTrie, value_type keyword){
            if(keyword.empty()){
                return TrieIterator(*myTrie);
            } else {
                myCursor = myTrie->root;
                value_type search = keyword + terminator;
                this->myTrie = myTrie;

                while (true) {
                    if (search == "") {
                        return this;
                    }
                    // Preparing the record for the current stage to add to the stack
                    auto search_result = myCursor->kids.find(search.substring(0, 0));
                    auto end = myCursor->kids.end();
                    breadcrumb record(search_result, end);

                    // Checking if current letter is found
                    if (record.first != record.second) {
                        // If letter is found, record is stored on the stack, cursor is advanced to found node and first letter
                        // of the search string is removed. Loop is continued.
                        parents.push(record);
                        myCursor = search_result->second;
                        search = search.substring(1);
                    }
                        // If not found a end() iterator is returned, signaling that the key was not found
                    else {
                        return TrieIterator(myTrie);
                    }
                }
            }
        }



    typedef TrieIterator iterator;



*/

    bool empty() const {

        return 0;
    };

    /*  1.Set a current node as a root node
        2. Set the current letter as the first letter of the word
        3.If the current node has already an existing reference to the current letter (through one of the elements in the “children” field),
            then set current node to that referenced node.
            Otherwise, create a new node, set the letter equal to the current letter, and also initialize current node to this new node
        4. Repeat step 3 until the key is traversed*/



    void insert(const value_type &value) {
        string word = value.first;

        std::cout <<  " root "<< root<< endl;

        //1

       Knot* crawlp =root;
        std::cout <<  " crawlp startadresse "<< crawlp << endl;

        //2.
        char current;


        for (int j = 0; j < word.length(); j++) {

            current = word.at(j);
            std::cout <<  "Buchstabe "<< j<<" inserting = " << current << endl;
            std::cout << "crawlp kids size before = "<< crawlp->kids.size()<<endl;
                      Knot* gotback= (Knot *) crawlp->insert(current);

            std::cout <<  "crawler kids size after " << crawlp->kids.size()<< endl;

            crawlp =  gotback;
            std::cout <<  "crawlp = " << crawlp<< " gotback= "<< gotback<< endl;





            std::cout << " --------------------NÄCHSTER BUCHSTABE-------------------------"<< endl;
        }
        crawlp->insert(value);

        std::cout << " -------------------       NEUES WORT      -------------------------"<< endl;
    };

    void erase(const key_type &value);

    void clear(); // erase all


/*    iterator lower_bound(const key_type& testElement) {
        if(testElement.empty() || this->empty()){
            cout << "no test Element" << endl;
        }
        typedef pair<Node*, key_type> breadcrumb;
        stack<breadcrumb> path;
        Node *current_node = root;
        key_type word = testElement;
        bool failed = false;

        while (true){
           if (current_node->kids->lower_bound(word[0]) == current_node->kids->end()) {
               if (failed) {
                   if (path.empty()) {
                       cout << "lower_bound out of bounds" << endl;
                       return this->end();
                   } else {
                       if (current_node->kids->lower_bound(word[0]) )
                   }
               }
                else {
                   current_node = path.top();
               }
           }

        }
    }; // first element >= testElement
    iterator upper_bound(const key_type& testElement); // first element > testElement
    iterator find(const key_type& testElement); // first element == testElement
    iterator begin(){
        bool
        while(true){

        }
    }; // returns end() if not found
    iterator end();*/
};

#endif //TRIE_TRIE_
