# lruCache
A LRU cache implemented in C++ for practicing and better understanding the LRU algorithm.  
uses vector to simulate the memory space and LRU queue.

## Replacement Time
Length of reference string: 1000  
Length of virtual memory space: 3
algorithm | replacement frequency 
 - | - 
FIFO | 440
CLOCK | 437
OPT | 271
LRU | 429

## TODO
- [x] Finish the test scripts for LRU cache
- [x] Add FIFO、OPT、CLOCK algorithm for comparison
- [x] Caculate the frequency of replacement for each algorithm mentioned above
- [ ] improve the code style and runtime for LRU cache