#include "dataRead.hpp"

dataRead::dataRead(string file_name, vector<vector<float>> &table_data)
{
	ifstream inFile(file_name);
	string lineStr;
	int count = 0;

	while (getline(inFile, lineStr))
	{
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

void dataRead::s_dataRead(string file_name, vector<vector<float>> &table_data)
{
	ifstream inFile(file_name);
	string lineStr;
	int count = 0;

	while (getline(inFile, lineStr))
	{
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
void dataRead::s_dataWrite(string file_name, vector<vector<float>> &table_data)
{
	ofstream OpenFile(file_name);
	if (OpenFile.fail()) 
	{
		// std::cout << "/* message */" << std::endl;
		return ;
	}
	for(auto var : table_data)
	{
		for (size_t i = 0; i < var.size(); i++)
		{
			if(i==var.size()-1)
			{
				OpenFile<<var[i];
			}
			else
			{
				OpenFile<<var[i]<<",";
			}
			
			
		}
		
		OpenFile<<endl;
	}

	OpenFile.close();
}

dataRead::~dataRead()
{
}