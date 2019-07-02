#include "magMatchBase.hpp"

magMatchBase::magMatchBase()
{
    start_node=nodeClass(-1);
    
}


void magMatchBase::magMatchBase_init(int init_node_index,float yaw,vector<vector<float>> nresult,int init_fm_interval)
{
    _init_fm_interval=init_fm_interval;
    init_finger_mark(nresult);
    init_add_item(init_node_index,yaw);
    track_ob.push_back(pair2_xy(0,0));
}
void magMatchBase::magMatchBase_init(vector<int> init_node_indexs,vector<float> yaws,vector<vector<float>> nresult,int init_fm_interval)
{
    start_node=nodeClass(-1);
    start_node._print_seq_cut_length=2;
    _init_fm_interval=init_fm_interval;
    init_finger_mark(nresult);
    
    for (size_t i = 0; i < init_node_indexs.size(); i++)
    {
        init_add_item(init_node_indexs[i],yaws[i]);
    }
    track_ob.push_back(pair2_xy(0,0)); 
}
void magMatchBase::magMatchBase_init(int start_index,int end_index,float yaw,vector<vector<float>> nresult,int init_fm_interval)
{
    start_node=nodeClass(-1);
    start_node._print_seq_cut_length=2;
    _init_fm_interval=init_fm_interval;
    init_finger_mark(nresult);
    
    for (size_t i = start_index; i < end_index; i++)
    {
        if (i%init_fm_interval==0)
        {
            init_add_item(i,yaw);
        }
    }
    track_ob.push_back(pair2_xy(0,0)); 
}

