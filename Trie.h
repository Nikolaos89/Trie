


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

    class TrieIterator {
    };

    typedef TrieIterator iterator;

    class Node {
    public:

        virtual Node *insert(char c) = 0;

        virtual Node *insert(value_type sol) = 0;

        virtual void print(int level)=0;




        //     virtual void print(string prefix = "");

        //    virtual bool operator<(const Node &n);
    };

    class Leaf : public Node {
    public:
        mapped_type val;


        Leaf() {}

        Node *insert(char c) {
            return nullptr;
        }

        Node *insert(value_type sol) {

        };


        void print(const int level) {
            for (int i = 0; i < level/2; i++) {
                cout << "   ";
            }
            cout << ":" << this->val << endl;
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

            void print(const int level) {
                for (auto &l: kids) {
                    if (l.first != "#") {
                        for (int tmp = 0; tmp <= level; tmp++) {
                            cout << "  ";

                        }
                        cout << l.first << endl;
                    }

                    l.second->print(level+2);

                }
            }

// inserts first terminator then Leaf returns the leaf
            Node *insert(value_type sol) {
                pair<map_iterator, bool> ret;
                typedef pair<key_type, Node *> entry;


                Leaf* ende = new Leaf();


                ende->val = sol.second;

                entry eintrag;
                eintrag.first = "#";
                eintrag.second = ende;

                kids.insert(eintrag);

                return eintrag.second;


            }

// returns Node the char inserted points to
            Node *insert(char c) {


                pair<map_iterator, bool> ret;
                typedef pair<key_type, Node *> entry;

                Node *neuer = getNewKnot();

                entry eintrag;
                eintrag.first = c;
                eintrag.second = neuer;

                ret = kids.insert(eintrag);

                map_iterator neu = ret.first;

                Node *returning = neu->second;
                return returning;
            }


        };


        Knot *root;

        Trie() {
            root = new Knot();
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

//Should return reference (T&) to
//item pointed at
        value_type & operator *() {
            return myCursor[current].element;
        }

        iterator& operator =(const iterator& rhs) {
            this->myCursor=rhs.myCursor;
            this->current=rhs.current;
            return *this;
        }

        bool operator !=(const iterator& rhs) const {


            return &myCursor[current]!=&rhs.myCursor[rhs.current];
        }

        bool operator ==(const iterator& rhs) const {
            return &myCursor[current]==&rhs.myCursor[rhs.current];
        }

        iterator& operator ++() {
            current= myCursor[current].next;

            return *this;

        }

        iterator operator ++(int) {
            iterator clone(*this);
            current=myCursor[current].next;

            return clone;
        }
        // postfix operator dummy parameter


    };





*/



        bool empty() const {

            return root->kids.empty();
        };


        iterator insert(const value_type &value) {
            key_type word = value.first;


            Knot *crawlp = root;


            char current;


            for (int j = 0; j < word.length(); j++) {

                current = word.at(j);

                Knot *gotback = (Knot *) crawlp->insert(current);

                crawlp = gotback;

            }
            crawlp->insert(value);

        };

        void print() {

root->print(0);
        };


// lege den weg bis leaf zurück und zählt dabei nodes. wenn verzweigung counter neusetzten
// counter = zulöschende elemente von leaf aus
// evtl umändern in stack da dann nodes gleich verfügbar
    void erase(const key_type &value) {

        key_type current;
        Knot *crawlp = root;
        int counter = 0;
        for (int j = 0; j < value.length(); j++) {
            counter++;
            current = value.at(j);
            if (crawlp->kids.size() != 1) {
                counter = 0;
            }
            crawlp = (Knot *) crawlp->kids.find(current)->second;
        }

        counter++; // für Leaf

        // iteration bis zum node der verzweigung
        int steps = value.length() - counter;
        crawlp = root;
        for (int j = 0; j < steps; j++) {
            current = value.at(j);
            crawlp = (Knot *) crawlp->kids.find(current)->second;

        }
        current = value.at(steps);

        Knot *safer = (Knot *) crawlp->kids.find(current)->second;
        while (true) {
            crawlp->kids.erase(current);
            current = safer->kids.begin()->first;
            if (current == "#") {
                break;
            }
            safer = (Knot *) safer->kids.begin()->second;
            crawlp = safer;
        }

        std::cout << current << endl;
        crawlp->kids.erase("#");


    };

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
