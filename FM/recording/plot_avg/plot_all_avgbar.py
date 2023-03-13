import numpy as np
import matplotlib.pyplot as plt
import statistics

ccnumber_21 = 1
ccnumber_32 = 1
ccnumber_54 = 1
ccnumber_65 = 1
ccnumber_87 = 1
ccnumber_98 = 1
ccnumber_1110 = 1
ccnumber_1211 = 1

file = '/home/j/Desktop/recording/ts_2-1_CCclient.txt' 
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



bar1_x = np.array([1])
bar1_y = np.array([ccmean_21]) 

file = '/home/j/Desktop/recording/ts_3-2_CCclient.txt' 
ccx32,ccy32 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval_32 = [float(s) for s in line.split()]
		ccx32.append(ccnumber_32)
		ccy32.append(ccval_32[0])
		ccnumber_32 = ccnumber_32+1

ccmean_32 = statistics.mean(ccy32)
ccst_dev_32 = statistics.pstdev(ccy32)
ccmax_32 = max(ccy32)



bar2_x = np.array([1])
bar2_y = np.array([ccmean_32]) 

file = '/home/j/Desktop/recording/ts_5-4_CCserver.txt' 
ccx54,ccy54 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval_54 = [float(s) for s in line.split()]
		ccx54.append(ccnumber_54)
		ccy54.append(ccval_54[0])
		ccnumber_54 = ccnumber_54+1

ccmean_54 = statistics.mean(ccy54)
ccst_dev_54 = statistics.pstdev(ccy54)
ccmax_54 = max(ccy54)


bar3_x = np.array([1])
bar3_y = np.array([ccmean_54]) 

file = '/home/j/Desktop/recording/ts_6-5_CCserver.txt' 
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



bar4_x = np.array([1])
bar4_y = np.array([ccmean_65]) 


file = '/home/j/Desktop/recording/ts_8-7_CCserver.txt' 
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



bar5_x = np.array([1])
bar5_y = np.array([ccmean_87]) 
#bar3_y = np.append(bar3_y,[0]) 

file = '/home/j/Desktop/recording/ts_9-8_CCserver.txt' 
ccx98,ccy98 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval_98 = [float(s) for s in line.split()]
		ccx98.append(ccnumber_98)
		ccy98.append(ccval_98[0])
		ccnumber_98 = ccnumber_98+1

ccmean_98 = statistics.mean(ccy98)
ccst_dev_98 = statistics.pstdev(ccy98)
ccmax_98 = max(ccy98)



bar6_x = np.array([1])
bar6_y = np.array([ccmean_98]) 
#bar4_y = np.append(bar4_y, [0])
#print(yy21,yy43,yy65,yy87)

file = '/home/j/Desktop/recording/ts_11-10_CCclient.txt' 
ccx1110,ccy1110 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval_1110 = [float(s) for s in line.split()]
		ccx1110.append(ccnumber_1110)
		ccy1110.append(ccval_1110[0])
		ccnumber_1110 = ccnumber_1110+1

ccmean_1110 = statistics.mean(ccy1110)
ccst_dev_1110 = statistics.pstdev(ccy1110)
ccmax_1110 = max(ccy1110)


bar7_x = np.array([1])
bar7_y = np.array([ccmean_1110]) 


file = '/home/j/Desktop/recording/ts_12-11_CCclient.txt' 
ccx1211,ccy1211 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		ccval_1211 = [float(s) for s in line.split()]
		ccx1211.append(ccnumber_1211)
		ccy1211.append(ccval_1211[0])
		ccnumber_1211 = ccnumber_1211+1

ccmean_1211 = statistics.mean(ccy1211)
ccst_dev_1211 = statistics.pstdev(ccy1211)
ccmax_1211 = max(ccy1211)


bar8_x = np.array([1])
bar8_y = np.array([ccmean_1211]) 

anumber_21 = 1
anumber_32 = 1
anumber_54 = 1
anumber_65 = 1
anumber_87 = 1
anumber_98 = 1
anumber_1110 = 1
anumber_1211 = 1

file = '/home/j/Desktop/recording/ts_2-1_Aclient.txt' 
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


bar1_x = np.append(bar1_x,[2])
bar1_y = np.append(bar1_y,amean_21 )