bool magMatchBase::init_add_item(int init_node_index,float yaw)
{
    if (finger_mark.size()==0)
    {
        return false;
    }
    else
    {
        ts=new nodeClass(init_node_index);
        ts->_yaw=yaw;
        ts->ob_x=finger_mark[init_node_index].x;
        ts->ob_y=finger_mark[init_node_index].x;
        start_node.appendNode(ts);
        tmp_node_list.push_back(ts);        
    }
    
    
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
    if (ob_distance<=0)
    {
        cout<<"ob_distance必须大于0"<<endl;
        return -1;
    }
    t1 = clock();    
    if (observation_content.size()>20)
    {
        DISTANCE_thre=1;
    }
    if (observation_content.size()>80)
    {
        DISTANCE_thre=0.5;
    }    
    if (observation_content.size()>50 || tmp_node_list.size()>pro_node_extend_len)
    {
        COS_thre=cos(M_PI/3.0);
    }
    if (tmp_node_list.size()>300)
    {
        COS_thre=cos(M_PI/3.0);
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
    for(nodeClass* leaf_node : tmp_node_list)
    {
        if (observation_content.size()>8)
        {
            /* code */
            ob_dis_x_y[0]=sin(epoch_angle+leaf_node->_yaw);
            ob_dis_x_y[1]=cos(epoch_angle+leaf_node->_yaw);        
        }
        //多的时候就先预置一个，然后找到最小的替换这个，最后append
        tmp_node_list_size=tmp_node_list.size();
        observation_content_size=observation_content.size();
        if(tmp_node_list_size>pro_node_extend_len || observation_content_size<20){
            tmpnode=new nodeClass(-1);
        }
        
        distance_coefficient_min=1e+9;
        for(int fp_index=0;fp_index<finger_mark.size();fp_index++)
        {
            
            if (abs(finger_mark[fp_index].x-finger_mark[leaf_node->node_index].x)<ob_distance*2)
            {
                if (abs(finger_mark[fp_index].y-finger_mark[leaf_node->node_index].y)<ob_distance*2)
                {
                    fp_x=finger_mark[fp_index].x-finger_mark[leaf_node->node_index].x;
                    fp_y=finger_mark[fp_index].y-finger_mark[leaf_node->node_index].y;
                    fp_distance=sqrtf(fp_x*fp_x+fp_y*fp_y);
                    included_angle=(ob_dis_x_y[0]*fp_x+fp_y*ob_dis_x_y[1])/(ob_distance*fp_distance);
                    deta_x=leaf_node->ob_x+fp_x;
                    deta_y=leaf_node->ob_y+fp_y;
                    if (included_angle>COS_thre)
                    {
                        distance_coefficient=abs(ob_distance*leaf_node->_scale-fp_distance)/(ob_distance*leaf_node->_scale)-1;
                        if(tmp_node_list_size>pro_node_extend_len || observation_content_size<20){
                            if (distance_coefficient<0.1 && distance_coefficient<distance_coefficient_min)
                            {
                                tmpnode->node_index=fp_index;
                                tmpnode->_yaw=leaf_node->_yaw;
                                tmpnode->_scale=leaf_node->_scale;
                                tmpnode->ob_x=deta_x;
                                tmpnode->ob_y=deta_y;                            
                                distance_coefficient_min=distance_coefficient;
                            }
                        }
                        else
                        {
                            if (abs(distance_coefficient)<0.05)
                            {
                                tmpnode=new nodeClass(fp_index);
                                tmpnode->_yaw=leaf_node->_yaw;
                                tmpnode->_scale=leaf_node->_scale;
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
            if (distance_coefficient_min<1e+9)//单次且有
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
    tmp_node_list.clear();
    if (observation_content.size()>8)
    {
        for(nodeClass* var : newtmpnode_list)
        {
            fp_mag.clear();
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
    t2 = clock();
    speend_time = (float)(t2 - t1) / CLOCKS_PER_SEC;
    printf("匹配距离计算time speend %.3f\r\n'" , speend_time);
        for(auto item : newtmpnode_list)
        {
            dis_dif = item->node_probability-min_dis;
            if( (dis_dif/min_dis <= DISTANCE_thre ) || _define_random_rand()< 0.01)
            {
                if (observation_content.size()>pro_len_angle){
                    dis_dif_less=item->node_less_prob-min_dis_less;
                    if (dis_dif_less/min_dis_less <= DISTANCE_thre){//子串也符合要求  
                        if( observation_content.size()>adjust_len+1)
                        {
                            theta_2_all=atan2((finger_mark[item->node_index].x-finger_mark[item->node_start].x),(finger_mark[item->node_index].y-finger_mark[item->node_start].y));
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
                        }
                        else
                        {
                            item->_yaw=item->_yaw;
                        }
                        

                        tmp_node_list.push_back(item);
                    }
                }
                else{
                    item->_yaw=item->_yaw;
                    tmp_node_list.push_back(item);
                }                                       
            }
        }
    t2 = clock();
    speend_time = (float)(t2 - t1) / CLOCKS_PER_SEC;
    printf("抽取结果，并计算方向time speend %.3f\r\n'" , speend_time);
        printf("min dis %.3f\r\n", min_dis);
        // # print(min_dis_item.node_index)
        // # print(min_dis_item.node_start)
        output_result.push_back(min_dis_item->node_index);
        out_tmp_dis = min_dis;
    }
    else
    {
        tmp_node_list = vector<nodeClass*>(newtmpnode_list) ;//据说是深复制
        out_tmp_dis = -1;
    }

    if (tmp_node_list.size()<50)
    {
        /* code */
        int len_tmp_node_list=tmp_node_list.size();
        for (int tmp_leaf_node_index = 0; tmp_leaf_node_index < len_tmp_node_list; tmp_leaf_node_index++)
        {
            /* code */
            for (int _ = 0; _ < 2; _++)
            {
                tmpnode = new nodeClass(tmp_node_list[tmp_leaf_node_index]->node_index);
                tmpnode->node_index = tmp_node_list[tmp_leaf_node_index]->node_index+int((_define_random_rand()-0.5)*10);
                if (tmpnode->node_index>=finger_mark.size() || tmpnode->node_index<0)
                {
                    continue;
                }
                tmpnode->_scale = tmp_node_list[tmp_leaf_node_index]->_scale * (_define_random_rand()+0.5);
                tmpnode->_yaw=tmp_node_list[tmp_leaf_node_index]->_yaw*(_define_random_rand()*2-1)*0.1;
                tmpnode->ob_x=tmp_node_list[tmp_leaf_node_index]->ob_x;
                tmpnode->ob_y=tmp_node_list[tmp_leaf_node_index]->ob_y;
                if (tmpnode->_scale > 1.5){
                    tmpnode->_scale = 1.5;
                }
                if (tmpnode->_scale < 1){//由于选择的线是原来的旋转，所以肯定是变长了
                    tmpnode->_scale = 1;
                    }
                tmp_node_list[tmp_leaf_node_index]->appendNode(tmpnode);
                tmp_node_list.push_back(tmpnode);
            }
            
        }
    }
    if (tmp_node_list.size()==0)
    {
        int len_newtmpnode_list=newtmpnode_list.size();
        for (int tmp_leaf_node_index = 0; tmp_leaf_node_index < len_newtmpnode_list; tmp_leaf_node_index++)
        {
            /* code */
            for (int _ = 0; _ < 4; _++)
            {
                tmpnode = new nodeClass(newtmpnode_list[tmp_leaf_node_index]->node_index);
                tmpnode->node_index = newtmpnode_list[tmp_leaf_node_index]->node_index+int((_define_random_rand()-0.5)*20);
                if (tmpnode->node_index>=finger_mark.size() || tmpnode->node_index<0)
                {
                    continue;
                }                
                tmpnode->_scale = newtmpnode_list[tmp_leaf_node_index]->_scale * (_define_random_rand()+0.5)*2;
                tmpnode->_yaw=newtmpnode_list[tmp_leaf_node_index]->_yaw*(_define_random_rand()*2-1)*0.5;
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
  
    }
    printf("'node_count=%ld\r\n" , tmp_node_list.size());
    t2 = clock();
    speend_time = (float)(t2 - t1) / CLOCKS_PER_SEC;
    printf("'time speend %.3f\r\n'" , speend_time);
    out_put_dis.push_back(pair_3<float>(newtmpnode_list.size(), out_tmp_dis, speend_time));
    return out_tmp_dis;
}

vector<vector<int>> magMatchBase::get_current_node_list()
{
    current_node_list_result.clear();
    for(auto var : tmp_node_list)
    {
        cout<<"now the node_index is "<<var->node_index<<"dis="<<var->node_probability<<endl;
        current_node_list_result.push_back(var->containSeq);
        for(auto item : var->containSeq)
        {
            cout<<item<<",";
        }
        cout<<endl;
    }
    return current_node_list_result;
}
void magMatchBase::print_min_seq()
{
    printf("now the node_index is %d,dis=%.3f,scale+%.3f,yaw=%.3f\r\n",min_dis_item->node_index,min_dis_item->node_probability,min_dis_item->_scale,min_dis_item->_yaw);
    // cout<<" "<<min_dis_item->node_index<<"dis="<<min_dis_item->node_probability<<endl;
    for(auto var : min_dis_item->containSeq)
    {
        cout<<var<<",";
    }
    cout<<endl;
}

magMatchBase::~magMatchBase() {
    // if(tmpnode!=nullptr)
    // {
    //     delete tmpnode;
    //     tmpnode=nullptr;
    // }
}