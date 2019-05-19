#include"LRU.hpp"

int main(){
    LRU lru(5);
    lru.insert(1,10);
    lru.insert(2,20);
    lru.insert(3,30);
    lru.insert(4,40);
    lru.insert(5,50);

    int value1 = lru.get(4);
    cout<<value1<<endl;

    lru.insert(6,60);
    int value2 = lru.get(1);
    cout<<value2<<endl;
    int value3 = lru.get(6);
    cout<<value3<<endl;
    return 0;
}