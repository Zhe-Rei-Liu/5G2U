import numpy as np
import matplotlib.pyplot as plt
import statistics

ccnumber = 1
anumber = 1
mnumber = 1
"""
計算WC ts_3-1的時間
"""
file = '../../recording/ts_2-1_CCclient.txt' 
ccx,ccy21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccx.append(ccnumber)
		ccy21.append(ccval[0])
		ccnumber = ccnumber+1

bar1_x = np.array(ccx)
ccy21 = np.array(ccy21) 

file = '../../recording/ts_3-2_CCclient.txt' 
ccy32 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy32.append(ccval[0])
ccy32 = np.array(ccy32) 

bar1_y1 = ccy32 + ccy21
"""
計算WC->FM的時間
"""
file = 'CC_WC->FM.txt' 
ccy43 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy43.append(ccval[0])
		
bar1_y2 = np.array(ccy43) 
"""
計算FM ts_9-4的時間	 	
"""
file = '../../recording/ts_5-4_CCserver.txt' 
ccy54 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy54.append(ccval[0])
ccy54 = np.array(ccy54) 		
		
file = '../../recording/ts_7-5_CCserver.txt' 
ccy75 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy75.append(ccval[0])
ccy75.append(0)
ccy75 = np.array(ccy75) 
		
file = '../../recording/ts_8-7_CCserver.txt' 
ccy87 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy87.append(ccval[0])
ccy87.append(0)
ccy87 = np.array(ccy87) 
		
file = '../../recording/ts_9-8_CCserver.txt' 
ccy98 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy98.append(ccval[0])
ccy98.append(0)
ccy98 = np.array(ccy98) 

bar1_y3 = ccy54 + ccy75 + ccy87 + ccy98
"""
計算FM->WC的時間
"""
file = 'CC_FM->WC.txt' 
ccy109 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy109.append(ccval[0])
		
bar1_y4 = np.array(ccy109) 
"""
計算WC ts_12-10的時間	 	
"""
file = '../../recording/ts_11-10_CCclient.txt' 
ccy1110 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy1110.append(ccval[0])
ccy1110.append(0)
ccy1110 = np.array(ccy1110) 
		
file = '../../recording/ts_12-11_CCclient.txt' 
ccy1211 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy1211.append(ccval[0])
ccy1211.append(0)
print(ccy1211[1593])
ccy1211 = np.array(ccy1211) 

bar1_y5 = ccy1110 + ccy1211	

# 分析CC傳輸時間達到多少QoS
cctotal = bar1_y5 + bar1_y4 + bar1_y3 + bar1_y2 + bar1_y1 
cctotal = cctotal.tolist()
print(len(cctotal))
ccmean = statistics.mean(cctotal)
ccst_dev = statistics.pstdev(cctotal)
ccmax = max(cctotal)
ccmin = min(cctotal)
print(ccmax)
print(ccmin)

# Tranmission time > 0.02
i = 0
violate_tt_CC = 0
while i < len(cctotal):
	if (cctotal[i] > 0.02):
		violate_tt_CC = violate_tt_CC+1
	i = i + 1
ttrate_CC = 1 - (violate_tt_CC/len(cctotal))
   	
"""
計算WC ts_3-1的時間
"""
file = '../../recording/ts_2-1_Aclient.txt' 
ax,ay21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ax.append(anumber)
		ay21.append(aval[0])
		anumber = anumber+1

bar2_x = np.array(ax)
ay21 = np.array(ay21) 

file = '../../recording/ts_3-2_Aclient.txt' 
ay32 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay32.append(aval[0])
ay32 = np.array(ay32) 

bar2_y1 = ay32 + ay21			

"""
計算WC->FM的時間
"""
file = 'A_WC->FM.txt' 
ay43 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay43.append(aval[0])
		
bar2_y2 = np.array(ay43) 
"""
計算FM ts_9-4的時間	 	
"""
file = '../../recording/ts_5-4_Aserver.txt' 
ay54 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay54.append(aval[0])
ay54 = np.array(ay54) 		
		
file = '../../recording/ts_7-5_Aserver.txt' 
ay75 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay75.append(aval[0])
ay75.append(0)
ay75 = np.array(ay75) 
		
file = '../../recording/ts_8-7_Aserver.txt' 
ay87 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay87.append(aval[0])
ay87.append(0)
ay87 = np.array(ay87) 
		
file = '../../recording/ts_9-8_Aserver.txt' 
ay98 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay98.append(aval[0])
ay98.append(0)
ay98 = np.array(ay98) 

