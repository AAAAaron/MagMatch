#include "fastDtw.hpp"

void fastDtw::fastdtw(vector<float> x, vector<float> y,float *distance,vector<pair_2> &path, FunctionName fn , int radius )
{
    s__fastDtw(x,y,distance,path,s__difference,radius);
}

float fastDtw::s__difference(float a,float b)
{
    return abs(a-b);
}

void fastDtw::s__prep_input(vector<float> x, vector<float> y, FunctionName dist)
{

}


void fastDtw::s__dtw(vector<float> x, vector<float> y,vector<pair_2> &windows,float *distance,vector<pair_2> &path,FunctionName dist )
{
    int tmp;

    // int max_x_y;
    if (windows.size()==0)
    {
        for (int i = 0; i < x.size(); i++)
        {
            for (int j = 0; j < y.size(); j++)
            {
                windows.push_back(pair_2(i,j));
            }
        }  
        // cout<<x.size()<<"  "<<y.size()<<endl;
    }
    else
    {
        // cout<<windows.size()<<endl;
    }
    
    int x_max=0;
    int y_max=0;

    for (int i = 0; i < windows.size(); i++)
    {
        windows[i].x+=1;
        windows[i].y+=1;
        if (windows[i].x>x_max)
        {
            x_max=windows[i].x;
        }
        if(windows[i].y>y_max)
        {
            y_max=windows[i].y;
        }
    }
    

    x_max+=1;
    y_max+=1;
    // int max_x_y=max(x_max,y_max);
    vector<float> D(x_max*y_max,MAX_INF);
    D[0]=0;
    vector<int> D1(x_max*y_max,0);
    vector<int> D2(x_max*y_max,0);
    // x_max-=1;//很严重的一个bug
    // y_max-=1;    
    int count_s=0;
    for(auto var : windows)
    {
        int i=var.x;
        int j=var.y;
        float dt=dist(x[i-1],y[j-1]);
        D[i*y_max+j]=min(D[(i-1)*y_max+j],D[i*y_max+j-1]);
        D[i*y_max+j]=min(D[i*y_max+j],D[(i-1)*y_max+j-1]);
        if(D[i*y_max+j]==D[(i-1)*y_max+j])
        {
            D1[i*y_max+j]=i-1;
            D2[i*y_max+j]=j;
        }
        else if (D[i*y_max+j]==D[i*y_max+j-1])
        {
            D1[i*y_max+j]=i;
            D2[i*y_max+j]=j-1;            
        }
        else if (D[i*y_max+j]==D[(i-1)*y_max+j-1])
        {
            D1[i*y_max+j]=i-1;
            D2[i*y_max+j]=j-1;
        }
        else
        {
            std::cout<<"sth.wrong"<<endl;
        }
        D[i*y_max+j]+=dt;
        // printf("x[%d]=%.3f,y[%d]=%.3f,dst=%.3f",x[i-1],i-1,y[i-1],j-1,dt);
        
    }
    path.clear();
    // for (int i = 0; i < D.size(); i++)
    // {
    //     printf("(%d,%d),(%.5f,%d,%d),",int(i/y_max),i%y_max,D[i],D1[i],D2[i]);
    // }
    // std::cout<<endl;
    // std::cout<<D.size()<<endl;
    int i=x.size();
    int j=y.size();
    vector<int> rx,ry;
    int count=0;
    while (!(i==0 && j==0))//替代i==j==0,
    {
        path.push_back(pair_2(i-1,j-1));
        

        tmp=i*y_max+j;
    //    std::cout<<i << "/*ij/"<<j << std::endl;
        i=D1[tmp];
        j=D2[tmp];
        
        count+=1;
        
    }
    *distance=D[x.size()*y_max+y.size()];
    float dis=D[x.size()*y_max+y.size()];
    // cout<<"distance="<<dis<<endl;
    reverse(path.begin(),path.end());

    
}

void fastDtw::dtw(vector<float> x, vector<float> y,float *distance,vector<pair_2> &path,FunctionName dist )
{    vector<pair_2> windows;
    s__dtw(x,y,windows,distance,path,s__difference);
}

