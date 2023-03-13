import numpy as np
import matplotlib.pyplot as plt
from matplotlib.pyplot import MultipleLocator
import statistics

ccnumber = 0
anumber = 0
mnumber = 0

cctotalWT_1 = 0
atotalWT_1 = 0
mtotalWT_1 = 0

cctotalWT_2 = 0
atotalWT_2 = 0
mtotalWT_2 = 0
"""
計算WC window time
"""
x = np.arange(0,91,0.1)
x = x.tolist()

file = '/home/lukelin/Desktop/result/output/AW-WGCL_CCWT_1.txt' 
AW_ccwt_1 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		if ccnumber%20==0:
			ccval = [float(s) for s in line.split()]
			AW_ccwt_1.append(ccval[0])
			cctotalWT_1 = cctotalWT_1 + ccval[0]*100
		ccnumber = ccnumber + 1


file = '/home/lukelin/Desktop/result/output/AW-WGCL_AWT_1.txt' 
AW_awt_1 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		if anumber%20==0:
			aval = [float(s) for s in line.split()]
			AW_awt_1.append(aval[0])
			atotalWT_1 = atotalWT_1 + aval[0]*100
		anumber = anumber + 1

file = '/home/lukelin/Desktop/result/output/AW-WGCL_MWT.txt' 
AW_mwt = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		if mnumber%20==0:
			mval = [float(s) for s in line.split()]
			AW_mwt.append(mval[0])
			mtotalWT_1 = mtotalWT_1 + mval[0]*100
		mnumber = mnumber +1
print("Percentage of Bandwidth Distributed by AW-WGCL:")
print("Control Command:",round(cctotalWT_1/90500.0,3),"% ||| Warning:",round(atotalWT_1/90500.0,3),"% ||| S.D Uploading:",round(mtotalWT_1/90500.0,3),"%")

ccnumber = 0
anumber = 0
mnumber = 0


file = '/home/lukelin/Desktop/result/output/LCP_CCWT_1.txt' 
W_ccwt_1 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		if ccnumber%20==0:
			ccval = [float(s) for s in line.split()]
			W_ccwt_1.append(ccval[0])
			cctotalWT_2 = cctotalWT_2 + ccval[0]*100
		ccnumber = ccnumber + 1


file = '/home/lukelin/Desktop/result/output/LCP_AWT_1.txt' 
W_awt_1 = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		if anumber%20==0:
			aval = [float(s) for s in line.split()]
			W_awt_1.append(aval[0])
			atotalWT_2 = atotalWT_2 + aval[0]*100
		anumber = anumber + 1


file = '/home/lukelin/Desktop/result/output/LCP_MWT.txt' 
W_mwt = []
with open(file,'r') as f:
	lines = f.readlines()
	for line in lines:
		if mnumber%20==0:
			mval = [float(s) for s in line.split()]
			W_mwt.append(mval[0])
			mtotalWT_2 = mtotalWT_2 + mval[0]*100
		mnumber = mnumber +1
print("\nPercentage of Bandwidth Distributed by LCP:")
print("Control Command:",round(cctotalWT_2/90500.0,3),"% ||| Warning:",round(atotalWT_2/90500.0,3),"% ||| S.D Uploading:",round(mtotalWT_2/90500.0,3),"%")

"""
繪製結果圖
"""


plt.figure(figsize=(20,10))
plt.subplot(3,1,1)
p1 = plt.plot(x, AW_ccwt_1,linestyle = '-',color = 'blue' ,label = 'AW-WGCL')
p2 = plt.plot(x, W_ccwt_1,linestyle = '-',color = 'red' ,label = 'LCP')
x_major_locator = MultipleLocator(5)
ax = plt.gca()
ax.xaxis.set_major_locator(x_major_locator)
plt.xlim(0,91)
plt.ylim(0,1)
plt.title('Window Time Comparison of Control Command',fontsize=14)
plt.xlabel('Time',fontsize=12)
plt.ylabel('Window Time per TTI (ms)',fontsize=12)
plt.text(91, 0.7 , '--------Avg. BW--------',fontsize=10)
plt.text(91, 0.6 , 'AW-WGCL: %0.3f%%'%(cctotalWT_1/90500.0*100.0),fontsize=10)
plt.text(91, 0.5 , 'LCP: %0.3f%%'%(cctotalWT_2/90500.0*100.0),fontsize=10)
plt.text(91, 0.4 , '----------------------------',fontsize=10)
plt.legend(bbox_to_anchor=(1.09, 1.05),fontsize=9)

plt.subplot(3,1,2)
p1 = plt.plot(x, AW_awt_1,linestyle = '-',color = 'blue' ,label = 'AW-WGCL')
p2 = plt.plot(x, W_awt_1,linestyle = '-',color = 'red' ,label = 'LCP')
x_major_locator = MultipleLocator(5)
ax = plt.gca()
ax.xaxis.set_major_locator(x_major_locator)
plt.xlim(0,91)
plt.ylim(0,1)
plt.title('Window Time Comparison of Warning',fontsize=14)
plt.xlabel('Time',fontsize=12)
plt.ylabel('Window Time per TTI (ms)',fontsize=12)
plt.text(91, 0.7 , '--------Avg. BW--------',fontsize=10)
plt.text(91, 0.6 , 'AW-WGCL: %0.3f%%'%(atotalWT_1/90500.0*100.0),fontsize=10)
plt.text(91, 0.5 , 'LCP: %0.3f%%'%(atotalWT_2/90500.0*100.0),fontsize=10)
plt.text(91, 0.4 , '----------------------------',fontsize=10)
plt.legend(bbox_to_anchor=(1.09, 1.05),fontsize=9)

plt.subplot(3,1,3)
p1 = plt.plot(x, AW_mwt,linestyle = '-',color = 'blue' ,label = 'AW-WGCL')
p2 = plt.plot(x, W_mwt,linestyle = '-',color = 'red' ,label = 'LCP')
x_major_locator = MultipleLocator(5)
ax = plt.gca()
ax.xaxis.set_major_locator(x_major_locator)
plt.xlim(0,91)
plt.ylim(0,1)
plt.title('Window Time Comparison of S.D Uploading',fontsize=14)
plt.xlabel('Time',fontsize=12)
plt.ylabel('Window Time per TTI (ms)',fontsize=12)
plt.text(91, 0.7 , '--------Avg. BW--------',fontsize=10)
plt.text(91, 0.6 , 'AW-WGCL: %0.3f%%'%(mtotalWT_1/90500.0*100.0),fontsize=10)
plt.text(91, 0.5 , 'LCP: %0.3f%%'%(mtotalWT_2/90500.0*100.0),fontsize=10)
plt.text(91, 0.4 , '----------------------------',fontsize=10)
plt.legend(bbox_to_anchor=(1.09, 1.05),fontsize=9)


plt.subplots_adjust(left=0.05,
                    bottom=0.05, 
                    right=0.92, 
                    top=0.92, 
                    wspace=0.2, 
                    hspace=0.6)
                    
plt.show()
