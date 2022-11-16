#include <iomanip>
#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <chrono>
#include "MyBloom.h"
#include "MurmurHash3.h"
#include "Rambo_construction.h"
#include "utils.h"
#include "constants.h"
#include <ctime>
#include <unordered_map>
#include <unordered_set>
using namespace std;



int main(int argc, char **argv) {

    bool insert = false;
    bool ser = false;
    bool test = false;
    bool deser = true;

    int n_perSet = 100000; //num of items(judge how to build bloomfilter)
    int R_all = 3;
    int B_all = 1000;

    //int K = Ki; // total number of sets
    int K = 10000000;

    double insert_raw = 0;
    double insert_rambo = 0;
    double search_time = 0;

    //test blockchain data！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！

    //fstream f("test_modified.txt");
    fstream f("tag_and_edge_modified.txt");
    //fstream f("xaa");
    //unordered_set<string> key_set;
    //std::unordered_map<string, unordered_set<int>> key_set;
    //int start = 4000000; //开始块范围
    int start = 4638567;
    //int end = 4981465;
    //int end = 13000000; 
    int end = 12210044;
    //int end = 8165992; //结束块范围
    string line;
    
    int bias = start - 1;
    K = end - bias;

    //创建Rambo
    //cout<<"start build myrambo"<<endl;
    RAMBO myRambo(n_perSet, R_all, B_all, K);

    //
    int now_insert_num = 0;
    //cout<<"start insert lines"<<endl;

    //文件获取每行插入
    while(getline(f,line)){
        std::vector<string> KeySets = line2array(line, ';');


        now_insert_num++;
        if(now_insert_num%100000==0){
            cout<<"having insert "<<now_insert_num<<" keys!"<<endl;
        }

        //std::clock_t insert1 = std::clock();
        //key_set[KeySets[0]].insert(atoi(KeySets[1].c_str()));
        //std::clock_t insert2 = std::clock();

        myRambo.createMetaRambo_single(atoi(KeySets[1].c_str())); //插入meta信息

        myRambo.insertion_pair(make_pair(KeySets[0], KeySets[1]));//插入keyvalue对
        //std::clock_t insert3 = std::clock();

        //insert_raw += double(insert2-insert1)/CLOCKS_PER_SEC;
        //insert_rambo += double(insert3-insert2)/CLOCKS_PER_SEC;
    }

    
    return 0;
}
