#include "nodeClass.hpp"

nodeClass::nodeClass(int node_index) {
    this->node_index=node_index;
}

nodeClass::~nodeClass() {
    for(auto var : _children)
    {
        if (var!=nullptr)
        {
            delete var;
            var=nullptr;
        }
    }
}

void nodeClass::appendNode(nodeClass* child){
    _children.push_back(child);
    child->father=this;
    child->node_start=node_start;
    children_count+=1;
}

vector<int> nodeClass::outFatherSeq(){
    containSeq.clear();
    constainX.clear();
    constainY.clear();
    nodeClass* cur_item=father;
    while (cur_item!=nullptr)
    {
        /*  */
        containSeq.push_back(cur_item->node_index);
        constainX.push_back(cur_item->ob_x);
        constainY.push_back(cur_item->ob_y);
        cur_item=cur_item->father;
    }
    reverse(containSeq.begin(),containSeq.end());
    return containSeq;
    
}