#include "magMatchBase.hpp"

magMatchBase::magMatchBase()
{
    start_node=nodeClass(-1);
    
}
//初始化的yaw角度主要指的是偏移量

void magMatchBase::magMatchBase_init(int init_node_index,float yaw,vector<vector<float>> nresult,int init_fm_interval)
{
    _init_fm_interval=init_fm_interval;
    init_finger_mark(nresult);
    init_add_item(init_node_index,yaw);
    track_ob.push_back(pair2_xy(0,0));
}
void magMatchBase::magMatchBase_init(vector<int> init_node_indexs,vector<float> yaws,vector<vector<float>> nresult,int init_fm_interval)
{
    vector<int> mkt_nodes;
    vector<float> mkt_nodes_dis;
    start_node=nodeClass(-1);
    start_node._print_seq_cut_length=2;
    _init_fm_interval=init_fm_interval;
    init_finger_mark(nresult);
    
    for (size_t i = 0; i < init_node_indexs.size(); i++)
    {
        init_add_item(init_node_indexs[i],yaws[i]);
        mkt_nodes.push_back(init_node_indexs[i]);
        mkt_nodes_dis.push_back(0);
    }
    track_ob.push_back(pair2_xy(0,0)); 
    metro_karlo_tree.push_back(mkt_nodes);
    metro_karlo_tree_dis.push_back(mkt_nodes_dis);
}
bool magMatchBase::magMatchBase_init(vector<vector<float>>nresult,int init_fm_interval)
{
    if (nresult.size()==0)
    {
        return false;
    }
    
    vector<int> mkt_nodes;
    vector<float> mkt_nodes_dis;
    start_node=nodeClass(-1);
    start_node._print_seq_cut_length=2;
    _init_fm_interval=init_fm_interval;
    init_finger_mark(nresult);
    
    for (size_t i = 0; i < nresult.size(); i++)
    {
        if (i%init_fm_interval==0)
        {
            init_add_item(i,0.0);
            mkt_nodes.push_back(i);
            mkt_nodes_dis.push_back(0);
        }
    }
    track_ob.push_back(pair2_xy(0,0)); 
    metro_karlo_tree.push_back(mkt_nodes);  
    metro_karlo_tree_dis.push_back(mkt_nodes_dis);
    return true;  
}
void magMatchBase::magMatchBase_init(int start_index,int end_index,float yaw,vector<vector<float>> nresult,int init_fm_interval)
{
    vector<int> mkt_nodes;
    vector<float> mkt_nodes_dis;
    start_node=nodeClass(-1);
    start_node._print_seq_cut_length=2;
    _init_fm_interval=init_fm_interval;
    init_finger_mark(nresult);
    
    for (size_t i = start_index; i < end_index; i++)
    {
        if (i%init_fm_interval==0)
        {
            init_add_item(i,yaw);
            mkt_nodes.push_back(i);
            mkt_nodes_dis.push_back(0);
        }
    }
    track_ob.push_back(pair2_xy(0,0)); 
    metro_karlo_tree.push_back(mkt_nodes);
    metro_karlo_tree_dis.push_back(mkt_nodes_dis);
}

bool magMatchBase::init_add_item(int init_node_index,float yaw)
{
    if (finger_mark.size()==0)
    {
        return false;
    }
    else
    {
        for(auto var : sl_scale)
        {
            ts=new nodeClass(init_node_index);
            ts->_yaw=yaw;
            ts->_scale=var;
            ts->ob_x=finger_mark[init_node_index].x;
            ts->ob_y=finger_mark[init_node_index].x;
            start_node.appendNode(ts);
            ts->node_start=init_node_index;
            tmp_node_list.push_back(ts);            
        }
       
    }
    start_index_list.insert(init_node_index);
    
}

void magMatchBase::init_finger_mark(vector<vector<float>> nresult)
{

    // tmp_mat_all_fp.resize(nresult.size(),2);
    int count=0;
    for(vector<float> var : nresult)
    {
        finger_mark.push_back(mag_data(var[0],var[1],var[6]));
        // tmp_mat_all_fp.row(count)<<var[0],var[1];
        count+=1;
    }
    // (tmp_mat_all_fp.rowwise()-tmp_mat_all_fp.row(2).rowwise().squaredNorm()>5).Coeff(&index);
    // tmp_mat=(tmp_mat_all_fp>5);
    // tmp_mat=tmp_mat_all_fp.row(index);
    // cout<<"tmp_mat"<<tmp_mat.rows()<<"X"<<tmp_mat.cols()<<endl;
}

    clock_t t1,t2 ;
    float speend_time;
