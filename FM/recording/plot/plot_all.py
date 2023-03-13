import matplotlib.pyplot as plt
import statistics
import matplotlib.mlab as mlab
#import numpy as np

number_21 = 1
number_43 = 1
number_65 = 1
number_87 = 1

file = '/home/j/Desktop/recording/ts_2-1_client.txt' 
x21,y21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_21 = [float(s) for s in line.split()]
		x21.append(number_21)
		y21.append(val_21[0])
		number_21 = number_21+1

mean_21 = statistics.mean(y21)
st_dev_21 = statistics.pstdev(y21)
max_21 = max(y21)


file = '/home/j/Desktop/recording/ts_4-3_server.txt' 
x43,y43 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_43 = [float(s) for s in line.split()]
		x43.append(number_43)
		y43.append(val_43[0])
		number_43 = number_43+1

mean_43 = statistics.mean(y43)
st_dev_43 = statistics.pstdev(y43)
max_43 = max(y43)

file = '/home/j/Desktop/recording/ts_8-7_client.txt' 
x87,y87 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_87 = [float(s) for s in line.split()]
		x87.append(number_87)
		y87.append(val_87[0])
		number_87 = number_87+1

mean_87 = statistics.mean(y87)
st_dev_87 = statistics.pstdev(y87)
max_87 = max(y87)


file = '/home/j/Desktop/recording/ts_6-5_server.txt' 
x65,y65 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_65 = [float(s) for s in line.split()]
		x65.append(number_65)
		y65.append(val_65[0])
		number_65 = number_65+1

mean_65 = statistics.mean(y65)
st_dev_65 = statistics.pstdev(y65)
max_65 = max(y65)


plt.figure(figsize=(15, 6))
plt.plot(x21,y21, marker = '.',linestyle = '-',label = 'Client layer5->layer3')
plt.plot(x43,y43, marker = '.',linestyle = ':',color = 'green',label = 'Server layer3->layer5')
plt.plot(x87,y87, marker = '.',linestyle = '-',color = 'cyan',label = 'Client layer3->layer5')
plt.plot(x65,y65, marker = '.',linestyle = ':',color = 'olive',label = 'Server layer5->layer3')
plt.xlim(0,4050)
plt.ylim(0,0.003)
plt.text(2000, .0028, r'[ts_2-1]   $\mu=%0.9f$'%(mean_21)+'   $\sigma=%0.9f$'%(st_dev_21)+'    Max=%0.9f'%(max_21))
plt.text(2000, .0026, r'[ts_4-3]   $\mu=%0.9f$'%(mean_43)+'   $\sigma=%0.9f$'%(st_dev_43)+'    Max=%0.9f'%(max_43))
plt.text(2000, .0024, r'[ts_8-7]   $\mu=%0.9f$'%(mean_87)+'   $\sigma=%0.9f$'%(st_dev_87)+'    Max=%0.9f'%(max_87))
plt.text(2000, .0022, r'[ts_6-5]   $\mu=%0.9f$'%(mean_65)+'   $\sigma=%0.9f$'%(st_dev_65)+'    Max=%0.9f'%(max_65))
plt.xlabel('sequance number')
plt.ylabel('Execution time (second)')
plt.legend(loc=2)

plt.show()
#plt.savefig('command_client/server_exetime.png')
