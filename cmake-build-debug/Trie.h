//
// Created by nikol on 10.12.2019.
//

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <vector>

using namespace std;


template <class T, class E=char>
class Trie {

public:
    typedef basic_string<E> key_type;
    typedef pair<const key_type, T> value_type;
    typedef T mapped_type;

    static const key_type terminator = "#";

    class trie_iterator{

    };



    class Node{
        virtual void print(string prefix = "");

        virtual bool operator<(const Node &n);
    };

    class Knot: public Node{
        map<key_type, Node*> kids;

        void print(string prefix = ""){

            for(auto itr = kids.begin(); itr != kids.end(); itr++){
                if(itr->first != terminator) {
                    cout << prefix << itr->first() << endl;
                }
                itr->second.print(prefix + " ");
            }
        }

    };

    class Leaf: public Node{
        key_type value;

        void print(string prefix = ""){
            cout << prefix << value << endl;
        }
    };

    Knot *root = nullptr;

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

    typedef TrieIterator iterator;

    bool empty() const {
        return root == nullptr;
    };

    iterator insert(const value_type& value);

    void erase(const key_type& value);
    void clear(); // erase all

    iterator lower_bound(const key_type& testElement) {
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
    iterator end();
};
#endif //TRIE_TRIE_H
