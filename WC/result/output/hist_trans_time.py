import numpy as np
import matplotlib.pyplot as plt
import statistics

ccnumber = 1
anumber = 1
mnumber = 1

alg = input("Please enter your algorithm (LCP, WGCL, AW-WGCL): ")

#print(alg)
"""
計算WC ts_3-1的時間
"""
file = '/home/lukelin/Desktop/recording/ts_2-1_CCclient.txt' 
ccx,ccy21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccx.append(ccnumber)
		ccy21.append(ccval[0])
		ccnumber = ccnumber+1

ccx = np.array(ccx)
ccy21 = np.array(ccy21) 

file = '/home/lukelin/Desktop/recording/ts_3-2_CCclient.txt' 
ccy32 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy32.append(ccval[0])
ccy32 = np.array(ccy32) 

"""
計算WC->FM的時間
"""
if alg == "AW-WGCL":
	file = '/home/lukelin/Desktop/result/output/AW-WGCL_CC_WC->FM.txt' 
elif alg == "WGCL":
	file = '/home/lukelin/Desktop/result/output/WGCL_CC_WC->FM.txt'
elif alg == "LCP":
	file = '/home/lukelin/Desktop/result/output/LCP_CC_WC->FM.txt'
else:
	print("Wrong Algorithm!\n")
	os._exit(0)
	
ccy43 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy43.append(ccval[0])
		
ccy43 = np.array(ccy43) 
"""
計算FM ts_9-4的時間	 	
"""
file = '/home/lukelin/Desktop/recording/ts_5-4_CCserver.txt' 
ccy54 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy54.append(ccval[0])
ccy54 = np.array(ccy54) 		
		
file = '/home/lukelin/Desktop/recording/ts_7-5_CCserver.txt' 
ccy75 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy75.append(ccval[0])
ccy75.append(0)
ccy75 = np.array(ccy75) 
		
file = '/home/lukelin/Desktop/recording/ts_8-7_CCserver.txt' 
ccy87 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy87.append(ccval[0])
ccy87.append(0)
ccy87 = np.array(ccy87) 
		
file = '/home/lukelin/Desktop/recording/ts_9-8_CCserver.txt' 
ccy98 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy98.append(ccval[0])
ccy98.append(0)
ccy98 = np.array(ccy98) 

"""
計算FM->WC的時間
"""
if alg == "AW-WGCL":
	file = '/home/lukelin/Desktop/result/output/AW-WGCL_CC_FM->WC.txt' 
elif alg == "WGCL":
	file = '/home/lukelin/Desktop/result/output/WGCL_CC_FM->WC.txt'
elif alg == "LCP": 
	file = '/home/lukelin/Desktop/result/output/LCP_CC_FM->WC.txt'
	
ccy109 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy109.append(ccval[0])
		
ccy109 = np.array(ccy109) 
"""
計算WC ts_12-10的時間	 	
"""
file = '/home/lukelin/Desktop/recording/ts_11-10_CCclient.txt' 
ccy1110 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy1110.append(ccval[0])
ccy1110.append(0)
ccy1110 = np.array(ccy1110) 
		
file = '/home/lukelin/Desktop/recording/ts_12-11_CCclient.txt' 
ccy1211 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval = [float(s) for s in line.split()]
		ccy1211.append(ccval[0])
ccy1211.append(0)
ccy1211 = np.array(ccy1211) 

# 分析CC傳輸時間達到多少QoS
cctotal = ccy21 + ccy32 + ccy43 + ccy54 + ccy75 + ccy87 + ccy98 + ccy109 + ccy1110 + ccy1211
cctotal = cctotal.tolist()
print(len(cctotal))

i = 0
if alg == "AW-WGCL":
	path = '/home/lukelin/Desktop/result/output/AW-WGCL_CCtt.txt' 
elif alg == "WGCL":
	path = '/home/lukelin/Desktop/result/output/WGCL_CCtt.txt'
elif alg == "LCP": 
	path = '/home/lukelin/Desktop/result/output/LCP_CCtt.txt'
with open(path,'w') as f:	
	while i < len(cctotal):
		print(cctotal[i], file = f)
		i = i+1
	f.close()

ccmean = statistics.mean(cctotal)
ccst_dev = statistics.pstdev(cctotal)
ccmax = max(cctotal)
ccmin = min(cctotal)
#print(ccmax)
#print(ccmin)

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
file = '/home/lukelin/Desktop/recording/ts_2-1_Aclient.txt' 
ax,ay21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ax.append(anumber)
		ay21.append(aval[0])
		anumber = anumber+1

ax = np.array(ax)
ay21 = np.array(ay21) 

file = '/home/lukelin/Desktop/recording/ts_3-2_Aclient.txt' 
ay32 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay32.append(aval[0])
ay32 = np.array(ay32) 			