float magMatchBase::processData(float ob_distance,float epoch_angle,float magnetic_norm)
{
    vector<int> mkt_nodes;
    vector<float> mkt_nodes_dis;
    //多的时候就先预置一个，然后找到最小的替换这个，最后append
    tmp_node_list_size=tmp_node_list.size();
    observation_content_size=observation_content.size();  
    if (ob_distance<=0)
    {
        cout<<"ob_distance必须大于0"<<endl;
        return -1;
    }
    t1 = clock();    
    if (observation_content.size()>20)
    {
        DISTANCE_thre=3;
    }
    if (observation_content.size()>100)
    {
        DISTANCE_thre=1.5;
    }    
    if (observation_content.size()>50 || tmp_node_list.size()>pro_node_extend_len)
    {
        COS_thre=cos(M_PI/4.0);
    }
    if (tmp_node_list.size()>200)
    {
        COS_thre=cos(M_PI/3.0);
    }
    if (tmp_node_list_size<20)
    {
        // COS_thre=cos(M_PI/2.5);
        // distance_coefficient_min_thre=0.2;
    }
    
    ob_dis_x_y[0]=sin(epoch_angle);
    ob_dis_x_y[1]=cos(epoch_angle);
    observation_content.push_back(magnetic_norm);
    track_ob.push_back(pair2_xy(track_ob.back().x+ob_dis_x_y[0]*ob_distance,track_ob.back().y+ob_dis_x_y[1]*ob_distance));

    newtmpnode_list.clear();

    if (track_ob.size()>adjust_len+1)
    {
        theta_o=atan2((track_ob.back().x-track_ob.at(track_ob.size()-adjust_len-1).x),(track_ob.back().y-track_ob.at(track_ob.size()-adjust_len-1).y));
        theta_o_all=atan2((track_ob.back().x-track_ob.at(0).x),(track_ob.back().y-track_ob.at(0).y));
    }
    t2 = clock();
    speend_time = (float)(t2 - t1) / CLOCKS_PER_SEC;
    printf("初始化　time speend %.3f\r\n'" , speend_time);
 
    ob_distance+=last_length;
    for(nodeClass* leaf_node : tmp_node_list)
    {
        // cout<<"yaw="<<leaf_node->_yaw<<"scale="<<leaf_node->_scale<<" ";
        if (observation_content.size()>8)
        {
            /* code */
            ob_dis_x_y[0]=sin(epoch_angle+leaf_node->_yaw);
            ob_dis_x_y[1]=cos(epoch_angle+leaf_node->_yaw);        
        }

        if(tmp_node_list_size>pro_node_extend_len || observation_content_size<20){
            tmpnode=new nodeClass(-1);
        }
        
        distance_coefficient_min=1e+9;
        included_angle_max=COS_thre;
        for(int fp_index=0;fp_index<finger_mark.size();fp_index++)
        {
            
            if (abs(finger_mark[fp_index].x-finger_mark[leaf_node->node_index].x)<ob_distance*2)
            {
                if (abs(finger_mark[fp_index].y-finger_mark[leaf_node->node_index].y)<ob_distance*2)
                {
                    fp_x=finger_mark[fp_index].x-finger_mark[leaf_node->node_index].x;
                    fp_y=finger_mark[fp_index].y-finger_mark[leaf_node->node_index].y;
                    fp_distance=sqrtf(fp_x*fp_x+fp_y*fp_y);
                    if(fp_distance<1e-8)
                    {
                        continue;
                    }
                    included_angle=(ob_dis_x_y[0]*fp_x+fp_y*ob_dis_x_y[1])/fp_distance;
                    deta_x=leaf_node->ob_x+fp_x;
                    deta_y=leaf_node->ob_y+fp_y;
                     distance_coefficient=abs(ob_distance*leaf_node->_scale-fp_distance)/(ob_distance*leaf_node->_scale);
                    if (distance_coefficient<0.5 && included_angle>included_angle_max)
                    {
                       
                        if(tmp_node_list_size>pro_node_extend_len || observation_content_size<20){
                            tmpnode->node_index=fp_index;
                            tmpnode->_yaw=leaf_node->_yaw;
                            tmpnode->_scale=leaf_node->_scale;
                            // tmpnode->_scale=1.0/included_angle;
                            tmpnode->ob_x=deta_x;
                            tmpnode->ob_y=deta_y;                            
                            included_angle_max=included_angle;
                            
                        }
                        else
                        {
                            if (distance_coefficient<0.5){
                            tmpnode=new nodeClass(fp_index);
                            tmpnode->_yaw=leaf_node->_yaw;
                            tmpnode->_scale=leaf_node->_scale;
                            // tmpnode->_scale=1.0/included_angle;
                            tmpnode->ob_x=deta_x;
                            tmpnode->ob_y=deta_y;                            
                            leaf_node->appendNode(tmpnode);
                            newtmpnode_list.push_back(tmpnode);  
                            }   
                                                  
                        }  
                    }
                }
            }            
        }
        //单次的时候前面预置了，这个根据查询情况，看是否存入
        if(tmp_node_list_size>pro_node_extend_len || observation_content_size<20){
            if (included_angle_max>COS_thre)//单次且有
            {
                leaf_node->appendNode(tmpnode);
                newtmpnode_list.push_back(tmpnode);
            }
        }      

        
    }
    printf("newtmpnode_list=%ld\r\n" , newtmpnode_list.size());
    t2 = clock();
    speend_time = (float)(t2 - t1) / CLOCKS_PER_SEC;
    printf("节点生成　time speend %.3f\r\n'" , speend_time);
    min_dis = 1e+9;
    min_dis_less=1e+9; 
    if (newtmpnode_list.size()==0)
    {
        /* code */
        last_length+=ob_distance;
    }
    else{
        last_length=0;
        tmp_node_list.clear();
    }  
    
    // int count_size_300=0;
    if (observation_content.size()>8)
    {
        dtw_dis.clear();
        for(nodeClass* var : newtmpnode_list)
        {
            // if (newtmpnode_list.size()>900)
            // {
            //     if(count_size_300%(int(newtmpnode_list.size()/300))!=0)
            //     {
            //         continue;
            //     }
            // }
            // count_size_300++;
            fp_mag.clear();
            _path.clear();
            for(int seq_index : var->containSeq)
            {
                fp_mag.push_back(finger_mark[seq_index].mmagn);
            }
            if (observation_content.size()>pro_fast_dtw_length+1)
            {
                fp_mag_20.clear();
                observation_content_20.clear();
                fp_mag_20.assign(fp_mag.end()-pro_fast_dtw_length,fp_mag.end());
                observation_content_20.assign(observation_content.end()-pro_fast_dtw_length,observation_content.end());
                fastDtw::fastdtw(observation_content_20,fp_mag_20,&_distance,_path);
            }
            else
            {
                fastDtw::fastdtw(observation_content,fp_mag,&_distance,_path);               
            }
            
            


            var->node_probability=_distance;
            if (_distance<min_dis)
            {
                min_dis=_distance;
                min_dis_item=var;
            }
            // cout<<_distance<<"--";
            dtw_dis.push_back(_distance);
            if(observation_content.size()>pro_len_angle+1)
            {
                fp_mag_20.clear();
                observation_content_20.clear();
                fp_mag_20.assign(fp_mag.end()-pro_len_angle,fp_mag.end());
                observation_content_20.assign(observation_content.end()-pro_len_angle,observation_content.end());
                fastDtw::fastdtw(observation_content_20,fp_mag_20,&_distance,_path);
                var->node_less_prob=_distance;
                if (_distance<min_dis_less)
                {
                    min_dis_less=_distance;
                }
                
            }
        }
        if (dtw_dis.size()>0)
        {
            max_dis=*max_element(dtw_dis.begin(),dtw_dis.end());
            DTWDIS_THRE=(max_dis-min_dis)/min_dis;
            if (DTWDIS_THRE<0.01)
            {
                newtmpnode_list.clear();
                tmp_node_list.push_back(min_dis_item);
            }
            else if (DTWDIS_THRE<0.5 or newtmpnode_list.size()>8*pro_node_extend_len)
            {
                DTWDIS_THRE=(max_dis-min_dis)/4.0+min_dis;
            }
            else
            {
                DTWDIS_THRE=(max_dis+min_dis)/2.0;
            }
            
            printf("dismax=%.3f,dismin=%.3f,thre=%.3f",max_dis,min_dis,DTWDIS_THRE);
            if(newtmpnode_list.size()<4*pro_node_extend_len)
            {
                DTWDIS_THRE=1e+9;
            }
        }
        else//newnode里面没东西的时候就吧上次的弄过来
        {
            tmp_node_list.push_back(min_dis_item);
        }
        
        t2 = clock();
        speend_time = (float)(t2 - t1) / CLOCKS_PER_SEC;
        printf("newtmpnode_list:::=%ld\r\n" , newtmpnode_list.size());
        printf("匹配距离计算time speend %.3f\r\n'" , speend_time);
        // count_size_300=0;
        for(auto item : newtmpnode_list)
        {
            // if (newtmpnode_list.size()>900)
            // {
            //     if(count_size_300%(int(newtmpnode_list.size()/300))!=0)
            //     {
            //         continue;
            //     }
            // }
            // count_size_300++;

            dis_dif = item->node_probability-min_dis;
            if( (dis_dif/min_dis <= DISTANCE_thre && item->node_probability<=DTWDIS_THRE) || _define_random_rand()<0.5 )
            {
                if (observation_content.size()>pro_len_angle+1){
                    dis_dif_less=item->node_less_prob-min_dis_less;
                    if (dis_dif_less/min_dis_less <= DISTANCE_thre){//子串也符合要求  
                        if( observation_content.size()>adjust_len+1)
                        {
                            theta_2_all=atan2((finger_mark[item->node_index].x-finger_mark[item->node_start].x),(finger_mark[item->node_index].y-finger_mark[item->node_start].y));
                            // int tst=item->containSeq.at(item->containSeq.size()-adjust_len-1);
                            theta_2=atan2((finger_mark[item->node_index].x-finger_mark[item->containSeq.at(item->containSeq.size()-adjust_len-1)].x),(finger_mark[item->node_index].y-finger_mark[item->containSeq.at(item->containSeq.size()-adjust_len-1)].y));
                            tmpyaw1=theta_2-theta_o;
                            tmpyaw2=theta_o_all-theta_2_all;

                            // 从全程和局部上，选择变化大的那个
                            if (cos(tmpyaw1-item->father->_yaw)<cos(tmpyaw2-item->father->_yaw))
                            {
                                item->_yaw=tmpyaw1;
                            }                            
                            else{
                                item->_yaw=tmpyaw2;
                            }
                            // item->_yaw=tmpyaw1;
                            if (cos(item->_yaw-item->father->_yaw)<np_cos_theta)
                            {
                                item->_yaw=item->father->_yaw;
                            }
                            
                        }
                        else
                        {
                            item->_yaw=item->father->_yaw;
                        }
                        

                        tmp_node_list.push_back(item);
                    }
                }
                else
                {
                    // item->_yaw=item->father->_yaw;
                    tmp_node_list.push_back(item);
                }                                       
            }
        }
        printf("tsssss:node_count=%ld\r\n" , tmp_node_list.size());
        t2 = clock();
        speend_time = (float)(t2 - t1) / CLOCKS_PER_SEC;
        printf("抽取结果，并计算方向time speend %.3f\r\n'" , speend_time);
        printf("min dis %.3f\r\n,scale=%.3f,yaw=%.3f", min_dis,min_dis_item->_scale,min_dis_item->_yaw);
        // # print(min_dis_item.node_index)
        // # print(min_dis_item.node_start)
        // output_result.push_back(min_dis_item->node_index);
        out_tmp_dis = min_dis;
    }
    else
    {
        tmp_node_list = vector<nodeClass*>(newtmpnode_list) ;//据说是深复制
        out_tmp_dis = -1;
    }

    if (tmp_node_list.size()<20)//&&tmp_node_list.size()>0)
    {
        /* code */
        int len_tmp_node_list=tmp_node_list.size();
        for (int tmp_leaf_node_index = 0; tmp_leaf_node_index < len_tmp_node_list; tmp_leaf_node_index++)
        {
            /* code */
            for (int _ = 0; _ < 4; _++)
            {
                tmpnode = new nodeClass(tmp_node_list[tmp_leaf_node_index]->node_index);
                tmpnode->node_index = tmp_node_list[tmp_leaf_node_index]->node_index+int((_define_random_rand()-0.5)*10);
                if (tmpnode->node_index>=finger_mark.size() || tmpnode->node_index<0)
                {
                    continue;
                }
                tmpnode->_scale = tmp_node_list[tmp_leaf_node_index]->_scale * (_define_random_rand()+0.5);
                tmpnode->_yaw=tmp_node_list[tmp_leaf_node_index]->_yaw+(_define_random_rand()*2-1)*sample_step_yaw;
                tmpnode->ob_x=tmp_node_list[tmp_leaf_node_index]->ob_x;
                tmpnode->ob_y=tmp_node_list[tmp_leaf_node_index]->ob_y;
                tmpnode->Ignore_this_point=true;
                if (tmpnode->_scale > 1.3){
                    tmpnode->_scale = 1.3;
                }
                if (tmpnode->_scale < 1){//由于选择的线是原来的旋转，所以肯定是变长了
                    tmpnode->_scale = 1;
                    }
                tmp_node_list[tmp_leaf_node_index]->appendNode(tmpnode);
                tmp_node_list.push_back(tmpnode);
            }
            
        }
    // }
    // if (newtmpnode_list.size()==0 && tmp_node_list.size()==1)
    // {
    //     int len_tmp_node_list=tmp_node_list.size();
    //     for (int tmp_leaf_node_index = 0; tmp_leaf_node_index < len_tmp_node_list; tmp_leaf_node_index++)
    //     {
    //         /* code */
    //         for (int _ = 0; _ < 50; _++)
    //         {
    //             tmpnode = new nodeClass(tmp_node_list[tmp_leaf_node_index]->node_index);
    //             tmpnode->node_index = tmp_node_list[tmp_leaf_node_index]->node_index+int((_define_random_rand()-0.5)*20);
    //             if (tmpnode->node_index>=finger_mark.size() || tmpnode->node_index<0)
    //             {
    //                 continue;
    //             }
    //             tmpnode->_scale = tmp_node_list[tmp_leaf_node_index]->_scale * (_define_random_rand()+0.5)*2;
    //             tmpnode->_yaw=tmp_node_list[tmp_leaf_node_index]->_yaw+(_define_random_rand()*2-1)*sample_step_yaw*2;
    //             tmpnode->ob_x=tmp_node_list[tmp_leaf_node_index]->ob_x;
    //             tmpnode->ob_y=tmp_node_list[tmp_leaf_node_index]->ob_y;
    //             tmpnode->Ignore_this_point=true;
    //             if (tmpnode->_scale > 1.3){
    //                 tmpnode->_scale = 1.3;
    //             }
    //             if (tmpnode->_scale < 0.8){//由于选择的线是原来的旋转，所以肯定是变长了
    //                 tmpnode->_scale = 0.8;
    //                 }
    //             tmp_node_list[tmp_leaf_node_index]->appendNode(tmpnode);
    //             tmp_node_list.push_back(tmpnode);
    //         }
            
    //     }
    //     out_tmp_dis=-10;
  
    }
    if (tmp_node_list.size()==0)
    {
        int len_newtmpnode_list=newtmpnode_list.size();
        for (int tmp_leaf_node_index = 0; tmp_leaf_node_index < len_newtmpnode_list; tmp_leaf_node_index++)
        {
            /* code */
            for (int _ = 0; _ < 5; _++)
            {
                tmpnode = new nodeClass(newtmpnode_list[tmp_leaf_node_index]->node_index);
                tmpnode->node_index = newtmpnode_list[tmp_leaf_node_index]->node_index+int((_define_random_rand()-0.5)*20);
                if (tmpnode->node_index>=finger_mark.size() || tmpnode->node_index<0)
                {
                    continue;
                }                
                tmpnode->_scale = newtmpnode_list[tmp_leaf_node_index]->_scale * (_define_random_rand()+0.5)*2;
                tmpnode->_yaw=newtmpnode_list[tmp_leaf_node_index]->_yaw+(_define_random_rand()*2-1)*sample_step_yaw*2;
                tmpnode->ob_x=newtmpnode_list[tmp_leaf_node_index]->ob_x;
                tmpnode->ob_y=newtmpnode_list[tmp_leaf_node_index]->ob_y;
                if (tmpnode->_scale > 1.5){
                    tmpnode->_scale = 1.5;
                }
                if (tmpnode->_scale < 0.8){//由于选择的线是原来的旋转，所以肯定是变长了
                    tmpnode->_scale = 0.8;
                    }
                newtmpnode_list[tmp_leaf_node_index]->appendNode(tmpnode);
                tmp_node_list.push_back(tmpnode);               
            }
        }
        out_tmp_dis=-10;
  
    }


    
    
    printf("'node_count=%ld\r\n" , tmp_node_list.size());
    t2 = clock();
    speend_time = (float)(t2 - t1) / CLOCKS_PER_SEC;
    printf("'time speend %.3f\r\n'" , speend_time);
    out_put_dis.push_back(pair_3<float>(newtmpnode_list.size(), out_tmp_dis, speend_time));
        printf("--------------------------%ld---------------now the start is %d\r\n",start_index_list.size(),*start_index_list.begin());
    if (start_index_list.size()==1)
    {
        printf("-----------------------------------------now the start is %d\r\n",*start_index_list.begin());
        isInitFinish=true;
    }
    else
    {
        start_index_list.clear();
        for(auto item : tmp_node_list)
        {
            start_index_list.insert(item->node_start);
        }       
        for(auto var : start_index_list)
        {
            cout<<var<<",";
        } 
    }    
    for(auto item : tmp_node_list)
    {
        mkt_nodes.push_back(item->node_index);
        mkt_nodes_dis.push_back(item->node_probability);
    }
    if( min_dis_item!=nullptr){
        mkt_nodes.push_back(min_dis_item->node_index);
        mkt_nodes_dis.push_back(min_dis);
    }
    
    metro_karlo_tree.push_back(mkt_nodes);
    metro_karlo_tree_dis.push_back(mkt_nodes_dis);
    return out_tmp_dis;
}

