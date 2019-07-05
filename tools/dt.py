import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from fastdtw import fastdtw
from matplotlib.collections import LineCollection
# data1=pd.read_csv('./data/1.csv',header=None)
# data1.columns=['x','y','sl','yaw','detayaw','mx','my','mz','si','stime','mmagn']
# # data1.columns=['x','y','sl','yaw','detayaw','mx','my','mz','si','stime']
# # data1['mmagn']=np.sqrt(data1['mx']**2+data1['my']**2+data1['mz']**2)

data1=pd.read_csv('/home/aaron/project/MapMatching/data/allSecD.csv')
# data1.columns=['x','y','sl','yaw','detayaw','mx','my','mz','si','stime','mmagn']
# data1.columns=['x','y','sl','yaw','detayaw','mx','my','mz','si','stime']
# data1['mmagn']=np.sqrt(data1['mx']**2+data1['my']**2+data1['mz']**2)
dataA=pd.read_csv('/media/aaron/新加卷/工作记录/项目产出及记录/19年羲和后台过程归档/第二阶段材料整理/测试过程/iosFp/my_iOS_device_2019-06-26_16-48-43_+0800data.csv',header=None)
dataA.columns=['x','y','sl','yaw','detayaw','mx','my','mz','si','stime']
dataA['mmagn']=np.sqrt(dataA['mx']**2+dataA['my']**2+dataA['mz']**2)
mkt=[]
lastlin=[]
with open("/home/aaron/project/MagMatch/data/mkt.txt",'r') as target:
    for line in target.readlines():
        tmp=[]
        for data in line[:-1].split(","):
            tmp.append(int(data))
        lastlin.append(tmp[-1])
        mkt.append(tmp)
# print(data1.loc[lastlin[5:20],['x','y']])
with open("/home/aaron/project/MagMatch/data/log.txt",'r') as target:
    lines=target.readlines()
    lastline=lines[-1]
    yaw=lines[-3]

output_result=[]

for item in lastline[:-2].split(','):
    output_result.append(int(item))
print(len(output_result))
start_index = 0
end_index = 336
ts2=range(end_index)
result_p=np.array(output_result)
# deta=dataA.loc[start_index-1, 'mmagn']-data1.loc[200:250,'mmagn'].mean()
# dataA['mmagn']-=deta

# data1=pd.read_csv('./data/4.csv',header=None)
# # data1.columns=['x','y','sl','yaw','detayaw','mx','my','mz','si','stime','mmagn']
# data1.columns=['x','y','sl','yaw','detayaw','mx','my','mz','si','stime']
# data1['mmagn']=np.sqrt(data1['mx']**2+data1['my']**2+data1['mz']**2)
# # dataA=pd.read_csv('/media/aaron/新加卷1/工作记录/项目产出及记录/19年羲和后台过程归档/第二阶段材料整理/数据/对比数据/0100701.csv',header=None)
# dataA=pd.read_csv('./data/1.csv',header=None)
# dataA.columns=['x','y','sl','yaw','detayaw','mx','my','mz','si','stime','mmagn']
# dataA['mmagn']=np.sqrt(dataA['mx']**2+dataA['my']**2+dataA['mz']**2)


# result_p=np.loadtxt('./data/airesult.csv',delimiter=',')
# output_result=np.loadtxt('./data/airesult.csv',delimiter=',')
info_result=np.loadtxt('/home/aaron/project/MagMatch/data/info.csv',delimiter=',',dtype='float')
out_put_dis=np.loadtxt('/home/aaron/project/MagMatch/data/data.csv',delimiter=',')
out_put_dis[out_put_dis>500]=500
fig=plt.figure()
left, bottom, width, height = 0.05,0.2,0.8,0.75
ax = fig.add_axes([left,bottom,width,height])
ax.set_title('track match')
ax.grid()
left, bottom, width, height = 0.05,0.01,0.8,0.2
ax2 = fig.add_axes([left,bottom,width,height])
# ax2.plot(x,y,'g')
ax2.set_xlabel('points')
ax2.set_ylabel('mz')
ax2.set_title('match')

left, bottom, width, height = 0.05,0.5,0.2,0.45
ax3 = fig.add_axes([left,bottom,width,height])
# ax2.plot(x,y,'g')
ax3.set_xlabel('points')
ax3.set_ylabel('mz')