"""
計算WC->FM的時間
"""
if alg == "AW-WGCL": 
	file = '/home/lukelin/Desktop/result/output/AW-WGCL_A_WC->FM.txt' 
elif alg == "WGCL":
	file = '/home/lukelin/Desktop/result/output/WGCL_A_WC->FM.txt'
elif alg == "LCP":
	file = '/home/lukelin/Desktop/result/output/LCP_A_WC->FM.txt'
	
ay43 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay43.append(aval[0])
		
ay43 = np.array(ay43) 
"""
計算FM ts_9-4的時間	 	
"""
file = '/home/lukelin/Desktop/recording/ts_5-4_Aserver.txt' 
ay54 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay54.append(aval[0])
ay54 = np.array(ay54) 		
		
file = '/home/lukelin/Desktop/recording/ts_7-5_Aserver.txt' 
ay75 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay75.append(aval[0])
ay75.append(0)
ay75 = np.array(ay75) 
		
file = '/home/lukelin/Desktop/recording/ts_8-7_Aserver.txt' 
ay87 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay87.append(aval[0])
ay87.append(0)
ay87 = np.array(ay87) 
		
file = '/home/lukelin/Desktop/recording/ts_9-8_Aserver.txt' 
ay98 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay98.append(aval[0])
ay98.append(0)
ay98 = np.array(ay98) 

"""
計算FM->WC的時間
"""
if alg == "AW-WGCL":
	file = '/home/lukelin/Desktop/result/output/AW-WGCL_A_FM->WC.txt' 
elif alg == "WGCL":
	file = '/home/lukelin/Desktop/result/output/WGCL_A_FM->WC.txt'
elif alg == "LCP":
	file = '/home/lukelin/Desktop/result/output/LCP_A_FM->WC.txt'
	
ay109 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay109.append(aval[0])
		
ay109 = np.array(ay109) 
"""
計算WC ts_12-10的時間	 	
"""
file = '/home/lukelin/Desktop/recording/ts_11-10_Aclient.txt' 
ay1110 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay1110.append(aval[0])
ay1110.append(0)
ay1110 = np.array(ay1110) 
		
file = '/home/lukelin/Desktop/recording/ts_12-11_Aclient.txt' 
ay1211 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval = [float(s) for s in line.split()]
		ay1211.append(aval[0])
ay1211.append(0)
ay1211 = np.array(ay1211) 

# 分析A傳輸時間達到多少QoS
atotal = ay21 + ay32 + ay43 + ay54 + ay75 + ay87 + ay98 + ay109 + ay1110 + ay1211
atotal = atotal.tolist()
print(len(atotal))

i = 0
if alg == "AW-WGCL":
	path = '/home/lukelin/Desktop/result/output/AW-WGCL_Att.txt' 
elif alg == "WGCL":
	path = '/home/lukelin/Desktop/result/output/WGCL_Att.txt'
elif alg == "LCP": 
	path = '/home/lukelin/Desktop/result/output/LCP_Att.txt'
with open(path,'w') as f:	
	while i < len(atotal):
		print(atotal[i], file = f)
		i = i+1
	f.close()

amean = statistics.mean(atotal)
ast_dev = statistics.pstdev(atotal)
amax = max(atotal)
amin = min(atotal)
#print(amax)
#print(amin)

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
file = '/home/lukelin/Desktop/recording/ts_2-1_Mpub_demo.txt' 
mx,my21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval = [float(s) for s in line.split()]
		mx.append(mnumber)
		my21.append(mval[0])
		mnumber = mnumber+1

mx = np.array(mx)
my21 = np.array(my21) 

file = '/home/lukelin/Desktop/recording/ts_3-2_Mpub_demo.txt' 
my32 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval = [float(s) for s in line.split()]
		my32.append(mval[0])
my32 = np.array(my32) 
	
"""
計算WC->FM的時間
"""
if alg == "AW-WGCL":
	file = '/home/lukelin/Desktop/result/output/AW-WGCL_M_WC->FM.txt' 
elif alg == "WGCL": 
	file = '/home/lukelin/Desktop/result/output/WGCL_M_WC->FM.txt'
elif alg == "LCP": 
	file = '/home/lukelin/Desktop/result/output/LCP_M_WC->FM.txt'
	
my43 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval = [float(s) for s in line.split()]
		my43.append(mval[0])
		
my43 = np.array(my43) 	

"""
計算FM ts_6-4的時間
"""
file = '/home/lukelin/Desktop/recording/ts_5-4_Msub_demo.txt' 
my54 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval = [float(s) for s in line.split()]
		my54.append(mval[0])

my54 = np.array(my54) 	

file = '/home/lukelin/Desktop/recording/ts_6-5_Msub_demo.txt' 
my65 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval = [float(s) for s in line.split()]
		my65.append(mval[0])

