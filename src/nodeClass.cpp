#include "nodeClass.hpp"

nodeClass::nodeClass() {
}

nodeClass::nodeClass(int node_index) {
    this->node_index=node_index;
}

nodeClass::~nodeClass() {
    // cout<<"node_index"<<node_index<<endl;
    if (_children.size()==0)
    {
        /* code */
    }
    else{
    for(auto var : _children)
    {
        if (var!=nullptr)
        {
            // cout<<"xxxxxxx";
            delete var;
            var=nullptr;
        }
    }
    }
}

void nodeClass::appendNode(nodeClass* child){
    _children.push_back(child);
    child->father=this;
    child->node_start=node_start;
    children_count+=1;
    child->_print_seq_cut_length=_print_seq_cut_length;
    child->outFatherSeq();//添加即可执行
}

void nodeClass::outFatherSeq(){
    containSeq.clear();
    constainInfo.clear();
    nodeClass* cur_item=this;
    while (cur_item!=nullptr)
    {
        /*  */
        if (cur_item->Ignore_this_point)
        {
            cur_item=cur_item->father;
            continue;
        }
        containSeq.push_back(cur_item->node_index);
        vector<float> tmp;
        tmp.push_back(cur_item->ob_x);
        tmp.push_back(cur_item->ob_y);
        tmp.push_back(cur_item->_scale);
        tmp.push_back(cur_item->_yaw);
        constainInfo.push_back(tmp);
        cur_item=cur_item->father;
    }
    reverse(containSeq.begin(),containSeq.end());
    reverse(constainInfo.begin(),constainInfo.end());
    for (size_t _ = 0; _ <_print_seq_cut_length ; _++)
    {
        if(containSeq.size()>=1)
        {
             containSeq.erase(containSeq.begin());
             constainInfo.erase(constainInfo.begin());
        }
    }
    
   
}