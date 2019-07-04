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
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <ctime>

// template <class T>
float static _define_random_rand()
{
    // srand((unsigned)time(NULL));
    return rand() / double(RAND_MAX);
    
};
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
// template <class T>
struct pair2_xy
{
    float x;
    float y;
    pair2_xy(float _x,float _y):x(_x),y(_y){};
};

template <class T>
struct pair_3
{
    T x;
    T y;
    T z;
    pair_3(T _x,T _y,T _z):x(_x),y(_y),z(_z){};
};
struct mag_data
{
    float x;
    float y;
    float mmagn;//地磁模值
    mag_data(float _x,float _y,float _mmagn):x(_x),y(_y),mmagn(_mmagn){};
};

typedef float (* FunctionName)(float ,float );
#endif