left, bottom, width, height = 0.8,0.0,0.2,0.3
ax4 = fig.add_axes([left,bottom,width,height])
# ax2.plot(x,y,'g')
ax4.set_ylabel('info')
left, bottom, width, height = 0.8,0.35,0.2,0.3
ax5 = fig.add_axes([left,bottom,width,height])
# ax2.plot(x,y,'g')
ax5.set_ylabel('info')
left, bottom, width, height = 0.8,0.7,0.2,0.25
ax6 = fig.add_axes([left,bottom,width,height])
# ax2.plot(x,y,'g')
ax6.set_ylabel('info')

left, bottom, width, height = 0.3,0.9,0.05,0.05
ax7 = fig.add_axes([left,bottom,width,height])
# ax2.plot(x,y,'g')
# ax6.set_ylabel('info')
ax.scatter(data1['x'].values,data1['y'].values,c='y')
ax.scatter(dataA.loc[:,'x'].values,dataA.loc[:,'y'].values,c='gray')
plt.ion()
plt.pause(5)

match_start_index=3

data_index=0
for index,item in enumerate(output_result):
    data_index=index
    ax.scatter(data1.loc[mkt[index],'x'],data1.loc[mkt[index],'y'],c='m',s=5)
    ax.scatter(dataA.loc[data_index+start_index+match_start_index,'x'],dataA.loc[data_index+start_index+match_start_index,'y'],c='g')
    ax.scatter(data1.loc[item,'x'],data1.loc[item,'y'],c='c')   
    ax.scatter(data1.loc[mkt[index][-1],'x'],data1.loc[mkt[index][-1],'y'],c='k',marker="*",s=200)  
    
    ax.plot([dataA.loc[data_index+start_index+match_start_index,'x'],data1.loc[item,'x']],[dataA.loc[data_index+start_index+match_start_index,'y'],data1.loc[item,'y']],'r')
    
    ax.set_title('%d step ds=%.3f,yaw=%.3f,scale=%.3f,ls=%d'%(index,0,info_result[index,3]/np.pi*180,info_result[index,2],mkt[index][-1]))
    ax.axis('equal')
    ax4.cla()
    ax5.cla()
    ax6.cla()
    ax7.cla()
    if index>5:
        ax2.cla()
        ax2.plot(range(data_index),dataA.loc[start_index+match_start_index:start_index+match_start_index-1+data_index,'mmagn'],'g*-')
        ax2.plot(range(index), data1.loc[output_result[:index], 'mmagn'], 'r*-')
    if index>2 and index<100:
        ax3.cla()
        ax3.plot(range(data_index),dataA.loc[start_index+match_start_index:start_index+match_start_index-1+data_index,'mmagn'],'g*-')
        ax3.plot(range(index), data1.loc[output_result[:index], 'mmagn'], 'r*-')
    elif index>=100:
        ax3.cla()
        ax3.plot(range(100),dataA.loc[start_index+match_start_index+data_index-100:start_index+match_start_index-1+data_index,'mmagn'],'g*-')
        ax3.plot(range(100),data1.loc[output_result[index-100:index],'mmagn'], 'r*-')
    else:
        pass
    ax4.plot(range(index),out_put_dis[:index,0],'c*-')
    ax4.grid()
    ax4.set_title('cur node count %d'%out_put_dis[index,0])
    # ax5.ylim(0, 500)
    ax5.plot(range(index),out_put_dis[:index,1],'c*-')
    ax5.set_title('cur dis %.3f'%out_put_dis[index,1])
    ax6.plot(range(index),out_put_dis[:index,2],'c*-')
    ax6.grid()
    ax6.set_title('cur time %.3f'%out_put_dis[index,2])

    if out_put_dis[index,1]>=90 :
        ax7.text(0,0,"LOST!",fontdict={'size':'20','color':'r'},bbox = dict(facecolor = "y", alpha = 0.2))
    elif out_put_dis[index,0]<10:
        ax7.text(0,0,"TRACK!",fontdict={'size':'20','color':'b'},bbox = dict(facecolor = "y", alpha = 0.2))
    else:
        ax7.text(0,0,"FIND!",fontdict={'size':'20','color':'g'},bbox = dict(facecolor = "y", alpha = 0.2))
    ax2.grid()
    ax2.set_title('all points  match')
    ax3.grid()
    ax3.set_title('100 points  match')
    plt.pause(0.5)
    ax.lines.pop(0)
    ax.collections.remove(ax.collections[-1])
    ax.collections.remove(ax.collections[index*2+2])

plt.ioff()
plt.show()
