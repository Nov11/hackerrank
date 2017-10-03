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
class LRUCache : Cache{
    void remove(Node* node){
        if(node == nullptr || node == head){return;}
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void insert(Node* prev, Node* node){
        node->next = prev->next;
        prev->next->prev = node;
        node->prev = prev;
        prev->next = node;
    }
    
    void removeToFront(Node* prev, Node* node){
        remove(node);
        insert(prev, node);
    }
    public:
    LRUCache(int capacity){
        cp = capacity;
        Node* node = new Node(0,0);
        head = node;
        node->next = node;
        node->prev = node;
    }

    void set(int k, int v){
        if(mp.find(k) == mp.end()){
            Node* node = new Node(k, v);
            insert(head, node);
            mp[k] = node;
            if(mp.size() > cp){
                auto rm = head->prev;
                remove(rm);
                mp.erase(rm->key);
                delete rm;
            }
            return;
        }
        
        auto ptr = mp[k];
        ptr->value = v;
        removeToFront(head, ptr);
    }
    
    int get(int k){
        if(mp.find(k) == mp.end()){return -1;}
        auto node = mp[k];
        removeToFront(head, node);
        return node->value;
    }
};


int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
