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

file = '/home/j/Desktop/recording/ts_4-3_server.txt' 
x43,y43 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		val_43 = [float(s) for s in line.split()]
		x43.append(number_43)
		y43.append(val_43[0])
		number_43 = number_43+1

sum_req=[]
for i in range(len(y21)):
    sum_val=y21[i]+y43[i]
    sum_req.append(sum_val)		
mean_sum_req = statistics.mean(sum_req)
st_dev_sum_req = statistics.pstdev(sum_req)
max_sum_req = max(sum_req)

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
mean_sum_resp = statistics.mean(sum_resp)
st_dev_sum_resp = statistics.pstdev(sum_resp)
max_sum_resp = max(sum_resp)


plt.figure(figsize=(15, 6))
plt.plot(x21,sum_req, marker = '.',linestyle = ':',color = 'orange',label = 'Execution time for request')
plt.plot(x65,sum_resp, marker = '.',linestyle = ':',color = 'pink',label = 'Execution time for response')
plt.xlim(-50,4050)
plt.ylim(0,0.006)
plt.text(2000, .0055, r'Execution time for Req     $\mu=%0.9f$'%(mean_sum_req)+'   $\sigma=%0.9f$'%(st_dev_sum_req)+'    Max=%0.9f'%(max_sum_req))
plt.text(2000, .005, r'Execution time for Resp    $\mu=%0.9f$'%(mean_sum_resp)+'   $\sigma=%0.9f$'%(st_dev_sum_resp)+'    Max=%0.9f'%(max_sum_resp))
plt.xlabel('sequance number')
plt.ylabel('Execution time (second)')
plt.legend(loc=2)

#plt.show()
plt.savefig('Command_ReqResp_exetime.png')



