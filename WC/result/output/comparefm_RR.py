import numpy as np
import matplotlib.pyplot as plt
from matplotlib.pyplot import MultipleLocator
import statistics

ccnumber = 0
anumber = 0
mnumber = 0

cctotalWT = 0
atotalWT = 0
mtotalWT = 0
"""
計算WC window time
"""
x = np.arange(0,91,0.1)
x = x.tolist()

file = '/home/lukelin/Desktop/result/output/AW-WGCL_CCWT_2.txt' 
AW_ccwt_2 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		if ccnumber%20==0:
			ccval = [float(s) for s in line.split()]
			AW_ccwt_2.append(ccval[0])
			cctotalWT = cctotalWT + ccval[0]*100
		ccnumber = ccnumber + 1


file = '/home/lukelin/Desktop/result/output/AW-WGCL_AWT_2.txt' 
AW_awt_2 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		if anumber%20==0:
			aval = [float(s) for s in line.split()]
			AW_awt_2.append(aval[0])
			atotalWT = atotalWT + aval[0]*100
		anumber = anumber + 1

print("Percentage of Bandwidth Distributed by AW-WGCL:")
print("Control Command:",round(cctotalWT/90500.0,3),"% ||| Warning:",round(atotalWT/90500.0,3),"%")

ccnumber = 0
anumber = 0
mnumber = 0

cctotalWT = 0
atotalWT = 0
mtotalWT = 0

file = '/home/lukelin/Desktop/result/output/RR_CCWT_2.txt' 
W_ccwt_2 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		if ccnumber%20==0:
			ccval = [float(s) for s in line.split()]
			W_ccwt_2.append(ccval[0])
			cctotalWT = cctotalWT + ccval[0]*100
		ccnumber = ccnumber + 1


file = '/home/lukelin/Desktop/result/output/RR_AWT_2.txt' 
W_awt_2 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		if anumber%20==0:
			aval = [float(s) for s in line.split()]
			W_awt_2.append(aval[0])
			atotalWT = atotalWT + aval[0]*100
		anumber = anumber + 1

print("\nPercentage of Bandwidth Distributed by RR:")
print("Control Command:",round(cctotalWT/90500.0,3),"% ||| Warning:",round(atotalWT/90500.0,3),"%")

"""
繪製結果圖
"""


plt.figure(figsize=(20,10))
plt.subplot(2,1,1)
p1 = plt.plot(x, AW_ccwt_2,linestyle = '-',color = 'blue' ,label = 'AW-WGCL')
p2 = plt.plot(x, W_ccwt_2,linestyle = '-',color = 'red' ,label = 'RR')
x_major_locator = MultipleLocator(5)
ax = plt.gca()
ax.xaxis.set_major_locator(x_major_locator)
plt.xlim(0,91)
plt.ylim(0,1)
plt.title('Window Time Comparison of Control Command')
plt.xlabel('Time')
plt.ylabel('Window Time per TTI (ms)')
plt.legend(bbox_to_anchor=(1.005, 1.05))

plt.subplot(2,1,2)
p1 = plt.plot(x, AW_awt_2,linestyle = '-',color = 'blue' ,label = 'AW-WGCL')
p2 = plt.plot(x, W_awt_2,linestyle = '-',color = 'red' ,label = 'RR')
x_major_locator = MultipleLocator(5)
ax = plt.gca()
ax.xaxis.set_major_locator(x_major_locator)
plt.xlim(0,91)
plt.ylim(0,1)
plt.title('Window Time Comparison of Warning')
plt.xlabel('Time')
plt.ylabel('Window Time per TTI (ms)')
plt.legend(bbox_to_anchor=(1.09, 1.05))

plt.subplots_adjust(left=0.05,
                    bottom=0.05, 
                    right=0.92, 
                    top=0.92, 
                    wspace=0.2, 
                    hspace=0.6)
                    
plt.show()
