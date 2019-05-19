# lruCache
A LRU cache implemented in C++ for practicing and better understanding the LRU algorithm.  

# v1.0.0
## Summary  
Uses vector as memory space and vector. Besides, I wrote a small test function to the represent replacement frequency using LRU/FIFO/CLOCK/OPT.  
The results are as follows.
## Replacement Time
Length of reference string: 1000  
Length of virtual memory space: 3

| algorithm | replacement frequency |  
| ------------- |:-------------:|
| FIFO | 440 |  
| CLOCK | 437 |
| OPT | 271 |
| LRU | 429 |

# v2.0.0
## Summary
Clearly, using vector to implement LRU cache isn't a perfect choice and hash map can do much better than that. So in this version, I tried to use unordered_map and link-list to rewrite the LRU cache.  
## Usage example  
```cpp
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
```
