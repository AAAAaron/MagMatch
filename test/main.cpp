#include <iostream>
#include "nodeClass.hpp"
#include "fastDtw.hpp"
#include <type_traits>  // 注意包含此头文件.
using namespace std;

int main(int argc, const char** argv) {
    float x[]={1,2,3,4,5};
    float y[]={2,3,4};
    float distance=0.0;
    int len_all=max(5,3);
    int x_index[5]={0};
    int y_index[5]={0};
    int x_index_len;
    int y_index_len;
    fastDtw::dtw(x,5,y,3,distance,x_index,x_index_len,y_index,y_index_len);
    cout<<"distance"<<distance<<endl;
    for (int i = 0; i < x_index_len; i++)
    {
        cout<<"x:"<<x_index[i]<<"y:"<<y_index[i]<<endl;
    }
    
    


    return 0;
}



// int main_test_node() {
//     std::cout << "Hello Easy C++ project!" << std::endl;
//     nodeClass ns=nodeClass(10);
//     nodeClass* ts=nullptr;
    
//     for (int i = 0; i < 10; i++)
//     {
//         ts=new  nodeClass(i);
//         ns.appendNode(ts);
//         cout<<"ssdsdds"<<ns.children_count<<endl;
//         cout<<"bbbb"<<ts->father->node_index<<endl;
//     }
//     vector<int > result=ts->outFatherSeq();
//     cout<<"aaaaaa"<<result.size()<<endl;
//     for(auto var : result)
//     {
//         cout<<"sds"<<var<<endl;
//     }
    
    
//     delete ts;
//     ts=nullptr;

// }