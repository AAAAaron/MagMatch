#include <iostream>
#include "nodeClass.hpp"
#include "fastDtw.hpp"
using namespace std;

// int main(int argc, const char** argv) {
//     vector<float> x={-52.028,-53.014,-52.2958,-50.6336,-50.0742,-50.4611,-51.681,-51.5819,-48.8544,-45.835,-46.911,-48.8074,-47.7574,-43.7419,-40.0825,-37.5645,-37.1865,-36.6298,-38.845,-38.5716,-39.5176,-41.5561};
    
//     vector<float>  y={-40.0825,-37.5645,-37.1865,-36.6298,-38.845,-38.5716,-39.5176,-41.5561,-41.9617,-39.5357,-44.9475,-47.0937,-45.7272,-44.797,-43.6881,-43.5519,-43.84,-45.8267,-47.1882,-50.2573,-52.6531};
//     // vector<float> x={1,2,3,4,5};
//     // vector<float>y={2,3,4};

//     float distance=0.0;
//     vector<pair_2> path;
//     fastDtw::fastdtw(x,y,&distance,path);
//     // fastDtw::dtw(x,y,&distance,path);
//     cout<<"distance"<<distance<<endl;
//     for(auto var : path)
//     {
//         cout<<var.x<<"--"<<var.y<<endl;
//     }
    
//     return 0;
// }



int main() {
    std::cout << "Hello Easy C++ project!" << std::endl;
    nodeClass* nssss=new nodeClass(-10);
    nodeClass* ns= new nodeClass(-2);
    nssss->appendNode(ns);
    nodeClass* ts=nullptr;   
    for (int i = 0; i < 10; i++)
    {
        ts=new  nodeClass(i);
        ns->appendNode(ts);
        cout<<"ssdsdds"<<ns->children_count<<endl;
        cout<<"bbbb"<<ts->father->node_index<<endl;
    }

    ns= new nodeClass(-3);
    nssss->appendNode(ns);
    for (int i = 0; i < 10; i++)
    {
        ts=new  nodeClass(i+100);
        ns->appendNode(ts);
        cout<<"ssdsdds"<<ns->children_count<<endl;
        cout<<"bbbb"<<ts->father->node_index<<endl;
    }

    vector<int > result=ts->containSeq;
    cout<<"aaaaaa"<<result.size()<<endl;
    for(auto var : result)
    {
        cout<<"sds"<<var<<endl;
    }
        
    if(nssss!=nullptr){
    delete nssss;
    nssss=nullptr;
    }
}