vector<vector<int>> magMatchBase::get_current_node_list()
{
    current_node_list_result.clear();
    current_node_list_info.clear();
    for(auto var : tmp_node_list)
    {
        cout<<"now the node_index is "<<var->node_index<<"dis="<<var->node_probability<<endl;
        current_node_list_info.push_back(var->node_probability);
        current_node_list_result.push_back(var->containSeq);
        for(auto item : var->containSeq)
        {
            cout<<item<<",";
        }
        cout<<endl;
    }
    return current_node_list_result;
}
void magMatchBase::print_min_seq_yaw()
{
    printf("now the node_index is %d,dis=%.3f,scale=%.3f,yaw=%.3f\r\n",min_dis_item->node_index,min_dis_item->node_probability,min_dis_item->_scale,min_dis_item->_yaw);
    // cout<<" "<<min_dis_item->node_index<<"dis="<<min_dis_item->node_probability<<endl;
    cout<<endl;
    for(auto var : min_dis_item->constainInfo)
    {
        cout<<var[0]<<","<<var[0]<<","<<var[2]<<","<<var[3]<<","<<endl;
    }
    cout<<endl;
}
void magMatchBase::print_min_seq()
{
    printf("now the node_index is %d,dis=%.3f,scale=%.3f,yaw=%.3f\r\n",min_dis_item->node_index,min_dis_item->node_probability,min_dis_item->_scale,min_dis_item->_yaw);
    // cout<<" "<<min_dis_item->node_index<<"dis="<<min_dis_item->node_probability<<endl;
    for(auto var : min_dis_item->containSeq)
    {
        cout<<var<<",";
    }
    cout<<endl;
}

void magMatchBase::get_current_node_info2(string filename)
{
    dataRead::s_dataWrite(filename,min_dis_item->constainInfo);
}

void magMatchBase::print_metro_karlo_tree(string filename)
{
    dataRead::s_dataWrite(filename,metro_karlo_tree);
}
void magMatchBase::print_metro_karlo_tree_distance(string filename)
{
    dataRead::s_dataWrite(filename,metro_karlo_tree_dis);
}

vector<float> magMatchBase::get_current_result()
{
    vector<float> result;
    if (min_dis_item==nullptr)
    {
        return result;
    }
    
    
    if (isInitFinish)//初始化状态
    {
        result.push_back(1);
    }
    else
    {
        result.push_back(0);
    }
    result.push_back(min_dis_item->node_probability);
    result.push_back(finger_mark[min_dis_item->node_index].x);
    result.push_back(finger_mark[min_dis_item->node_index].y);
    return result;
}

magMatchBase::~magMatchBase() {
    // if(tmpnode!=nullptr)
    // {
    //     delete tmpnode;
    //     tmpnode=nullptr;
    // }
}