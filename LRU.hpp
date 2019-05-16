#include<unordered_map>
#include<iostream>
using namespace std;

struct LRUNode{
    int key;
    int value;
    LRUNode* prev;
    LRUNode* next;
};

class LRU{
    private:
        unordered_map<int, LRUNode*> hashmap;
        LRUNode* head;
        LRUNode* tail;
    public:
        LRU();
        ~LRU();
        int get(int key);
        void replace();
};

LRU::LRU(){
    head = new LRUNode;
    tail = new LRUNode;
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;
}

LRU::~LRU(){
    delete head;
    delete tail;
}

int LRU::get(int key){
    if(hashmap.find(key) != hashmap.end()){
        LRUNode* node = hashmap[key];

        node->prev->next = node->next;
        node->next->prev = node->prev;

        node->next = head->next;
        node->prev = head;
        head->next = node;
        head->next->prev = head;

        return node->value;
    }
    else
        return -1;
}

void LRU::replace(){
    
}

