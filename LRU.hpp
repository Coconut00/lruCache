#include<unordered_map>
#include<iostream>
using namespace std;

struct LRUNode{
    int key_;
    int value_;
    LRUNode* prev;
    LRUNode* next;
};

class LRU{
    private:
        unordered_map<int, LRUNode*> hashmap;
        LRUNode* head;
        LRUNode* tail;
        int capacity_;
        int count_;
    public:
        LRU(int capacity);
        ~LRU();
        int get(int key);
        void insert(int key, int value);
};

LRU::LRU(int capacity){
    this->count_ = 0;
    this->capacity_ = capacity;
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

        return node->value_;
    }
    else
        return -1;
}

void LRU::insert(int key, int value){
    if(hashmap.find(key) != hashmap.end()){
        LRUNode* node = hashmap[key];

        node->prev->next = node->next;
        node->next->prev = node->prev;

        node->value_ = value;

        node->next = head->next;
        node->prev = head;
        head->next = node;
        node->next->prev = node;
    }
    else{
        LRUNode* node = new LRUNode;
        if(count_ == capacity_){
            LRUNode* tempnode = tail->prev;

            tempnode->prev->next = tempnode->next;
            tempnode->next->prev = tempnode->prev;
            hashmap.erase(tempnode->key_);
            --count_;
        }
        node->key_ = key;
        node->value_ = value;
        hashmap[key] = node;

        node->next = head->next;
        node->prev = head;
        head->next = node;
        node->next->prev = node;
        ++count_;
    }
}

