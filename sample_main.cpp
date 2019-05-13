#include<time.h>
#include"LRU.hpp"

const int kMoveRate = 5; //工作面移动率，即处理moveRate个引用后将起始位置加1
const int kStartPos = 0; //工作面的起始位置
const int kPageSize = 100;   //虚拟内存的尺寸
const int kPageNum = 5;  //工作面中包含的页面数
const int kVibrateRate = 0.3;    //工作面剧烈抖动率
const int kFinalRsSize = 100;    //RS串最终长度
vector<int> rs;
/*
生成产生串
*/
void GenerateRS(vector<int>& rs, int kMoveRate, int kStartPos, int kPageSize, int kPageNum, int kVibrateRate, int kFinalRsSize){
    int length = 0;
    srand(time(0));
    while(length < kFinalRsSize){
        for(int step=0; step<kMoveRate; ++step){
            rs.push_back(rand() % (kPageNum - kStartPos + 1) + kStartPos);
            length++;
        }
        int random_num = rand() % 100 / (double) 101;
        if(random_num < kVibrateRate)
            kStartPos = rand() % kPageSize;
        else
            kStartPos = (kStartPos + 1) % kPageSize;
    }
}
int main(){
    
}