#pragma once
/*
需要指定是初始化还是跟踪状态，初始化状态要跟所有的一起开始
跟踪状态则直接指定某一个
*/


#include "common_include.h"
#include "nodeClass.hpp"
#include "math.h"
#include "fastDtw.hpp"
class magMatchBase {

public:
    vector<mag_data>  finger_mark;
    int _init_fm_interval=20;
    vector<float> sl_scale{0.9,1,1.1,1.2};
    nodeClass start_node;
    vector<float> observation_content;
    vector<pair2_xy> track_ob;
    float COS_thre=cos(M_PI/6.0);
    float DISTANCE_thre=3;
    float np_cos_theta=cos(15*M_PI/180);
    int adjust_len=20; //度调整的计算窗长度
    int pro_len_angle=30;
    int pro_fast_dtw_length=150;
    int pro_node_extend_len=55;
    vector<pair_2> _path;
    vector<int> output_result;
    magMatchBase();
    void magMatchBase_init(int init_node_index,float yaw,vector<vector<float>> nresult,int init_fm_interval=20);
    void magMatchBase_init(vector<int> init_node_indexs,vector<float> yaws,vector<vector<float>> nresult,int init_fm_interval=20);
    void magMatchBase_init(int start_index,int end_index,float yaw,vector<vector<float>> nresult,int init_fm_interval=20);
    bool init_add_item(int init_node_index,float yaw);
    float processData(float ob_distance,float epoch_angle,float magnetic_norm);
    vector<vector<int>> get_current_node_list();
    int get_current_node_index();
    int get_current_node_count();
    void print_min_seq();
    ~magMatchBase();
    float out_tmp_dis;
    vector<pair_3<float>> out_put_dis;

private:
    nodeClass* ts=nullptr;
    float ob_dis_x_y[2]={0,0};
    vector<nodeClass*> tmp_node_list;
    vector<nodeClass*> newtmpnode_list;
    vector<vector<int>> current_node_list_result;
    nodeClass* tmpnode=nullptr;
    void init_finger_mark(vector<vector<float>> nresult);
    // Eigen::MatrixXf tmp_mat_all_fp;
    float theta_o;
    float theta_o_all;
    float theta_2_all;
    float theta_2;
    float tmpyaw1;
    float tmpyaw2;
    float fp_distance;
    float distance_coefficient;
    float distance_coefficient_min;
    float fp_x;
    float fp_y;
    float included_angle;
    float included_angle_coefficient;
    float _min_rules_item=1e+9;
    float deta_x;
    float deta_y;
    float min_dis;
    float dis_dif;
    float dis_dif_less;
    nodeClass* min_dis_item;
    float min_dis_less;
    float _distance;
    vector<float> fp_mag;
    vector<float> fp_mag_20;
    vector<float> observation_content_20;
    int tmp_node_list_size;
    int observation_content_size;
    // Eigen::MatrixXf tmp_mat;
    // MatrixXf::Index index;
};