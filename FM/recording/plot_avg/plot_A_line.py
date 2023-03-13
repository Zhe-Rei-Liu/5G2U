import matplotlib.pyplot as plt
import statistics
import matplotlib.mlab as mlab
import numpy as np

number_2 = 1


file = '/home/j/Desktop/recording/ts_2-1_Aclient.txt' 
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

file = '/home/j/Desktop/recording/ts_3-2_Aclient.txt' 
x2,y2 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_32 = [float(s) for s in line.split()]
		y2.append(val_32[0])
y2 = np.array(y2)		

file = '/home/j/Desktop/recording/ts_5-4_Aserver.txt' 
x3,y3 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_54 = [float(s) for s in line.split()]
		y3.append(val_54[0])
y3 = np.array(y3)

file = '/home/j/Desktop/recording/ts_6-5_Aserver.txt' 
x4,y4 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_65 = [float(s) for s in line.split()]
		y4.append(val_65[0])
y4 = np.array(y4)

file = '/home/j/Desktop/recording/ts_8-7_Aserver.txt' 
x5,y5 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_87 = [float(s) for s in line.split()]
		y5.append(val_87[0])
y5.append(0)		
y5 = np.array(y5)	

file = '/home/j/Desktop/recording/ts_9-8_Aserver.txt' 
x6,y6 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_98 = [float(s) for s in line.split()]
		y6.append(val_98[0])
y6.append(0)		
y6 = np.array(y6)	


file = '/home/j/Desktop/recording/ts_11-10_Aclient.txt' 
x7,y7 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_1110 = [float(s) for s in line.split()]
		y7.append(val_1110[0])
y7.append(0)
y7 = np.array(y7)


file = '/home/j/Desktop/recording/ts_12-11_Aclient.txt' 
x8,y8 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_1211 = [float(s) for s in line.split()]
		y8.append(val_1211[0])
y8.append(0)
y8 = np.array(y8)

x = np.array(x1)
y = y1+y2+y3+y4+y5+y6+y7+y8
y = y.tolist()

mean = statistics.mean(y)
st_dev = statistics.pstdev(y)
maxval = max(y)
count = max(x1)

mean_np = np.linspace(mean,mean,count)
mean_list = mean_np.tolist()

plt.figure(figsize=(15, 6))
plt.plot(x1,y, marker = '.',linestyle = '-',color = 'red' ,label = 'Alarming Execution Latency')
#bar1 = plt.bar(x, y, color='blue')
plt.text(1250, .0095, r'$\mu=%0.9f$'%(mean)+'   $\sigma=%0.9f$'%(st_dev)+'    Max=%0.9f'%(maxval))
plt.plot(x1,mean_list, linestyle = '--',color = 'black', label = 'Avg. Alarming Execution Latency')
plt.xlim(0,2020)
plt.ylim(0,0.01)

plt.xlabel('Sequance number')
plt.ylabel('Execution latency (second)')
plt.legend(loc=2)

plt.show()
#plt.savefig('command_client/server_exetime.png')

