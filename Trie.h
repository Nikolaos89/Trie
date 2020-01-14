


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


    class TrieIterator {
        typedef TrieIterator iterator;
        typedef typename map<key_type, Node*>::iterator map_iterator;
    private:

        typedef pair<map_iterator, map_iterator> breadcrumb;
        Trie *myTrie;
        Knot *myCursor;
        stack<breadcrumb> parents;
        Leaf* value ;

    public:

        TrieIterator(Trie *myTree){
            this->myTrie = myTree;
            myCursor = nullptr;
        }

        TrieIterator(Trie *myTrie, value_type paar){
            key_type keyword= paar.first;
            if(keyword.empty()){
TrieIterator(*myTrie);
              //  return TrieIterator(*myTrie);
            } else {
                myCursor = myTrie->root;
                key_type search = keyword + "#";
                this->myTrie = myTrie;

                while (true) {
                    if (search == "") {
                        value= (Leaf*) myCursor;
                       break;
                    }
                    // Preparing the record for the current stage to add to the stack
                   /* string tofind= search.substr()*/
                    auto search_result = myCursor->kids.find(search.substr(0, 1));
                    auto end = myCursor->kids.end();
                    breadcrumb record(search_result, end);

                    // Checking if current letter is found
                    if (record.first != record.second) {
                        // If letter is found, record is stored on the stack, cursor is advanced to found node and first letter
                        // of the search string is removed. Loop is continued.
                        parents.push(record);
                        myCursor = (Knot*) search_result->second;
                        if(search.size()>1) {
                            search = search.substr(1);
                        }else{ search="";


                        }
                    }
                        // If not found a end() iterator is returned, signaling that the key was not found
                    else {
                        myCursor= nullptr;
                    }
                }
            }
        }

        iterator begin(Trie *myTrie){

            this->myTrie = myTrie;
            this->myCursor = myTrie->root;

            //If Trie is empty Iterator with empty Stack is returned
            if(myTrie->root.kids.empty()){
                return this;
            }

            while(true){
                // Preparing the record for the current stage to add to the stack
                auto search_result = this->myCursor->kids.find(terminator);
                auto end = this->myCursor->kids.end();
                breadcrumb record(search_result, end);

                // Checking if terminal sign is contained in current stage
                if (record.first == record.second) {
                    // If terminal sign is not found, record is stored on the stack, cursor is advanced to leftmost kid entry
                    this->parents.push(record);
                    this->myCursor = this->myCursor->kids.begin()->second;
                }
                    // If found: record is stored, cursor is advanced once more and Iterator is returned
                else {
                    this->parents.push(record);
                    this->myCursor = search_result->second;
                    return this;
                }
            }
        }

//Should return reference (T&) to
//item pointed at
        value_type & operator *() {
            return *myCursor;
        }

        iterator& operator =(const iterator& rhs) {
            this->myCursor=rhs.myCursor;
            this->myTrie=rhs.myTrie;
            this->parents=rhs.parents;
            return *this;
        }

        bool operator !=(const iterator& rhs) const {
            return parents.size() != rhs.parents.size();
        }

        bool operator ==(const iterator& rhs) const {
            return parents.size() == rhs.parents.size();
        }

        // nicht fertig
        iterator& operator ++() {
            if(this->parents.empty()){
                return *begin(this->myTrie);
            } else {
                while(true){

                }
            }

        }
    };

    typedef TrieIterator iterator;



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
iterator it=TrieIterator(this,value);
return  it;

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


        crawlp->kids.erase("#");


    };

    void clear(){
      /* mit iterator über tree iterieren und dann erase aufrufen*/
    }


    iterator lower_bound(const key_type& testElement) {
        return iterator(*this, testElement);
    }; // first element >= testElement


    iterator upper_bound(const key_type& testElement){
        return ++lower_bound(testElement);
    }; // first element > testElement

    iterator find(const key_type& testElement){
        return iterator(*this, testElement);
    }; // first element == testElement

    iterator begin(){
        return iterator(*this).begin();
    }; // returns end() if not found

    iterator end(){
        return iterator(*this);
    };

};

#endif //TRIE_TRIE_

