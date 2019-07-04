#include <iostream>
#include "nodeClass.hpp"
#include "fastDtw.hpp"
using namespace std;

// int main3(int argc, const char** argv) {
//     vector<float> x={48.6280289, 48.7419357, 49.2980804, 49.4285774, 48.5894852,
//        48.2236748, 49.3317413, 50.2540627, 50.9985771};
    
//     vector<float>  y={49.694973 , 47.2558098, 46.0036201, 47.1931267, 46.2354965,
//        42.7104645, 45.4454689, 44.0454712, 44.1697197};
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
int main(int argc, char const *argv[])
{
    for (size_t i = 0; i < 100; i++)
    {
        // cout<<_define_random_rand()<<endl;
        printf("%.3f ..\r\n",_define_random_rand());
    }
    
    return 0;
}



// int main2() {
//     std::cout << "Hello Easy C++ project!" << std::endl;
//     nodeClass* nssss=new nodeClass(-10);
//     nodeClass* ns= new nodeClass(-2);
//     nssss->appendNode(ns);
//     nodeClass* ts=nullptr;   
//     for (int i = 0; i < 10; i++)
//     {
//         ts=new  nodeClass(i);
//         ns->appendNode(ts);
//         cout<<"ssdsdds"<<ns->children_count<<endl;
//         cout<<"bbbb"<<ts->father->node_index<<endl;
//     }

//     ns= new nodeClass(-3);
//     nssss->appendNode(ns);
//     for (int i = 0; i < 10; i++)
//     {
//         ts=new  nodeClass(i+100);
//         ns->appendNode(ts);
//         cout<<"ssdsdds"<<ns->children_count<<endl;
//         cout<<"bbbb"<<ts->father->node_index<<endl;
//     }

//     vector<int > result=ts->containSeq;
//     cout<<"aaaaaa"<<result.size()<<endl;
//     for(auto var : result)
//     {
//         cout<<"sds"<<var<<endl;
//     }
        
//     if(nssss!=nullptr){
//     delete nssss;
//     nssss=nullptr;
//     }
// }