my65 = np.array(my65) 

# 分析M傳輸時間達到多少QoS
mtotal = my21 + my32 + my43 + my54 + my65
mtotal = mtotal.tolist()
print(len(mtotal))

i = 0
if alg == "AW-WGCL":
	path = '/home/lukelin/Desktop/result/output/AW-WGCL_Mtt.txt' 
elif alg == "WGCL":
	path = '/home/lukelin/Desktop/result/output/WGCL_Mtt.txt'
elif alg == "LCP": 
	path = '/home/lukelin/Desktop/result/output/LCP_Mtt.txt'
with open(path,'w') as f:	
	while i < len(mtotal):
		print(mtotal[i], file = f)
		i = i+1
	f.close()

mmean = statistics.mean(mtotal)
mst_dev = statistics.pstdev(mtotal)
mmax = max(mtotal)
mmin = min(mtotal)
#print(mmax)
#print(mmin)

# Tranmission time > 0.3
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
plt.figure(figsize=(50,10))

ccxvalue = []

for i in range(1, 21):
	ccxvalue.append(0.05*i)	
	
yvalue = [1, 10, 100, 1000, 10000]	

ccbound = []
for i in range(len(yvalue)):
	ccbound.append(0.02)

plt.subplot(3,1,1)
plt.title('Control Command',fontsize=14)
plt.plot(ccbound, yvalue, '--', color ='black')
plt.hist(cctotal, (int)((ccmax -ccmin)/0.0015), density = 0, color ='green', histtype = 'bar',alpha = 0.7, edgecolor='black') 
plt.xticks(ccxvalue)
plt.yscale("log")
plt.text(0.8, 7900 , r'$\mu = %0.9f$'%(ccmean),fontsize=11)
plt.text(0.8, 3160, r'$\sigma = %0.9f$'%(ccst_dev),fontsize=11)
plt.text(0.8, 1260, 'Max = %0.9f'%(ccmax),fontsize=11)
plt.text(0.8, 500, 'min = %0.9f'%(ccmin),fontsize=11)
plt.text(0.8, 200, 'Transmission time<20ms[%%]:%0.3f'%(ttrate_CC*100),fontsize=11)
plt.xlabel('Transmission Time',fontsize=12)
plt.ylabel('Msg_number',fontsize=12)

axvalue = []

for i in range(1, 21):
	axvalue.append(0.05*i)

abound = []
for i in range(len(yvalue)):
	abound.append(0.03)

plt.subplot(3,1,2)
plt.title('Warning',fontsize=14)
plt.plot(abound, yvalue, '--', color ='black')
plt.hist(atotal, (int)((amax -amin)/0.0015), density = 0, color ='red', histtype = 'bar',alpha = 0.7, edgecolor='black') 
plt.xticks(axvalue)
plt.yscale("log")
plt.text(0.8, 7900 , r'$\mu = %0.9f$'%(amean),fontsize=11)
plt.text(0.8, 3160, r'$\sigma = %0.9f$'%(ast_dev),fontsize=11)
plt.text(0.8, 1260, 'Max = %0.9f'%(amax),fontsize=11)
plt.text(0.8, 500, 'min = %0.9f'%(amin),fontsize=11)
plt.text(0.8, 200, 'Transmission time<30ms[%%]:%0.3f'%(ttrate_A*100),fontsize=11)
plt.xlabel('Transmission Time',fontsize=12)
plt.ylabel('Msg_number',fontsize=12)

mxvalue = []

for i in range(1, 21):
	mxvalue.append(0.3*i)

mbound = []
for i in range(len(yvalue)):
	mbound.append(0.3)

plt.subplot(3,1,3)
plt.title('S.D Uploading',fontsize=14)
plt.plot(mbound, yvalue, '--', color ='black')
plt.hist(mtotal, (int)((mmax -mmin)/0.01), density = 0, color ='yellow', histtype = 'bar',alpha = 0.7, edgecolor='black') 
plt.xticks(mxvalue)
plt.yscale("log")
plt.text(4.8, 7900 , r'$\mu = %0.9f$'%(mmean),fontsize=11)
plt.text(4.8, 3160, r'$\sigma = %0.9f$'%(mst_dev),fontsize=11)
plt.text(4.8, 1260, 'Max = %0.9f'%(mmax),fontsize=11)
plt.text(4.8, 500, 'min = %0.9f'%(mmin),fontsize=11)
plt.text(4.8, 200, 'Transmission time<300ms[%%]:%0.3f'%(ttrate_M*100),fontsize=11)
plt.xlabel('Transmission Time',fontsize=12)
plt.ylabel('Msg_number',fontsize=12)

plt.subplots_adjust(left=0.05,
                    bottom=0.05, 
                    right=0.94, 
                    top=0.92, 
                    wspace=0.2, 
                    hspace=0.6)
plt.show()

