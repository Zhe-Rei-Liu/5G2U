import numpy as np
import matplotlib.pyplot as plt
import statistics

ccnumber_21 = 1
ccnumber_43 = 1
ccnumber_65 = 1
ccnumber_87 = 1

file = '/home/j/Desktop/recording/ts_5-4_CCserver.txt' 
ccx21,ccy21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval_21 = [float(s) for s in line.split()]
		ccx21.append(ccnumber_21)
		ccy21.append(ccval_21[0])
		ccnumber_21 = ccnumber_21+1

ccmean_21 = statistics.mean(ccy21)
ccst_dev_21 = statistics.pstdev(ccy21)
ccmax_21 = max(ccy21)

#xx21 = [1]
#yy21 = [mean_21]

bar1_x = np.array([1])
bar1_y = np.array([ccmean_21]) 

file = '/home/j/Desktop/recording/ts_6-5_CCserver.txt' 
ccx43,ccy43 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval_43 = [float(s) for s in line.split()]
		ccx43.append(ccnumber_43)
		ccy43.append(ccval_43[0])
		ccnumber_43 = ccnumber_43+1

ccmean_43 = statistics.mean(ccy43)
ccst_dev_43 = statistics.pstdev(ccy43)
ccmax_43 = max(ccy43)

#xx43 = [1]
#yy43 = [mean_43]

bar2_x = np.array([1])
bar2_y = np.array([ccmean_43]) 


file = '/home/j/Desktop/recording/ts_8-7_CCserver.txt' 
ccx65,ccy65 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval_65 = [float(s) for s in line.split()]
		ccx65.append(ccnumber_65)
		ccy65.append(ccval_65[0])
		ccnumber_65 = ccnumber_65+1

ccmean_65 = statistics.mean(ccy65)
ccst_dev_65 = statistics.pstdev(ccy65)
ccmax_65 = max(ccy65)

#xx65 = [1]
#yy65 = [mean_65]

bar3_x = np.array([1])
bar3_y = np.array([ccmean_65]) 
#bar3_y = np.append(bar3_y,[0]) 

file = '/home/j/Desktop/recording/ts_9-8_CCserver.txt' 
ccx87,ccy87 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval_87 = [float(s) for s in line.split()]
		ccx87.append(ccnumber_87)
		ccy87.append(ccval_87[0])
		ccnumber_87 = ccnumber_87+1

ccmean_87 = statistics.mean(ccy87)
ccst_dev_87 = statistics.pstdev(ccy87)
ccmax_87 = max(ccy87)

#xx87 = [1]
#yy87 = [mean_87]

bar4_x = np.array([1])
bar4_y = np.array([ccmean_87]) 
#bar4_y = np.append(bar4_y, [0])
#print(yy21,yy43,yy65,yy87)

anumber_21 = 1
anumber_43 = 1
anumber_65 = 1
anumber_87 = 1

file = '/home/j/Desktop/recording/ts_5-4_Aserver.txt' 
ax21,ay21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval_21 = [float(s) for s in line.split()]
		ax21.append(anumber_21)
		ay21.append(aval_21[0])
		anumber_21 = anumber_21+1

amean_21 = statistics.mean(ay21)
ast_dev_21 = statistics.pstdev(ay21)
amax_21 = max(ay21)

#xx21 = [1]
#yy21 = [mean_21]
bar1_x = np.append(bar1_x,[2])
bar1_y = np.append(bar1_y,amean_21 )

file = '/home/j/Desktop/recording/ts_6-5_Aserver.txt' 
ax43,ay43 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval_43 = [float(s) for s in line.split()]
		ax43.append(anumber_43)
		ay43.append(aval_43[0])
		anumber_43 = anumber_43+1

amean_43 = statistics.mean(ay43)
ast_dev_43 = statistics.pstdev(ay43)
amax_43 = max(ay43)

#xx43 = [1]
#yy43 = [mean_43]

bar2_x = np.append(bar2_x,[2])
bar2_y = np.append(bar2_y, amean_43)


file = '/home/j/Desktop/recording/ts_8-7_Aserver.txt' 
ax65,ay65 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval_65 = [float(s) for s in line.split()]
		ax65.append(anumber_65)
		ay65.append(aval_65[0])
		anumber_65 = anumber_65+1

amean_65 = statistics.mean(ay65)
ast_dev_65 = statistics.pstdev(ay65)
amax_65 = max(ay65)

#xx65 = [1]
#yy65 = [mean_65]

bar3_x = np.append(bar3_x,[2])
bar3_y = np.append(bar3_y, amean_65)
#bar3_y = np.append(bar3_y,[0]) 

