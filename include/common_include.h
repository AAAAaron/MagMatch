#ifndef COMMON_INCLUDE_H_
#define COMMON_INCLUDE_H_

// #include <Eigen/Core>
// #include <Eigen/Geometry>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
using namespace Eigen;

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// template <class T>
struct pair_2
{
    int x;
    int y;
    pair_2(int input_x,int input_y):x(input_x),y(input_y){};
    bool operator == (const pair_2 &a) const  
    {
        if(x==a.x&&y==a.y)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    };
   
};
// bool operator==(const struct  pair_2 & X,const struct pair_2 & Y)
// {
//     //return hash<string>()(X.num+X.file)==hash<string>()(Y.num+Y.file);
//     return (Y.x==X.x)&&(Y.y==X.y);
// }

struct pair_2_int_hash{
    size_t operator()( const struct pair_2  _r) const {
    string tmp=to_string(_r.x)+to_string(_r.y);
    return std::hash<string>()(tmp);
    }
};

template <class T>
struct pair_3
{
    T x;
    T y;
    T z;
};


typedef float (* FunctionName)(float ,float );
#endif