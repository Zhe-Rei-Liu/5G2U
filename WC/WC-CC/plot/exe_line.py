import matplotlib.pyplot as plt
import statistics
import matplotlib.mlab as mlab
import numpy as np

number_1 = 1
number_2 = 1
number_3 = 1

scenario = input("Type the traffic scenario(basic, demo, thesis):")

if scenario != "basic":
	if scenario != "demo":
		if scenario != "thesis":
			print("Error scenario you type!!! Click bottom again!!!")
			os._exit()
# Control Command 執行延遲圖表繪製

file = '/home/lukelin/Desktop/recording/ts_2-1_CCclient.txt' 
x1,y1 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_21 = [float(s) for s in line.split()]
		x1.append(number_1)
		y1.append(val_21[0])
		number_1 = number_1+1

x1 = np.array(x1)
y1 = np.array(y1)

file = '/home/lukelin/Desktop/recording/ts_3-2_CCclient.txt' 
x2,y2 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_32 = [float(s) for s in line.split()]
		y2.append(val_32[0])
y2 = np.array(y2)		

file = '/home/lukelin/Desktop/recording/ts_5-4_CCserver.txt' 
x3,y3 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_54 = [float(s) for s in line.split()]
		y3.append(val_54[0])
y3 = np.array(y3)

file = '/home/lukelin/Desktop/recording/ts_7-5_CCserver.txt' 
x4,y4 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_65 = [float(s) for s in line.split()]
		y4.append(val_65[0])
y4.append(0)
y4 = np.array(y4)

file = '/home/lukelin/Desktop/recording/ts_8-7_CCserver.txt' 
x5,y5 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_87 = [float(s) for s in line.split()]
		y5.append(val_87[0])
y5.append(0)		
y5 = np.array(y5)	

file = '/home/lukelin/Desktop/recording/ts_9-8_CCserver.txt' 
x6,y6 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_98 = [float(s) for s in line.split()]
		y6.append(val_98[0])
y6.append(0)		
y6 = np.array(y6)	


file = '/home/lukelin/Desktop/recording/ts_11-10_CCclient.txt' 
x7,y7 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_1110 = [float(s) for s in line.split()]
		y7.append(val_1110[0])
y7.append(0)
y7 = np.array(y7)


file = '/home/lukelin/Desktop/recording/ts_12-11_CCclient.txt' 
x8,y8 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_1211 = [float(s) for s in line.split()]
		y8.append(val_1211[0])
y8.append(0)
y8 = np.array(y8)

x = np.array(x1)
ccy = y1+y2+y3+y4+y5+y6+y7+y8
ccy = ccy.tolist()

ccmean = statistics.mean(ccy)
ccst_dev = statistics.pstdev(ccy)
ccmax = max(ccy)
cccount = max(x1)

max_index = ccy.index(ccmax)
#print(max_index)
#print(y1[max_index] ,y2[max_index] ,y3[max_index] ,y4[max_index] ,y5[max_index] ,y6[max_index] ,y7[max_index] ,y8[max_index])
#print(len(y1),len(y2),len(y3),len(y4),len(y5),len(y6),len(y7),len(y8))
acount = max(x1)

ccmean_np = np.linspace(ccmean,ccmean,cccount)
ccmean_list = ccmean_np.tolist()

msg_num = 4570
plt.figure(figsize=(20, 10))
plt.subplot(3, 1, 1)
plt.plot(x1,ccy, marker = '.',linestyle = '-',label = 'Control Command Execution Latency')
#bar1 = plt.bar(x, y, color='blue')
plt.text(msg_num*0.6, .0305, r'$\mu=%0.9f$'%(ccmean)+'   $\sigma=%0.9f$'%(ccst_dev)+'    Max=%0.9f'%(ccmax),fontsize=14)
plt.plot(x1,ccmean_list, linestyle = '--',color = 'black', label = 'Avg. Control Command Execution Latency')
plt.xlim(0,msg_num)
plt.ylim(0,0.03)