file = '/home/j/Desktop/recording/ts_9-8_Aserver.txt' 
ax87,ay87 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval_87 = [float(s) for s in line.split()]
		ax87.append(anumber_87)
		ay87.append(aval_87[0])
		anumber_87 = anumber_87+1

amean_87 = statistics.mean(ay87)
ast_dev_87 = statistics.pstdev(ay87)
amax_87 = max(ay87)

#xx87 = [1]
#yy87 = [mean_87]

bar4_x = np.append(bar4_x,[2])
bar4_y = np.append(bar4_y, amean_87)
#bar4_y = np.append(bar4_y, [0])
#print(yy21,yy43,yy65,yy87)

mnumber_21 = 1
mnumber_43 = 1
mnumber_65 = 1
mnumber_87 = 1

file = '/home/j/Desktop/recording/ts_5-4_Msub.txt' 
mx21,my21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval_21 = [float(s) for s in line.split()]
		mx21.append(mnumber_21)
		my21.append(mval_21[0])
		mnumber_21 = mnumber_21+1

mmean_21 = statistics.mean(my21)
mst_dev_21 = statistics.pstdev(my21)
mmax_21 = max(my21)

#xx21 = [1]
#yy21 = [mean_21]
bar1_x = np.append(bar1_x,[3])
bar1_y = np.append(bar1_y,mmean_21 )

file = '/home/j/Desktop/recording/ts_6-5_Msub.txt' 
mx43,my43 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval_43 = [float(s) for s in line.split()]
		mx43.append(mnumber_43)
		my43.append(mval_43[0])
		mnumber_43 = mnumber_43+1

mmean_43 = statistics.mean(my43)
mst_dev_43 = statistics.pstdev(my43)
mmax_43 = max(my43)

#xx43 = [1]
#yy43 = [mean_43]

bar2_x = np.append(bar2_x,[3])
bar2_y = np.append(bar2_y, mmean_43)

bar3_x = np.append(bar3_x,[3])
bar3_y = np.append(bar3_y, [0])

bar4_x = np.append(bar4_x,[3])
bar4_y = np.append(bar4_y, [0])

left = bar1_x
left = left*1.3
height1 = bar1_y
height2 = bar2_y
height3 = bar3_y
height4 = bar4_y

xaxis_val = ['Control Command', 'Alarming', 'Monitoring']
plt.xticks(left,xaxis_val)

print("")
print("In Factory Management")
print("=======Control Command=======\n"+chr(916)+"ts_54=", height1[0],'\n'+chr(916)+"ts_65=", height2[0],'\n'+chr(916)+"ts_87=", height3[0],'\n'+chr(916)+"ts_98=", height4[0])
print("=======    Alarming   =======\n"+chr(916)+"ts_54=", height1[1],'\n'+chr(916)+"ts_65=", height2[1],'\n'+chr(916)+"ts_87=", height3[1],'\n'+chr(916)+"ts_98=", height4[1])
print("=======   Monitoring  =======\n"+chr(916)+"pts_54=", height1[2],'\n'+chr(916)+"pts_65=", height2[2])
print("=============================\n")	

plt.rcParams['figure.figsize'] = (5,7)
#選擇要在下面的棒狀圖 blue 
bar1 = plt.bar(left, height1, color='blue')
#選擇要在上面的棒狀圖 red, yellow, green
bar2 = plt.bar(left, height2, bottom=height1, color='red')
bar3 = plt.bar(left, height3, bottom=height2+height1, color='yellow')
bar4 = plt.bar(left, height4, bottom=height3+height2+height1, color='green')
plt.legend((bar1[0], bar2[0], bar3[0], bar4[0]), (r'$\Delta$ts_54 \ $\Delta$pts_54', r'$\Delta$ts_65 \ $\Delta$pts_65', r'$\Delta$ts_87',r'$\Delta$ts_98'))

plt.xlim(0,5)
plt.ylim(0,0.006)
"""
plt.text(1, .0029, r'[ts_D-3]   $\mu=%0.9f$'%(mean_21)+'   $\sigma=%0.9f$'%(st_dev_21)+'    Max=%0.9f'%(max_21))
plt.text(1, .0027, r'[ts_4-D]   $\mu=%0.9f$'%(mean_43)+'   $\sigma=%0.9f$'%(st_dev_43)+'    Max=%0.9f'%(max_43))
plt.text(1, .0025, r'[ts_E-5]   $\mu=%0.9f$'%(mean_65)+'   $\sigma=%0.9f$'%(st_dev_65)+'    Max=%0.9f'%(max_65))
plt.text(1, .0028, r'[ts_6-E]   $\mu=%0.9f$'%(mean_87)+'   $\sigma=%0.9f$'%(st_dev_87)+'    Max=%0.9f'%(max_87))
plt.title('average execution delay')
"""

plt.show()



