import numpy as np
import matplotlib
import matplotlib.pyplot as plt

input_1 = '/home/lukelin/Desktop/WC-CC/ana_traffic.txt'
x=[]
y=[]
time = 0

f = open(input_1)
with open(input_1,'r') as f:
	lines = f.readlines()
	for line in lines:
		val = [int(s) for s in line.split()]
		y.append(float(val[0]/500000000))		
		x.append(int(time))
		time = time + 1
	f.close()
print(len(y))

fig = plt.figure(figsize=(8, 6), dpi=80)
fig.patch.set_facecolor('silver')
fig.canvas.set_window_title('BW utilization')

plt.style.use('classic')
# 打开交互模式
plt.ion()

# 循环
for index in range(0,len(y)+1,1):
    # 清除原有图像
    plt.cla()

    # 设定标题等
    plt.title("WC Bandwidth Utilization (Total is 500Mbps)")
    plt.grid(True)

    # 生成测试数据


    # 设置X轴
    plt.xlabel("Time (sec)")
    plt.xlim(0,index)

    # 设置Y轴
    plt.ylabel("Percentage of Bandwidth Utilization (%)")
    plt.ylim(0,1)

    # 画曲线
    plt.plot(x[:index], y[:index], "b.-",markersize="8", linewidth=2.0)
    # 暂停
    plt.pause(0.1)

# 关闭交互模式
plt.ioff()

# 图形显示
plt.show()


