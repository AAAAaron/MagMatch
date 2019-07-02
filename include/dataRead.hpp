#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
class dataRead {

public:
    dataRead(string file_name,vector<vector<float>> &table_data);
    void static s_dataRead(string file_name,vector<vector<float>> &table_data);
    ~dataRead();
};