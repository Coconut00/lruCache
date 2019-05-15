#include<ctime>
#include"LRU.hpp"

const int kMoveRate = 5; //工作面移动率，即处理moveRate个引用后将起始位置加1
int kStartPos = 0; //工作面的起始位置
const int kPageSize = 3;   //虚拟内存页面总数
const int kPageNum = 5;  //工作面中包含的页面数
const int kVibrateRate = 0.3;    //工作面剧烈抖动率
const int kFinalRsSize = 1000;    //RS串最终长度

int sum = 0;
/*
生成产生串
*/
void GenerateRS(vector<int>& rs, int kMoveRate, int kStartPos, int kPageSize, int kPageNum, int kVibrateRate, int kFinalRsSize){
    int length = 0;
    srand((unsigned)time(NULL));
    while(length < kFinalRsSize){
        for(int step=0; step<kMoveRate; ++step){
            if(kPageNum - kStartPos + 1 != 0){
                rs.push_back(rand() % (kPageNum - kStartPos + 1) + kStartPos);
                length++;
            }
            else{
                rs.push_back(rand() % (kPageNum - kStartPos + 2) + kStartPos);
                length++;
            }
        }
        int random_num = rand() % 100 / (double) 101;
        if(random_num < kVibrateRate)
            kStartPos = rand() % kPageSize;
        else
            kStartPos = (kStartPos + 1) % kPageSize;
    }
}
void test(){
    GenerateRS(rs, kMoveRate, kStartPos, kPageSize, kPageNum, kVibrateRate, kFinalRsSize);
    Memory memory(3);   
    //clock_t start, end;
    //start = clock();
    memory.OPT();
    //end = clock();
    cout<<replace_count<<endl;
}
int main(){
    test();
    return 0;
}