bar2_y3 = ay54 + ay75 + ay87 + ay98
"""
計算FM->WC的時間
"""
file = 'A_FM->WC.txt' 
ay109 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay109.append(aval[0])
		
bar2_y4 = np.array(ay109) 
"""
計算WC ts_12-10的時間	 	
"""
file = '../../recording/ts_11-10_Aclient.txt' 
ay1110 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay1110.append(aval[0])
ay1110.append(0)
ay1110 = np.array(ay1110) 
		
file = '../../recording/ts_12-11_Aclient.txt' 
ay1211 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay1211.append(aval[0])
ay1211.append(0)
ay1211 = np.array(ay1211) 

bar2_y5 = ay1110 + ay1211	

# 分析A傳輸時間達到多少QoS
atotal = bar2_y5 + bar2_y4 + bar2_y3 + bar2_y2 + bar2_y1 
atotal = atotal.tolist()
print(len(atotal))
amean = statistics.mean(atotal)
ast_dev = statistics.pstdev(atotal)
amax = max(atotal)
amin = min(atotal)
print(amin)

# Tranmission time > 0.03
i = 0
violate_tt_A = 0
while i < len(atotal):
	if (atotal[i] > 0.03):
		violate_tt_A = violate_tt_A+1
	i = i + 1
ttrate_A = 1 - (violate_tt_A/len(atotal))
"""
計算WC ts_3-1的時間
"""
file = '../../recording/ts_2-1_Mpub.txt' 
mx,my21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval = [float(s) for s in line.split()]
		mx.append(mnumber)
		my21.append(mval[0])
		mnumber = mnumber+1

bar3_x = np.array(mx)
my21 = np.array(my21) 

file = '../../recording/ts_3-2_Mpub.txt' 
my32 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval = [float(s) for s in line.split()]
		my32.append(mval[0])
my32 = np.array(my32) 

bar3_y1 = my32 + my21	
"""
計算WC->FM的時間
"""
file = 'M_trans_time.txt' 
my43 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval = [float(s) for s in line.split()]
		my43.append(mval[0])
		
bar3_y2 = np.array(my43) 	

"""
計算FM ts_6-4的時間
"""
file = '../../recording/ts_5-4_Msub.txt' 
my54 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval = [float(s) for s in line.split()]
		my54.append(mval[0])

my54 = np.array(my54) 	

file = '../../recording/ts_6-5_Msub.txt' 
my65 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval = [float(s) for s in line.split()]
		my65.append(mval[0])

my65 = np.array(my65) 

bar3_y3 = my65 + my54 	

# 分析M傳輸時間達到多少QoS
mtotal = bar3_y3 + bar3_y2 + bar3_y1 
mtotal = mtotal.tolist()
print(len(mtotal))
mmean = statistics.mean(mtotal)
mst_dev = statistics.pstdev(mtotal)
mmax = max(mtotal)
mmin = min(mtotal)
print(mmin)

# Tranmission time > 0.1
i = 0
violate_tt_M = 0
while i < len(mtotal):
	if (mtotal[i] > 0.3):
		violate_tt_M = violate_tt_M+1
	i = i + 1
ttrate_M = 1 - (violate_tt_M/len(mtotal))
   	

"""
繪製結果圖
"""
msg_num = 4570
plt.figure(figsize=(50,10))
plt.subplot(3,1,1)
barCC_1 = plt.bar(bar1_x, bar1_y1, color='green', width=1.0)
barCC_2 = plt.bar(bar1_x, bar1_y2, bottom=bar1_y1, color='gray', width=1.0)
barCC_3 = plt.bar(bar1_x, bar1_y3, bottom=bar1_y1+bar1_y2, color='lightcoral', width=1.0)
barCC_4 = plt.bar(bar1_x, bar1_y4, bottom=bar1_y1+bar1_y2+bar1_y3, color='darkgray', width=1.0)
barCC_5 = plt.bar(bar1_x, bar1_y5, bottom=bar1_y1+bar1_y2+bar1_y3+bar1_y4, color='green', width=1.0)
plt.xlim(0,msg_num)
plt.ylim(0,0.03)
plt.title('Control Command')
plt.text(msg_num*0.75, 0.03*1.23 , r'$\mu=%0.9f$'%(ccmean),fontsize=10)
plt.text(msg_num*0.75, 0.03*1.13, r'$\sigma=%0.9f$'%(ccst_dev),fontsize=10)
plt.text(msg_num*0.75, 0.03*1.03 , 'Max=%0.9f'%(ccmax),fontsize=10)
plt.text(msg_num*0.85, 0.03*1.03, 'Transmission time<20ms[%%]:%0.3f'%(ttrate_CC*100),fontsize=10)
#plt.text(0, .0255, r'$\mu=%0.9f$'%(ccmean)+'   $\sigma=%0.9f$'%(ccst_dev)+'    Max=%0.9f'%(ccmax)+'    Percentage of tranamission time<20ms =%0.3f'%(ttrate_CC),fontsize=12)
plt.legend((barCC_1[0], barCC_2[0], barCC_3[0], barCC_4[0]), ('OPC UA exe_latency in WC', 'WC->FM E2E latency', 'OPC UA exe_latency in FM','FM->WC E2E latency'),bbox_to_anchor=(0, 1), loc='upper left', prop={'size': 6})
plt.xlabel('Msg_number')
plt.ylabel('Transmission Time')


