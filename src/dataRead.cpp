#include "dataRead.hpp"

dataRead::dataRead(string file_name,vector<vector<float>> &table_data) {
    ifstream inFile(file_name);
	string lineStr;
	int count=0;

	while (getline(inFile, lineStr))  {
	stringstream ss(lineStr);
	string str;  
	vector<float> lineArray;  
	// 按照逗号分隔  
	
	while (getline(ss, str, ','))  
	{
		lineArray.push_back(atof(str.c_str())); 	
	}
    table_data.push_back(lineArray);
    }
    inFile.close();
}

void static s_dataRead(string file_name,vector<vector<float>> &table_data)
{
    ifstream inFile(file_name);
	string lineStr;
	int count=0;

	while (getline(inFile, lineStr))  {
	stringstream ss(lineStr);
	string str;  
	vector<float> lineArray;  
	// 按照逗号分隔  
	
	while (getline(ss, str, ','))  
	{
		lineArray.push_back(atof(str.c_str())); 	
	}
    table_data.push_back(lineArray);
    }
    inFile.close();	
}

dataRead::~dataRead() {

}