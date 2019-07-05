//
//Created by tianxiaochun on 2019/07/05.
//
#include "mktMM.h"
#include "magMatchBase.hpp"

// #define LISTENER_PDR_FIELD_ID               ("pdrStepCallback")
// #define LISTENER_PDR_JAVA_PATH              ("Lcom/xihe/newpdrsdk/locator/PdrStepCallbackInterface;")

// #define CB_PDR_DATA_NAME                    ("OnPdrStepEvent")
// #define CB_PDR_DATA_DESC                    ("(DDDDD)V")

// #define LISTENER_PRESSURE_FIELD_ID          ("pressureCallback")
// #define LISTENER_PRESSURE_JAVA_PATH         ("Lcom/xihe/newpdrsdk/locator/PressureCallbackInterface;")

// #define CB_PRESSURE_DATA_NAME               ("OnFloorChangeEvent")
// #define CB_PRESSURE_DATA_DESC               ("(IIDDI)V")


// class JniPdrStepLib {

// public:
//     jobject lib_java;
//     jobject listener_java;
//     jmethodID OnEvent;
//     JNIEnv *env;
// };

// JavaVM *vm = NULL;

// JniPdrStepLib *pdr_lib = NULL;

// JniPdrStepLib *floor_lib = NULL;
//流程

magMatchBase *mmb = NULL;
mmb=new magMatchBase();
vector<vector<float>> fp;
bool rs=mmb->magMatchBase_init(fp);

float dis_result= mmb->processData( SL, YAW, MagneticNorm);
if(abs(dis_result+1)<1e-5)
{
    "no result"
}
else
{
    vector<float>rs= mmb->get_current_result();
    // 初始化状态，概率，x,y
}

delete mmb;