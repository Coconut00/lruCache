#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
vector<int> rs;
class Memory{
private:
    int memory_size_;
    int lru_size_;
    vector<int> memory_space;
    vector<int> lru_queue;
public:
    Memory(int memory_size);
    void LRU();
    void FIFO();
    void OPT();
    void CLOCK();
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
                lru_queue.pop_back();
                lru_queue.insert(lru_queue.begin(), *itrrs);
                memory_space.erase(itrmemory-1);
                memory_space.push_back(*itrrs);
            }
        }
    }
}

void Memory::FIFO(){
    vector<int>::iterator itrrs = rs.begin();
    int replace_position = 0;
    for(; itrrs!=rs.end(); ++itrrs){
        vector<int>::iterator itrmemory = find(memory_space.begin(), memory_space.end(), *itrrs);
        //在虚拟内存中寻找到要访问的页面
        if(itrmemory != memory_space.end()) continue;
        //在虚拟内存中没找到要访问的页面
        else{
            /*
            空间够的情况：
                在虚拟内存空间中插入该页面号
            */
            if(memory_space.size() < memory_size_)
                memory_space.push_back(*itrrs);
            /*
            空间不够的情况：
                1、删除replace_position所指虚拟内存位置的数值
                2、在该位置插入要访问的页面号
                3、更新replace_position
            */
            else{
                memory_space.erase(memory_space.begin()+replace_position);
                memory_space.insert(memory_space.begin()+replace_position, *itrrs);
                replace_position = (replace_position+1) % memory_size_;
           }
        }
    }
}

void Memory::OPT(){
    int rs_used = 0;
    vector<int>::iterator itrrs = rs.begin();
    for(; itrrs!=rs.end(); ++itrrs){
        vector<int>::iterator itrmemory = find(memory_space.begin(), memory_space.end(), *itrrs);
        //在虚拟内存中寻找到要访问的页面，更新引用串已访问的位置
        if(itrmemory != memory_space.end()){
            rs_used++;
        }
        //在虚拟内存中没找到要访问的页面
        else{
            /*
            空间够的情况：
                在虚拟内存空间中插入该页面号，更新引用串已访问的位置
            */
            if(memory_space.size() < memory_size_){
                memory_space.push_back(*itrrs);
                rs_used++;
            }
            /*
            空间不够的情况：
                1、对虚拟内存空间中每个元素在引用串未访问过的位置进行迭代
                2、取所有元素的距离最大的一个，删除，在虚拟内存空间的该位置插入要访问的页面
                3、更新引用串已访问的位置
            */
            else{
                int memory_index = -1, rs_index, max_length = -1,replace_position = -1, flag = 0;
                bool is_find;
                for(; memory_index<memory_size_; ++memory_index){
                    is_find = false;
                    for(rs_index=rs_used; rs_index<rs.size(); ++rs_index){
                        if(memory_space[memory_index] == rs[rs_index]){
                            if(max_length < rs_index){
                                replace_position = memory_index;
                                max_length = rs_index;
                            }
                            is_find = true;
                            break;
                        }
                    }
                    //考虑极端情况，当虚拟内存空间的元素在引用串未访问过的位置没找到对应元素，则直接替换该位置的元素
                    if(!is_find){
                        memory_space.erase(memory_space.begin()+memory_index);
                        memory_space.insert(memory_space.begin()+memory_index, *itrrs);
                        flag = 1;
                        break;
                    }
                }
                if(!flag){
                    memory_space.erase(memory_space.begin()+replace_position);
                    memory_space.insert(memory_space.begin()+replace_position, *itrrs);
                }
            }
        }
    }
}

void Memory::CLOCK(){
    int clock_space[memory_size_];
    int clock_index = 0;
    memset(clock_space, 0, sizeof(clock_space));
    vector<int>::iterator itrrs = rs.begin();
    for(; itrrs!=rs.end(); ++itrrs){
        vector<int>::iterator itrmemory = find(memory_space.begin(), memory_space.end(), *itrrs);
        //在虚拟内存中寻找到要访问的页面，置该位置的标志位为1，更新指针位置
        if(itrmemory != memory_space.end()){
            clock_space[clock_index] = 1;
            clock_index = (clock_index+1) % memory_size_;
        }
        //在虚拟内存中没找到要访问的页面
        else{
            /*
            空间够的情况：
                在虚拟内存空间中插入该页面号，置该位置的标志位为1，更新指针位置
            */
            if(memory_space.size() < memory_size_){
                memory_space.push_back(*itrrs);
                clock_space[clock_index] = 1;
                clock_index = (clock_index+1) % memory_size_;
            }
            /*
            空间不够的情况：
                1、对clock_space进行迭代
                2、若标志位为1，则置0； 若标志位为0，则置换虚拟内存空间中该位置
                3、若迭代一遍之后没有进行置换操作，则重新进行迭代
            */
            else{
                
            }
        }
    }
}