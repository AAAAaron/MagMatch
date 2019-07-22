#include <iostream>
#include "nodeClass.hpp"
#include "fastDtw.hpp"
using namespace std;

int main(int argc, const char** argv) {
    vector<float> x={46.7526,47.5746,48.1369,49.2404,50.354,51.2559,51.3043,51.0213,50.8644,51.0506,50.9261,50.7425,50.7546,50.4562,49.7933,48.669,47.5004,47.1288,47.818,48.0042,48.9136,49.8093,49.835,50.3277,50.0627};
    
    vector<float>  y={48.4643,47.3412,45.6064,48.4934,48.4479,47.3004,46.5516,49.6772,46.1707,48.1215,48.2186,47.6292,48.0412,47.3778,45.853,45.8342,45.5006,47.486,48.5554,50.7551,48.1378,49.4849,49.0276,53.1466,56.5714};
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
// int main(int argc, char const *argv[])
// {
//     for (size_t i = 0; i < 100; i++)
//     {
//         // cout<<_define_random_rand()<<endl;
//         printf("%.3f ..\r\n",_define_random_rand());
//     }
    
//     return 0;
// }



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