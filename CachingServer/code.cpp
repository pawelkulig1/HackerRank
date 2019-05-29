#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache: public Cache{
    int size;
    public:

    LRUCache(int capacity)
    {
        head = nullptr;
        tail = nullptr;
        this->cp = capacity;
        size = 0;
        mp = map<int, Node*>();
    }

    void set(int key, int value) override {
        if(size == 0 && cp > 0)
        {
            Node *n = new Node(nullptr, nullptr, key, value);
            tail = n;
            head = n;
            mp[key] = n;
            size++;
            return;
        }

        map<int, Node*>::iterator it = mp.find(key);

        if(it == mp.end()) //not in map - create new
        {
            if(size == cp) //delete last one
            {
                mp.erase(tail->key);
                Node *newTail = tail->prev;
                delete tail;
                tail = newTail;
                tail->next = nullptr;
                size--;
            }

            Node *n = new Node(nullptr, head, key, value);
            head->prev = n;
            head = n;
            size++;
            mp[key] = n;

        }
        else //move existing
        {
            Node *n = it->second;
            Node *left = n->prev;
            Node *right = n->next;
            if(left != nullptr)
                left->next = right;
            if(right != nullptr)
                right->prev = left;

            n->prev = nullptr;
            n->next = head;
            n->value = value;
            head->prev = n;
            head = n;
            mp[key] = n;
        }
    }

    int get(int key) override {
        if(mp.find(key) == mp.end())
            return -1;
        return mp[key]->value;
        
    }

    ~LRUCache(){
        Node *n = head;
        Node *next = n->next;
        while(n != nullptr){
            next = n->next;
            delete n;
            n = next;
        }
    }
};


int main() {
