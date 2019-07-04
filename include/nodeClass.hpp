#pragma once
#include "common_include.h"

class nodeClass {

public:

int node_start=-1;
nodeClass* father=nullptr;
int node_index=-1;
int children_count=0;
float node_less_prob=-1.0;
float node_probability=-1.0;
float    ob_x=0;
float    ob_y=0;
float _yaw=0.0;
float _scale=1.0;
bool Ignore_this_point=false;
int _print_seq_cut_length=1;
vector<int> containSeq;
vector<float> constainX;
vector<float> constainY;
    nodeClass();
    nodeClass(int node_index);
    void appendNode(nodeClass* child);
    void outFatherSeq();
    ~nodeClass();
private:

vector<nodeClass*> _children;


};