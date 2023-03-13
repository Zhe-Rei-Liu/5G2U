import matplotlib.pyplot as plt
import statistics
import matplotlib.mlab as mlab
#import numpy as np

number_21 = 1
number_43 = 1

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

sum_req=[]
for i in range(len(y21)):
    sum_value=y21[i]+y43[i]
    sum_req.append(sum_value)
mean_sum = statistics.mean(sum_req)
st_dev_sum = statistics.pstdev(sum_req)
max_sum = max(sum_req)


plt.figure(figsize=(15, 6))
plt.plot(x21,y21, marker = '.',linestyle = '-',label = 'Client layer5->layer3')
plt.plot(x43,y43, marker = '.',linestyle = '-.',color = 'green',label = 'Server layer3->layer5')
#plt.plot(x21,sum_req, marker = '.',linestyle = '-',color = 'red',label = 'Execution time for request')
plt.xlim(-50,4050)
plt.ylim(0,0.006)
plt.text(2000, .0055, r'[ts_2-1]   $\mu=%0.9f$'%(mean_21)+'   $\sigma=%0.9f$'%(st_dev_21)+'    Max=%0.9f'%(max_21))
plt.text(2000, .005, r'[ts_4-3]   $\mu=%0.9f$'%(mean_43)+'   $\sigma=%0.9f$'%(st_dev_43)+'    Max=%0.9f'%(max_43))
#plt.text(5500, .0018, r'Sum   $\mu=%0.9f$'%(mean_sum)+'   $\sigma=%0.9f$'%(st_dev_sum)+'    Max=%0.9f'%(max_sum))
plt.xlabel('sequance number')
plt.ylabel('Execution time (second)')
plt.legend(loc=2)

#plt.show()
plt.savefig('Command_Req_client_exetime.png')