msg_num = 2110
plt.subplot(3,1,2)
plt.bar(bar2_x, bar2_y1, color='green', width=1.0)
plt.bar(bar2_x, bar2_y2, bottom=bar2_y1, color='gray', width=1.0)
plt.bar(bar2_x, bar2_y3, bottom=bar2_y1+bar2_y2, color='lightcoral', width=1.0)
plt.bar(bar2_x, bar2_y4, bottom=bar2_y1+bar2_y2+bar2_y3, color='darkgray', width=1.0)
plt.bar(bar2_x, bar2_y5, bottom=bar2_y1+bar2_y2+bar2_y3+bar2_y4, color='green', width=1.0)
plt.xlim(0,msg_num)
plt.ylim(0,0.045)
plt.title('Alarming')
plt.text(msg_num*0.75, 0.045*1.23, r'$\mu=%0.9f$'%(amean),fontsize=10)
plt.text(msg_num*0.75, 0.045*1.13, r'$\sigma=%0.9f$'%(ast_dev),fontsize=10)
plt.text(msg_num*0.75, 0.045*1.03, 'Max=%0.9f'%(amax),fontsize=10)
plt.text(msg_num*0.85, 0.045*1.03, 'Transmission time<30ms[%%]:%0.3f'%(ttrate_A*100),fontsize=10)
#plt.text(0, .036, r'$\mu=%0.9f$'%(amean)+'   $\sigma=%0.9f$'%(ast_dev)+'    Max=%0.9f'%(amax)+'    Percentage of tranamission time<30ms =%0.3f'%(ttrate_A),fontsize=12)
plt.legend((barCC_1[0], barCC_2[0], barCC_3[0], barCC_4[0]), ('OPC UA exe_latency in WC', 'WC->FM E2E latency', 'OPC UA exe_latency in FM','FM->WC E2E latency'),bbox_to_anchor=(0, 1), loc='upper left', prop={'size': 6})
plt.xlabel('Msg_number')
plt.ylabel('Transmission Time')


msg_num = 900
plt.subplot(3,1,3)
plt.bar(bar3_x, bar3_y1, color='green', width=1.0)
plt.bar(bar3_x, bar3_y2, bottom=bar3_y1, color='gray', width=1.0)
plt.bar(bar3_x, bar3_y3, bottom=bar3_y1+bar3_y2, color='lightcoral', width=1.0)
plt.xlim(0,msg_num)
plt.ylim(0,0.35)
plt.title('S.D Uploading')
plt.text(msg_num*0.75, 0.35*1.23, r'$\mu=%0.9f$'%(mmean),fontsize=10)
plt.text(msg_num*0.75, 0.35*1.13, r'$\sigma=%0.9f$'%(mst_dev),fontsize=10)
plt.text(msg_num*0.75, 0.35*1.03, 'Max=%0.9f'%(mmax),fontsize=10)
plt.text(msg_num*0.85, 0.35*1.03, 'Transmission time<300ms[%%]:%0.3f'%(ttrate_M*100),fontsize=10)
#plt.text(0, .155, r'$\mu=%0.9f$'%(mmean)+'   $\sigma=%0.9f$'%(mst_dev)+'    Max=%0.9f'%(mmax)+'    Percentage of tranamission time<100ms =%0.3f'%(ttrate_M),fontsize=12)
plt.legend((barCC_1[0], barCC_2[0], barCC_3[0]), ('OPC UA exe_latency in WC', 'WC->FM E2E latency', 'OPC UA exe_latency in FM'),bbox_to_anchor=(0, 1), loc='upper left', prop={'size': 6})
plt.xlabel('Msg_number')
plt.ylabel('Transmission Time')

plt.subplots_adjust(left=0.05,
                    bottom=0.05, 
                    right=0.94, 
                    top=0.92, 
                    wspace=0.2, 
                    hspace=0.6)
plt.show()
