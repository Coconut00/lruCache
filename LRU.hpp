#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Memory{
private:
    int memory_size_;
    int lru_size_;
    vector<int> memory_space;
    vector<int> lru_queue;
public:
    Memory(int memory_size);
    ~Memory();
    void LRU();
};

Memory::Memory(int memory_size){
    memory_size_ = memory_size;
    lru_size_ = memory_size;
}

void Memory::LRU(){
    vector<int>::iterator itrrs = rs.begin();
    for(; itrrs!=rs.end(); ++itrrs){
        vector<int>::iterator itrmemory = find(memory_space.begin(), memory_space.end(), *itrrs);
        //在虚拟内存中找到要访问的页面，更新lru_queue
        if(itrmemory != memory_space.end()){
            vector<int>::iterator itrlru = find(lru_queue.begin(), lru_queue.end(), *itrrs);
            if(itrlru != lru_queue.end()){
                int temp = *itrlru;
                lru_queue.erase(itrlru);
                lru_queue.insert(lru_queue.begin(), temp);
            }
        }
        /*
        在虚拟内存中没找到要访问的页面，由于虚拟内存和lru相当于是引用的关系，因此二者的size大小时刻相等
        需要分以下两种情况讨论:
            1、虚拟内存空间够 && lru_queue够
            2、虚拟内存空间不够 && lru_queue不够
        */
        else{
            /*
            空间够的情况：
                1、在虚拟内存空间中插入该页面号
                2、在lru_queue中插入该页面号，更新
            */
            if((memory_space.size() < memory_size_) && (lru_queue.size() < lru_size_)){
                memory_space.push_back(*itrrs);
                lru_queue.insert(lru_queue.begin(), *itrrs);
            }
            /*
            空间不够的情况：
                1、从lru_queue的队尾选取要被置换的页面号
                2、在lru_queue中删除该页面号，插入新的页面号，更新
                3、在虚拟内存空间中删除该页面号，插入新的页面号
            */
            else{
                int page_replace_num = lru_queue[lru_size_ - 1];
                lru_queue.pop_back();
                lru_queue.insert(lru_queue.begin(), *itrrs);
                memory_space.erase(itrmemory);
                memory_space.push_back(*itrrs);
            }
        }
    }
}