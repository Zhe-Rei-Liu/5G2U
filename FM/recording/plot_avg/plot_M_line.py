import matplotlib.pyplot as plt
import statistics
import matplotlib.mlab as mlab
import numpy as np

number_3 = 1

file = '/home/j/Desktop/recording/ts_2-1_Mpub.txt' 
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

file = '/home/j/Desktop/recording/ts_3-2_Mpub.txt' 
x2,y2 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_32 = [float(s) for s in line.split()]
		y2.append(val_32[0])
y2 = np.array(y2)		

file = '/home/j/Desktop/recording/ts_5-4_Msub.txt' 
x3,y3 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_54 = [float(s) for s in line.split()]
		y3.append(val_54[0])
y3 = np.array(y3)

file = '/home/j/Desktop/recording/ts_6-5_Msub.txt' 
x4,y4 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_65 = [float(s) for s in line.split()]
		y4.append(val_65[0])
y4 = np.array(y4)

print(len(y1),len(y2),len(y3),len(y4))
mx = np.array(x1)
my = y1+y2+y3+y4
my = my.tolist()

mmean = statistics.mean(my)
mst_dev = statistics.pstdev(my)
mmax = max(my)
mcount = max(x1)

mmean_np = np.linspace(mmean,mmean,mcount)
mmean_list = mmean_np.tolist()

plt.figure(figsize=(15, 6))
plt.plot(x1,my, marker = '.',linestyle = '-',color = 'green' ,label = 'Monitoring Execution Latency')
#bar1 = plt.bar(x, y, color='blue')
plt.text(1250, .0115, r'$\mu=%0.9f$'%(mmean)+'   $\sigma=%0.9f$'%(mst_dev)+'    Max=%0.9f'%(mmax))
plt.plot(x1,mmean_list, linestyle = '--',color = 'black', label = 'Avg. Monitoring Execution Latency')
plt.xlim(0,2020)
plt.ylim(0,0.012)

plt.xlabel('Sequance number')
plt.ylabel('Execution latency (second)')
plt.legend(loc=2)

plt.show()
#plt.savefig('command_client/server_exetime.png')

