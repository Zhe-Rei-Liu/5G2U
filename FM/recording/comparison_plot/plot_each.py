import matplotlib.pyplot as plt
import statistics
import matplotlib.mlab as mlab
#import numpy as np

number_21 = 1
number_43 = 1
number_65 = 1
number_87 = 1

pnumber_21 = 1
pnumber_43 = 1

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


summarization=[]
for i in range(len(y65)):
    summarization_value = y87[i]+y65[i]+y43[i]+y21[i]
    summarization.append(summarization_value)
mean_summarization = statistics.mean(summarization)
st_dev_summarization = statistics.pstdev(summarization)
max_summarization = max(summarization)


file = '/home/j/Desktop/recording/ts_2-1_pub.txt' 
xx21,yy21 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		pval_21 = [float(s) for s in line.split()]
		xx21.append(pnumber_21)
		yy21.append(pval_21[0])
		pnumber_21 = pnumber_21+1
mean_ps21 = statistics.mean(yy21)
st_dev_ps21 = statistics.pstdev(yy21)
max_ps21 = max(yy21)
min_ps21 = min(yy21)

file = '/home/j/Desktop/recording/ts_4-3_sub.txt' 
xx43,yy43 = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		pval_43 = [float(s) for s in line.split()]
		xx43.append(pnumber_43)
		yy43.append(pval_43[0])
		pnumber_43 = pnumber_43+1
mean_ps43 = statistics.mean(yy43)
st_dev_ps43 = statistics.pstdev(yy43)
max_ps43 = max(yy43)
min_ps43 = min(yy43)

file = '/home/j/Desktop/recording/decoding_sub.txt' 
dex,dey = [],[]
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		pval_43 = [float(s) for s in line.split()]
		xx43.append(pnumber_43)
		yy43.append(pval_43[0])
		pnumber_43 = pnumber_43+1
mean_ps43 = statistics.mean(yy43)
st_dev_ps43 = statistics.pstdev(yy43)
max_ps43 = max(yy43)
min_ps43 = min(yy43)

psummarization=[]
for i in range(len(y65)):
    psummarization_value = yy43[i]+yy21[i]
    psummarization.append(psummarization_value)
mean_psummarization = statistics.mean(psummarization)
st_dev_psummarization = statistics.pstdev(psummarization)
max_psummarization = max(psummarization)


plt.figure(figsize=(15, 6))
#plt.plot(x65,summarization, marker = '.',linestyle = '-.',color = 'purple',label = 'Client/Server processing delay')
#plt.plot(x65,psummarization, marker = '.',linestyle = '-',color = 'green',label = 'Pub/Sub processing delay')
#plt.plot(x65,y65, marker = '.',linestyle = '-.',color = 'green',label = 'Server layer5->layer3')
#plt.plot(x87,y87, marker = '.',linestyle = '--',label = 'Client layer3->layer5')
#plt.plot(x21,y21, marker = '.',linestyle = '-',label = 'Client layer5->layer3')
#plt.plot(x43,y43, marker = ',.',linestyle = '-.',color = 'green',label = 'Server layer3->layer5')
plt.plot(xx43,yy43, marker = '.',linestyle = '-.',color = 'pink',label = 'Subscriber layer3->layer5')
plt.plot(xx21,yy21, marker = '.',linestyle = '--',color = 'orange',label = 'Publisher layer5->layer3')
#plt.xlim(-50,4050)
#plt.ylim(0,0.006)
plt.xlim(-50,10005)
plt.ylim(0,0.001)
#plt.text(1780, .00575, r'Client/Server processing delay:    $\mu=%0.9f$'%(mean_summarization)+'   $\sigma=%0.9f$'%(st_dev_summarization)+'    Max=%0.9f'%(max_summarization))
#plt.text(1780, .0055, r'Pub/Sub processing delay:    $\mu=%0.9f$'%(mean_psummarization)+'   $\sigma=%0.9f$'%(st_dev_psummarization)+'    Max=%0.9f'%(max_psummarization))
#plt.text(1500, .000975, r'Server layer5->layer3 processing delay:    $\mu=%0.9f$'%(mean_65)+'   $\sigma=%0.9f$'%(st_dev_65)+'    Max=%0.9f'%(max_65))
#plt.text(1500, .000925, r'Client layer3->layer5 processing delay:    $\mu=%0.9f$'%(mean_87)+'   $\sigma=%0.9f$'%(st_dev_87)+'    Max=%0.9f'%(max_87))
#plt.text(1500, .000975, r'Client layer5->layer3 processing delay:    $\mu=%0.9f$'%(mean_21)+'   $\sigma=%0.9f$'%(st_dev_21)+'    Max=%0.9f'%(max_21))
#plt.text(1500, .000925, r'Server layer3->layer5 processing delay:    $\mu=%0.9f$'%(mean_43)+'   $\sigma=%0.9f$'%(st_dev_43)+'    Max=%0.9f'%(max_43))
plt.text(2200, .000975, r'Publisher layer5->layer3 processing delay:    $\mu=%0.9f$'%(mean_ps21)+'   $\sigma=%0.9f$'%(st_dev_ps21)+'    Max=%0.9f'%(max_ps21)+'    Min=%0.9f'%(min_ps21))
plt.text(2200, .000925, r'Subscriber layer3->layer5 processing delay:    $\mu=%0.9f$'%(mean_ps43)+'   $\sigma=%0.9f$'%(st_dev_ps43)+'    Max=%0.9f'%(max_ps43)+'    Min=%0.9f'%(min_ps43))

plt.xlabel('sequance number')
plt.ylabel('Processing Delay (second)')
plt.legend(loc=2)

plt.show()
