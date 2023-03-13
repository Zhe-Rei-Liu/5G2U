import numpy as np
import matplotlib
import matplotlib.pyplot as plt

input_1 = '/home/lukelin/Desktop/WC-CC/ana_traffic_WC.txt'
x1=[]
y1=[]
time1 = 0

input_2 = '/home/lukelin/Desktop/WC-CC/ana_traffic_FM.txt'
x2=[]
y2=[]
time2 = 0

f = open(input_1)
with open(input_1,'r') as f:
	lines = f.readlines()
	for line in lines:
		val = [int(s) for s in line.split()]
		y1.append(float(val[0]/5000000))		
		x1.append(int(time1))
		time1 = time1 + 1
	f.close()
	
f = open(input_2)
with open(input_2,'r') as f:
	lines = f.readlines()
	for line in lines:
		val = [int(s) for s in line.split()]
		y2.append(float(val[0]/1500000))		
		x2.append(int(time2))
		time2 = time2 + 1
	f.close()	

fig = plt.figure(figsize=(8, 10), dpi=80)
fig.patch.set_facecolor('silver')
fig.canvas.manager.set_window_title('BW utilization')

plt.style.use('classic')
# 打开交互模式
plt.ion()

# 循环
for index in range(0,len(y1)+1,1):
    # 清除原有图像
    plt.cla()
	
    plt.subplots_adjust(left=0.125,
   					bottom=0.05, 
                    right=0.9, 
                    top=0.95, 
                    wspace=0.2, 
                    hspace=0.35)
	
    plt.subplot(2, 1, 1)
    # 设定标题等
    plt.title("WC Bandwidth Utilization (Total is 500Mbps)")
    plt.grid(True)

    # 生成测试数据


    # 设置X轴
    plt.xlabel("Time (sec)")
    plt.xlim(0,index)

    # 设置Y轴
    plt.ylabel("Percentage of WC Bandwidth Utilization (%)")
    plt.ylim(0,100)

    # 画曲线
   
    plt.plot(x1[:index], y1[:index], "b.-",markersize="8", linewidth=2.0)
    
    plt.subplot(2, 1, 2)
    # 设定标题等
    plt.title("FM Bandwidth Utilization (Total is 150Mbps)")
    plt.grid(True)

    # 生成测试数据


    # 设置X轴
    plt.xlabel("Time (sec)")
    plt.xlim(0,index)

    # 设置Y轴
    plt.ylabel("Percentage of FM Bandwidth Utilization (%)")
    plt.ylim(0,100)

    # 画曲线
    
    plt.plot(x2[:index], y2[:index], "r.-",markersize="8", linewidth=2.0)
    # 暂停
    plt.pause(0.1)

# 关闭交互模式
plt.ioff()

# 图形显示
plt.show()