void fastDtw::s__fastDtw(vector<float> x, vector<float> y,float *distance,vector<pair_2> &path, FunctionName dist, int radius )
{
    double min_time_size = radius + 2;
    if (x.size()<min_time_size || y.size()<min_time_size)
    {
        dtw(x,y,distance,path,dist);
        return;
    }
    vector<float> x_shrinked;
    vector<float> y_shrinked;
    reduce_by_half(x,x_shrinked);
    reduce_by_half(y,y_shrinked);
    vector<pair_2> new_path;
    s__fastDtw(x_shrinked,y_shrinked,distance,new_path,s__difference,radius);
    // printf("xxx");
    // for(auto var : new_path)
    // {
    //     printf("(%d,%d),",var.x,var.y);
    // }
    // std::cout<<endl;
    // std::cout<<x.size()<<" "<<y.size()<<endl;


        // cout<<"--ooooxxxxxxooooo------"<<endl;
        // cout<<x.size()<<"sds"<<y.size()<<endl;
        // for(auto var : new_path)
        // {
        //     cout<<var.x<<"----"<<var.y<<",";
        // }
        // cout<<endl;
    
    
    expand_windows(new_path,x.size(),y.size(),radius);
    // std::cout<<"windows"<<endl;
    // for(auto var : x)
    // {
    //     std::cout<<var<<",";
    // }
    // std::cout<<endl;
    // for(auto var : y)
    // {
    //     std::cout<<var<<",";
    // }
    // std::cout<<endl;
    // std::cout<<"--ooooooooo------"<<endl;
    // std::cout<<x.size()<<"sds"<<y.size()<<endl;
    // for(auto var : new_path)
    // {
    //     std::cout<<var.x<<"----"<<var.y<<",";
    // }
    // std::cout<<endl;


    s__dtw(x,y,new_path,distance,path,dist);
    return;
}

void fastDtw::reduce_by_half(vector<float> x,vector<float> &x_result)
{
    for (int i = 0; i < x.size()-x.size()%2; i=i+2)
    {
        x_result.push_back((x[i]+x[1+i])/2); 
    }
    
}
void  fastDtw::expand_windows(vector<pair_2> &path,int len_x,int len_y,int radius)
{
    // cout<<path.size()<<endl;
    // for(auto var : path)
    // {
    //     cout<<var.x<<"--------"<<var.y<<endl;
    // }
    unordered_set <pair_2,pair_2_int_hash> path_;
    for(auto var : path)
    {
        path_.insert(var);
        int i=var.x;
        int j=var.y;
        for (int ai = -radius; ai < radius+1; ai++)
        {
            for (int bi = -radius; bi < radius+1; bi++)
            {
                // cout<<"sdsdasd"<<ai+i<<"sdsad "<<bi+j<<"i "<<i<<"j "<<j<<endl;
                path_.insert(pair_2 (ai+i,bi+j));
                // cout<<"len"<<path_.size()<<endl;
            }
            
        }        
    }

    // std::cout<<"--cccccccccccccc---"<<endl;

    // for(auto var : path_)
    // {
    //      printf("(%d,%d),",var.x,var.y);
    // }
    // std::cout<<endl;
    // std::cout<<path_.size()<<"xxxx"<<path.size()<<endl;
    

    unordered_set<pair_2,pair_2_int_hash> windows;
    for(auto var : path_)
    {
        int i=var.x;
        int j=var.y;
        // cout<<"px "<<var.x<<"py "<<var.y;      
        windows.insert(pair_2(i*2,j*2));
        windows.insert(pair_2(i*2,j*2+1));
        windows.insert(pair_2(i*2+1,j*2));
        windows.insert(pair_2(i*2+1,j*2+1));        
        // cout<<windows.size()<<endl;
    }
    // std::cout<<"--dddddddddddd---"<<endl;
    
    // for(auto var : windows)
    // {
    //      printf("(%d,%d),",var.x,var.y);
    // }
    // std::cout<<endl;
    // std::cout<<windows.size()<<endl;
    

    path.clear();

    int start_j=0;
    for (int i = 0; i < len_x; i++)
    {
        int new_start_j=MAX_INF;
        for (int j = start_j; j < len_y; j++)
        {          
            auto it =windows.find(pair_2(i,j));
            if (it!=windows.end())
            {
                path.push_back(pair_2(i,j));
                if(new_start_j==MAX_INF)
                {

                    new_start_j=j;
                }

            }
            else if (new_start_j!=MAX_INF)
            {
                break;
            }

        }
        start_j=new_start_j;
    }
    // std::cout<<"--fffffffff---"<<endl;
    
    // for(auto var : path)
    // {
    //      printf("(%d,%d),",var.x,var.y);
    // }
    // std::cout<<endl;
    // std::cout<<path.size()<<endl;    
    
    
}
