
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from fastdtw import fastdtw

nresult = pd.read_csv('/home/aaron/project/MapMatching/data/allSecD.csv')
ios_data = pd.read_csv(
    '/media/aaron/新加卷/工作记录/项目产出及记录/19年羲和后台过程归档/第二阶段材料整理/测试过程/iosFp/my_iOS_device_2019-06-26_16-48-43_+0800data.csv', header=None)
# ios_data = pd.read_csv(
#     '/media/aaron/新加卷1/工作记录/项目产出及记录/19年羲和后台过程归档/第二阶段材料整理/测试过程/iosFp/my_iOS_device_2019-06-21_15-05-05_+0800data.csv', header=None)


ios_data.columns = ['x', 'y', 'sl', 'yaw',
                    'detayaw', 'mx', 'my', 'mz', 'si', 'stime']
ios_data['mmagn'] = np.sqrt(
    ios_data['mx']**2+ios_data['my']**2+ios_data['mz']**2)

with open("../data/log.txt",'r') as target:
    lastline=target.readlines()[-1]
ts1=[]
for item in lastline[:-2].split(','):
    ts1.append(int(item))
start_index = 0
end_index = 336
ts2=range(end_index)
# fastdtw(ios_data.loc[ts2,'mmagn'],nresult.loc[ts1,'mmagn'])

item = int(item)
sc_item = 1
# print(sc_item)
init_item = ts1[0]
# print ('长度缩短%.3f'%sc_item)
plt.figure(figsize=(20, 10))
ax = plt.subplot(1, 2, 1)
# ax.imshow(img2)

ax.scatter(nresult.loc[:, 'x'], nresult.loc[:, 'y'], c='gray')
ax.plot(nresult.loc[ts1, 'x'],
        nresult.loc[ts1, 'y'], 'c*-', markersize=20)
ax.plot(ios_data.loc[start_index:end_index, 'x']*sc_item+nresult.loc[init_item, 'x'],
        ios_data.loc[start_index:end_index, 'y']*sc_item+nresult.loc[init_item, 'y'], 'r*-')
ax.plot(nresult.loc[init_item, 'x'],
        nresult.loc[init_item, 'y'], 'yo-', markersize=20)
ax.plot(nresult.loc[ts1[-1], 'x'],        nresult.loc[ts1[-1], 'y'], 'mo-', markersize=20)

ax.axis('equal')
ax.grid()

distance, path = fastdtw(nresult.loc[ts1, 'mmagn']  # -nresult.loc[tmp_node_list[item].outFatherSeq()[1:end_index],'mmagn'].mean()
                         ,
                         ios_data.loc[ts2,'mmagn']
                         #                          -ios_data.loc[start_index:end_index,'mmagn'].mean()
                         )
ax2 = plt.subplot(1, 2, 2)
# print(tmp_node_list[item].outFatherSeq()[1:end_index])
ax2.plot(range(len(ts1)), nresult.loc[ts1, 'mmagn']  # -nresult.loc[tmp_node_list[item].outFatherSeq()[1:end_index],'mmagn'].mean()
         , 'c*-')
ax2.plot(range(end_index), ios_data.loc[ts2,'mmagn']  # -ios_data.loc[start_index:end_index,'mmagn'].mean()
         , 'r*-')
for jjitem in path:
    ax2.plot([jjitem[0], jjitem[1]], [nresult.loc[ts1[jjitem[0]], 'mmagn']  # -nresult.loc[tmp_node_list[item].outFatherSeq()[1:end_index],'mmagn'].mean()
                                      ,
                                      ios_data.loc[ts2[jjitem[1]],'mmagn']
                                      #                          -ios_data.loc[start_index:end_index,'mmagn'].mean()
                                      ], 'y-')
plt.title('ds=%.3f'%(distance))
#     plt.savefig('./data/s%d.png' % item, dpi=300)

plt.show()