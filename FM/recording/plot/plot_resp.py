import matplotlib.pyplot as plt
import statistics
import matplotlib.mlab as mlab
#import numpy as np

number_65 = 1
number_87 = 1

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


sum_resp=[]
for i in range(len(y65)):
    sum_value=y87[i]+y65[i]
    sum_resp.append(sum_value)
mean_sum = statistics.mean(sum_resp)
st_dev_sum = statistics.pstdev(sum_resp)
max_sum = max(sum_resp)

plt.figure(figsize=(15, 6))
plt.plot(x65,y65, marker = '.',linestyle = '-.',color = 'green',label = 'Server layer5->layer3')
plt.plot(x87,y87, marker = '.',linestyle = '--',label = 'Client layer3->layer5')
#plt.plot(x65,sum_resp, marker = '.',linestyle = '-',color = 'red',label = 'Execution time for response')
plt.xlim(-50,4050)
plt.ylim(0,0.006)
plt.text(2000, .005, r'[ts_8-7]   $\mu=%0.9f$'%(mean_87)+'   $\sigma=%0.9f$'%(st_dev_87)+'    Max=%0.9f'%(max_87))
plt.text(2000, .0055, r'[ts_6-5]   $\mu=%0.9f$'%(mean_65)+'   $\sigma=%0.9f$'%(st_dev_65)+'    Max=%0.9f'%(max_65))
#plt.text(4500, .0018, r'Sum   $\mu=%0.9f$'%(mean_sum)+'   $\sigma=%0.9f$'%(st_dev_sum)+'    Max=%0.9f'%(max_sum))
plt.xlabel('sequance number')
plt.ylabel('Execution time (second)')
plt.legend(loc=2)

#plt.show()
plt.savefig('Command_Resp_server_exetime.png')