plt.xlabel('Sequance number',fontsize=12)
plt.ylabel('Execution latency (second)',fontsize=12)
plt.legend(loc=2,fontsize=12)



# Alarming 執行延遲圖表繪製

file = '/home/lukelin/Desktop/recording/ts_2-1_Aclient.txt' 
x1,y1 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_21 = [float(s) for s in line.split()]
		x1.append(number_2)
		y1.append(val_21[0])
		number_2 = number_2+1

x1 = np.array(x1)
y1 = np.array(y1)

file = '/home/lukelin/Desktop/recording/ts_3-2_Aclient.txt' 
x2,y2 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_32 = [float(s) for s in line.split()]
		y2.append(val_32[0])
y2 = np.array(y2)		

file = '/home/lukelin/Desktop/recording/ts_5-4_Aserver.txt' 
x3,y3 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_54 = [float(s) for s in line.split()]
		y3.append(val_54[0])
y3 = np.array(y3)

file = '/home/lukelin/Desktop/recording/ts_7-5_Aserver.txt' 
x4,y4 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_65 = [float(s) for s in line.split()]
		y4.append(val_65[0])
y4.append(0)		
y4 = np.array(y4)

file = '/home/lukelin/Desktop/recording/ts_8-7_Aserver.txt' 
x5,y5 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_87 = [float(s) for s in line.split()]
		y5.append(val_87[0])
y5.append(0)		
y5 = np.array(y5)	

file = '/home/lukelin/Desktop/recording/ts_9-8_Aserver.txt' 
x6,y6 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_98 = [float(s) for s in line.split()]
		y6.append(val_98[0])
y6.append(0)		
y6 = np.array(y6)	


file = '/home/lukelin/Desktop/recording/ts_11-10_Aclient.txt' 
x7,y7 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_1110 = [float(s) for s in line.split()]
		y7.append(val_1110[0])
y7.append(0)
y7 = np.array(y7)


file = '/home/lukelin/Desktop/recording/ts_12-11_Aclient.txt' 
x8,y8 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_1211 = [float(s) for s in line.split()]
		y8.append(val_1211[0])
y8.append(0)
y8 = np.array(y8)

ax = np.array(x1)
ay = y1+y2+y3+y4+y5+y6+y7+y8
ay = ay.tolist()

amean = statistics.mean(ay)
ast_dev = statistics.pstdev(ay)
amax = max(ay)

max_index = ay.index(amax)
#print(max_index)
#print(y1[max_index] ,y2[max_index] ,y3[max_index] ,y4[max_index] ,y5[max_index], y6[max_index] ,y7[max_index] ,y8[max_index])
#print(len(y1),len(y2),len(y3),len(y4),len(y5),len(y6),len(y7),len(y8))
acount = max(x1)

amean_np = np.linspace(amean,amean,acount)
amean_list = amean_np.tolist()

msg_num = 2110
plt.subplot(3, 1, 2)
plt.plot(x1,ay, marker = '.',linestyle = '-',color = 'red',label = 'Warning Execution Latency')
#bar1 = plt.bar(x, y, color='blue')
plt.text(msg_num*0.6, .0305, r'$\mu=%0.9f$'%(amean)+'   $\sigma=%0.9f$'%(ast_dev)+'    Max=%0.9f'%(amax),fontsize=14)
plt.plot(x1,amean_list, linestyle = '--',color = 'black', label = 'Avg. Warning Execution Latency')
plt.xlim(0,msg_num)
plt.ylim(0,0.03)

plt.xlabel('Sequance number',fontsize=12)
plt.ylabel('Execution latency (second)',fontsize=12)
plt.legend(loc=2,fontsize=12)



# Monitoring 執行延遲圖表繪製

