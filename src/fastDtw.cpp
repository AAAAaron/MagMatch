#include "fastDtw.hpp"


void fastDtw::s_fastDtw(float *x, float *y,float distance,int *x_index,int *y_index, FunctionName fn , float radius )
{

}

float fastDtw::s__difference(float a,float b)
{
    return abs(a-b);
}

void fastDtw::s__prep_input(float*x,float*y, FunctionName dist)
{

}


void fastDtw::s__dtw(float *x,int len_x,float *y,int len_y,float distance,int* x_index,int x_index_len,int* y_index,int y_index_len,FunctionName dist )
{
    float *D;
    D[0]=0;
    int *D1;
    int *D2;
    D1[0]=0;
    D2[0]=0;

    if (x_index_len>0&& y_index_len>0)
    {
        for (int i = 0; i < x_index_len; i++)
        {
            x_index[i]+=1;
        }
        for (int j = 0; j < y_index_len; j++)
        {
            y_index[j]+=1;
        }
        
    }
    else
    {
        x_index_len=len_x;
        y_index_len=len_y;
        for (int i = 0; i < x_index_len; i++)
        {
            x_index[i]=i+1;
        }
        for (int j = 0; j < y_index_len; j++)
        {
            y_index[j]=j+1;
        }        
    }


    for (int x_i = 1; x_i < x_index_len+1; x_i++)
    {
        D[x_i*x_index_len]=0;
        D1[x_i*x_index_len]=0;
        D2[x_i*x_index_len]=0;
    }
    for (int y_i = 1; y_i < y_index_len+1; y_i++)
    {
        D[y_i]=0;
        D1[y_i]=0;
        D2[y_i]=0;
    }    
    for (int x_i = 0; x_i < x_index_len; x_i++)
    {
        for (int y_i = 0; y_i < y_index_len; y_i++)
        {
            float dt=dist(x[x_index[x_i]-1],y[y_index[y_i]-1]);
            D[x_index[x_i]*x_index_len+y_index[y_i]]=min(D[(x_index[x_i]-1)*x_index_len+y_index[y_i]],D[x_index[x_i]*x_index_len+(y_index[y_i]-1)]);
            D[x_index[x_i]*x_index_len+y_index[y_i]]=min(D[(x_index[x_i]-1)*x_index_len+(y_index[y_i]-1)],D[x_index[x_i]*x_index_len+y_index[y_i]]);
            if (D[(x_index[x_i]-1)*x_index_len+y_index[y_i]]==D[x_i*x_index_len+y_index[y_i]])
            {
                D1[x_index[x_i]*x_index_len+y_index[y_i]]=x_index[x_i]-1;
                D2[x_index[x_i]*x_index_len+y_index[y_i]]=y_index[y_i];
            }
            else if (D[(x_index[x_i])*x_index_len+y_index[y_i]-1]==D[x_i*x_index_len+y_index[y_i]])
            {
                D1[x_index[x_i]*x_index_len+y_index[y_i]]=x_index[x_i];
                D2[x_index[x_i]*x_index_len+y_index[y_i]]=y_index[y_i]-1;
            }
            else
            {
                D1[x_index[x_i]*x_index_len+y_index[y_i]]=x_index[x_i]-1;
                D2[x_index[x_i]*x_index_len+y_index[y_i]]=y_index[y_i]-1;                
            }
            D[x_index[x_i]*x_index_len+y_index[y_i]]+=dt;
        }
        
    }
    int i=len_x;
    int j=len_y;
    int* rx;
    int* ry;
    int count=0;
    while (!(i==0 && j==0))//替代i==j==0,
    {
        rx[count]=i-1;
        ry[count]=j-1;
        i=D1[i+x_index_len+j];
        j=D2[i+x_index_len+j];
        count+=1;
    }
    for (int i = 0; i < count; i++)
    {
        x_index[i]=rx[count-i-1];
        y_index[i]=ry[count-i-1];
    }
    distance=D[len_x,len_y];
    x_index_len=count-1;
    y_index_len=count-1;
}

void fastDtw::dtw(float *x,int len_x,float *y,int len_y,float distance,int* x_index,int x_index_len,int* y_index,int y_index_len,FunctionName dist )
{    
    s__dtw(x,len_x,y,len_y,distance, x_index,x_index_len, y_index,y_index_len,s__difference);
}