file = '/home/j/Desktop/recording/ts_3-2_Aclient.txt' 
ax32,ay32 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval_32 = [float(s) for s in line.split()]
		ax32.append(anumber_32)
		ay32.append(aval_32[0])
		anumber_32 = anumber_32+1

amean_32 = statistics.mean(ay32)
ast_dev_32 = statistics.pstdev(ay32)
amax_32 = max(ay32)


bar2_x = np.append(bar2_x,[2])
bar2_y = np.append(bar2_y,amean_32 )

file = '/home/j/Desktop/recording/ts_5-4_Aserver.txt' 
ax54,ay54 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval_54 = [float(s) for s in line.split()]
		ax54.append(anumber_54)
		ay54.append(aval_54[0])
		anumber_54 = anumber_54+1

amean_54 = statistics.mean(ay54)
ast_dev_54 = statistics.pstdev(ay54)
amax_54 = max(ay54)


bar3_x = np.append(bar3_x,[2])
bar3_y = np.append(bar3_y,amean_54 )

file = '/home/j/Desktop/recording/ts_6-5_Aserver.txt' 
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



bar4_x = np.append(bar4_x,[2])
bar4_y = np.append(bar4_y,amean_65 )


file = '/home/j/Desktop/recording/ts_8-7_Aserver.txt' 
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


bar5_x = np.append(bar5_x,[2])
bar5_y = np.append(bar5_y,amean_87 )
#bar3_y = np.append(bar3_y,[0]) 

file = '/home/j/Desktop/recording/ts_9-8_Aserver.txt' 
ax98,ay98 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval_98 = [float(s) for s in line.split()]
		ax98.append(anumber_98)
		ay98.append(aval_98[0])
		anumber_98 = anumber_98+1

amean_98 = statistics.mean(ay98)
ast_dev_98 = statistics.pstdev(ay98)
amax_98 = max(ay98)


bar6_x = np.append(bar6_x,[2])
bar6_y = np.append(bar6_y,amean_98 )
#bar4_y = np.append(bar4_y, [0])
#print(yy21,yy43,yy65,yy87)

file = '/home/j/Desktop/recording/ts_11-10_Aclient.txt' 
ax1110,ay1110 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval_1110 = [float(s) for s in line.split()]
		ax1110.append(anumber_1110)
		ay1110.append(aval_1110[0])
		anumber_1110 = anumber_1110+1

amean_1110 = statistics.mean(ay1110)
ast_dev_1110 = statistics.pstdev(ay1110)
amax_1110 = max(ay1110)

bar7_x = np.append(bar7_x,[2])
bar7_y = np.append(bar7_y,amean_1110 )


file = '/home/j/Desktop/recording/ts_12-11_Aclient.txt' 
ax1211,ay1211 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		aval_1211 = [float(s) for s in line.split()]
		ax1211.append(anumber_1211)
		ay1211.append(aval_1211[0])
		anumber_1211 = anumber_1211+1

amean_1211 = statistics.mean(ay1211)
ast_dev_1211 = statistics.pstdev(ay1211)
amax_1211 = max(ay1211)


bar8_x = np.append(bar8_x,[2])
bar8_y = np.append(bar8_y,amean_1211 )


mnumber_21 = 1
mnumber_32 = 1
mnumber_54 = 1
mnumber_65 = 1

file = '/home/j/Desktop/recording/ts_2-1_Mpub.txt' 
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

bar1_x = np.append(bar1_x,[3])
bar1_y = np.append(bar1_y,mmean_21 )

file = '/home/j/Desktop/recording/ts_3-2_Mpub.txt' 
mx32,my32 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval_32 = [float(s) for s in line.split()]
		mx32.append(mnumber_32)
		my32.append(mval_32[0])
		mnumber_32 = mnumber_32+1

mmean_32 = statistics.mean(my32)
mst_dev_32 = statistics.pstdev(my32)
mmax_32 = max(my32)


bar2_x = np.append(bar2_x,[3])
bar2_y = np.append(bar2_y, mmean_32)

file = '/home/j/Desktop/recording/ts_5-4_Msub.txt' 
mx54,my54 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval_54 = [float(s) for s in line.split()]
		mx54.append(mnumber_54)
		my54.append(mval_54[0])
		mnumber_54 = mnumber_54+1