if scenario == "basic":
	file = '/home/lukelin/Desktop/recording/ts_2-1_Mpub.txt' 
	x1,y1 = [],[]
	with open(file,'r') as f:
		lines = f.readlines()
		for line in lines:
			val_21 = [float(s) for s in line.split()]
			x1.append(number_3)
			y1.append(val_21[0])
			number_3 = number_3+1

	x1 = np.array(x1)
	y1 = np.array(y1)

	file = '/home/lukelin/Desktop/recording/ts_3-2_Mpub.txt' 
	x2,y2 = [],[]
	with open(file,'r') as f:
		lines = f.readlines()
		for line in lines:
			val_32 = [float(s) for s in line.split()]
			y2.append(val_32[0])
	y2 = np.array(y2)		

	file = '/home/lukelin/Desktop/recording/ts_5-4_Msub.txt' 
	x3,y3 = [],[]
	with open(file,'r') as f:
		lines = f.readlines()
		for line in lines:
			val_54 = [float(s) for s in line.split()]
			y3.append(val_54[0])
	y3 = np.array(y3)

	file = '/home/lukelin/Desktop/recording/ts_6-5_Msub.txt' 
	x4,y4 = [],[]
	with open(file,'r') as f:
		lines = f.readlines()
		for line in lines:
			val_65 = [float(s) for s in line.split()]
			y4.append(val_65[0])
	y4 = np.array(y4)

else:
	file = '/home/lukelin/Desktop/recording/ts_2-1_Mpub_demo.txt' 
	x1,y1 = [],[]
	with open(file,'r') as f:
		lines = f.readlines()
		for line in lines:
			val_21 = [float(s) for s in line.split()]
			x1.append(number_3)
			y1.append(val_21[0])
			number_3 = number_3+1

	x1 = np.array(x1)
	y1 = np.array(y1)

	file = '/home/lukelin/Desktop/recording/ts_3-2_Mpub_demo.txt' 
	x2,y2 = [],[]
	with open(file,'r') as f:
		lines = f.readlines()
		for line in lines:
			val_32 = [float(s) for s in line.split()]
			y2.append(val_32[0])
	y2 = np.array(y2)		

	file = '/home/lukelin/Desktop/recording/ts_5-4_Msub_demo.txt' 
	x3,y3 = [],[]
	with open(file,'r') as f:
		lines = f.readlines()
		for line in lines:
			val_54 = [float(s) for s in line.split()]
			y3.append(val_54[0])
	y3 = np.array(y3)

	file = '/home/lukelin/Desktop/recording/ts_6-5_Msub_demo.txt' 
	x4,y4 = [],[]
	with open(file,'r') as f:
		lines = f.readlines()
		for line in lines:
			val_65 = [float(s) for s in line.split()]
			y4.append(val_65[0])
	y4 = np.array(y4)

#print(len(y1),len(y2),len(y3),len(y4))
mx = np.array(x1)
my = y1+y2+y3+y4
my = my.tolist()

mmean = statistics.mean(my)
mst_dev = statistics.pstdev(my)
mmax = max(my)
mcount = max(x1)

mmean_np = np.linspace(mmean,mmean,mcount)
mmean_list = mmean_np.tolist()

msg_num = len(y1)
plt.subplot(3, 1, 3)
plt.plot(x1,my, marker = '.',linestyle = '-',color = 'green' ,label = 'S.D Uploading Execution Latency')
#bar1 = plt.bar(x, y, color='blue')
plt.text(msg_num*0.6, .0305, r'$\mu=%0.9f$'%(mmean)+'   $\sigma=%0.9f$'%(mst_dev)+'    Max=%0.9f'%(mmax),fontsize=14)
plt.plot(x1,mmean_list, linestyle = '--',color = 'black', label = 'Avg. S.D Uploading Execution Latency')
plt.xlim(0,msg_num)
plt.ylim(0,0.03)

plt.xlabel('Sequance number',fontsize=12)
plt.ylabel('Execution latency (second)',fontsize=12)
plt.legend(loc=2,fontsize=12)

plt.subplots_adjust(left=0.125,
                    bottom=0.05, 
                    right=0.9, 
                    top=0.95, 
                    wspace=0.2, 
                    hspace=0.35)
plt.show()
#plt.savefig('command_client/server_exetime.png')

