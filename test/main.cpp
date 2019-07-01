#include <iostream>
#include "nodeClass.hpp"
#include "fastDtw.hpp"
#include <type_traits>  // 注意包含此头文件.
using namespace std;

int main(int argc, const char** argv) {
    vector<float> x={-52.028,-53.014,-52.2958,-50.6336,-50.0742,-50.4611,-51.681,-51.5819,-48.8544,-45.835,-46.911,-48.8074,-47.7574,-43.7419,-40.0825,-37.5645,-37.1865,-36.6298,-38.845,-38.5716,-39.5176,-41.5561};
    
    vector<float>  y={-40.0825,-37.5645,-37.1865,-36.6298,-38.845,-38.5716,-39.5176,-41.5561,-41.9617,-39.5357,-44.9475,-47.0937,-45.7272,-44.797,-43.6881,-43.5519,-43.84,-45.8267,-47.1882,-50.2573,-52.6531};
    // vector<float> x={1,2,3,4,5};
    // vector<float>y={2,3,4};

    float distance=0.0;
    vector<pair_2> path;
    fastDtw::fastdtw(x,y,&distance,path);
    // fastDtw::dtw(x,y,&distance,path);
    cout<<"distance"<<distance<<endl;
    for(auto var : path)
    {
        cout<<var.x<<"--"<<var.y<<endl;
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