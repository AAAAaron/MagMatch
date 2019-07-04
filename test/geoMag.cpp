#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "nodeClass.hpp"
#include "fastDtw.hpp"
#include "dataRead.hpp"
#include "magMatchBase.hpp"
using namespace std;

int main(int argc, const char** argv) {

    vector<vector<float>> datafp,testdata;
    string filename="/home/aaron/project/MapMatching/data/allSecD_nohead.csv";
    string filetest="/media/aaron/新加卷/工作记录/项目产出及记录/19年羲和后台过程归档/第二阶段材料整理/测试过程/iosFp/my_iOS_device_2019-06-26_16-48-43_+0800data.csv";
    dataRead DR=dataRead(filename,datafp);
    dataRead::s_dataRead(filetest,testdata);
    printf("%ldX%ld\r\n",testdata.size(),testdata[0].size());

    magMatchBase ts1=magMatchBase();
    // ts1.magMatchBase_init(10,M_PI,data);
    ts1.magMatchBase_init(0,7000,0.0,datafp,12);
    
    cout<<ts1.finger_mark.size()<<endl;
    
    for (size_t i = 0; i <330; i++)
    {
        if(testdata[i][2]<1e-9)
        {
            continue;
        }
        if (i==8)
        {
            cout<<"------"<<endl;
            /* code */
        }
        cout<<"index="<<i<<endl;
        float mmagn=sqrt(testdata[i][5]*testdata[i][5]+testdata[i][6]*testdata[i][6]+testdata[i][7]*testdata[i][7]);
        float rs=ts1.processData(testdata[i][2],testdata[i][3],mmagn);
        

        
        // if (rs!=-1)
        // {
        //     /* code */ts1.print_min_seq();
        // }
        
    }
    ts1.get_current_node_info2("../data/info.csv");
    ts1.print_min_seq();
    ofstream out2f("../data/data.csv");
    // ts1.get_current_node_list();
    for(auto var : ts1.out_put_dis)
    {
        out2f<<var.x<<","<<var.y<<","<<var.z<<endl;
    }
    out2f.close();
    

}