mmean_54 = statistics.mean(my54)
mst_dev_54 = statistics.pstdev(my54)
mmax_54 = max(my54)


bar3_x = np.append(bar3_x,[3])
bar3_y = np.append(bar3_y, mmean_54)

file = '/home/j/Desktop/recording/ts_6-5_Msub.txt' 
mx65,my65 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		mval_65 = [float(s) for s in line.split()]
		mx65.append(mnumber_65)
		my65.append(mval_65[0])
		mnumber_65 = mnumber_65+1

mmean_65 = statistics.mean(my65)
mst_dev_65 = statistics.pstdev(my65)
mmax_65 = max(my65)


bar4_x = np.append(bar4_x,[3])
bar4_y = np.append(bar4_y, mmean_65)

bar5_x = np.append(bar5_x,[3])
bar5_y = np.append(bar5_y, 0)

bar6_x = np.append(bar6_x,[3])
bar6_y = np.append(bar6_y, 0)

bar7_x = np.append(bar7_x,[3])
bar7_y = np.append(bar7_y, 0)

bar8_x = np.append(bar8_x,[3])
bar8_y = np.append(bar8_y, 0)

left = bar1_x
left = left*1.3
height1 = bar1_y
height2 = bar2_y
height3 = bar3_y
height4 = bar4_y
height5 = bar5_y
height6 = bar6_y
height7 = bar7_y
height8 = bar8_y

labels = bar1_y + bar2_y + bar3_y + bar4_y + bar5_y + bar6_y + bar7_y + bar8_y

def createLabels(data,x):
    for item in data:      
        print(item)
        plt.text(
            x, 
            item+0.00003, 
            '%f' % float(item),
            ha = "center",
            va = "bottom",
        )
        x = x+1.3


plt.figure(figsize=(9, 6))
xaxis_val = ['Control Command', 'Alarming', 'Monitoring']
plt.xticks(left,xaxis_val)

#print("")
#print("Total Execution delay")
#print("=======Control Command=======\n"+chr(916)+"ts_54=", height1[0],'\n'+chr(916)+"ts_65=", height2[0],'\n'+chr(916)+"ts_87=", height3[0],'\n'+chr(916)+"ts_98=", height4[0])
#print("=======    Alarming   =======\n"+chr(916)+"ts_54=", height1[1],'\n'+chr(916)+"ts_65=", height2[1],'\n'+chr(916)+"ts_87=", height3[1],'\n'+chr(916)+"ts_98=", height4[1])
#print("=======   Monitoring  =======\n"+chr(916)+"pts_54=", height1[2],'\n'+chr(916)+"pts_65=", height2[2])
#print("=============================\n")	

#選擇要在下面的棒狀圖 blue 
bar1 = plt.bar(left, height1, color='deepskyblue')
#選擇要在上面的棒狀圖 red, yellow, green
bar2 = plt.bar(left, height2, bottom=height1, color='lightcoral')
bar3 = plt.bar(left, height3, bottom=height2+height1, color='lawngreen')
bar4 = plt.bar(left, height4, bottom=height3+height2+height1, color='yellow')
bar5 = plt.bar(left, height5, bottom=height4+height3+height2+height1, color='navy')
bar6 = plt.bar(left, height6, bottom=height5+height4+height3+height2+height1, color='maroon')
bar7 = plt.bar(left, height7, bottom=height6+height5+height4+height3+height2+height1, color='darkgreen')
bar8 = plt.bar(left, height8, bottom=height7+height6+height5+height4+height3+height2+height1, color='goldenrod')
plt.legend((bar1[0], bar2[0], bar3[0], bar4[0], bar5[0], bar6[0], bar7[0], bar8[0]), (r'$\Delta$ts_21 \ $\Delta$pts_21', r'$\Delta$ts_32 \ $\Delta$pts_32', r'$\Delta$ts_54 \ $\Delta$pts_54', r'$\Delta$ts_65 \ $\Delta$pts_65', r'$\Delta$ts_87',r'$\Delta$ts_98',r'$\Delta$ts_1110',r'$\Delta$ts_1211'))

createLabels(labels,1.3)

plt.title("Analysis of Execution Latency",fontsize=16)
plt.xlim(0,6)
plt.ylim(0,0.01)


plt.show()



