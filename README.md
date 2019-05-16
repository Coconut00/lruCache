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

## TODO
- [x] Finish the test scripts for LRU cache
- [x] Add FIFO、OPT、CLOCK algorithm for comparison
- [x] Caculate the frequency of replacement for each algorithm mentioned above  

# v2.0.0
## Summary
Clearly, using vector to implement LRU cache isn't a perfect choice and hash map can do much better than that. So in this version, I tried to use unordered_map and link-list to rewrite the LRU cache.
