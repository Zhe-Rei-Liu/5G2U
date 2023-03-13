import cv2
import matplotlib.pyplot as plt
import statistics
import matplotlib.mlab as mlab
import numpy as np
import imageio.v2 as imageio
import os

video1 = cv2.VideoCapture("/home/lukelin/Desktop/WC-CC/demo/warning.mp4")
video2 = cv2.VideoCapture("/home/lukelin/Desktop/WC-CC/demo/warning.mp4")

video1.set(cv2.CAP_PROP_FPS, int(25))
video2.set(cv2.CAP_PROP_FPS, int(25))

input_1 = '/home/lukelin/Desktop/result/output/AW-WGCL_Att.txt'

filenames = []
y = [] 
all_frames = []
frame_count = 0
ratio = 0
waitpara = 0
msg_num = 0
error_count = 0
num = 0

xbound = [0,2107]	
ybound = [0.03, 0.03]	

f = open(input_1)
with open(input_1,'r') as f:
	lines = f.readlines()
	for line in lines:
		val = [float(s) for s in line.split()]
		y.append(float(val[0]))		
		msg_num = msg_num + 1
	f.close()

while(True):
	ret1, frame1 = video1.read()
	if ret1 is False:
		break
	all_frames.append(frame1)
	frame_count = frame_count + 1
	
print(len(all_frames), " ", len(y), " ", frame_count)	

ratio = int(len(y)/frame_count) + 1
	
for i in range(0,len(y),ratio):
	plt.plot(y[:i],color = 'orange')
	plt.plot(xbound,ybound,linestyle = '--',color = 'red')
	plt.xlim(0,2107)
	plt.ylim(0,0.4)
	plt.title('Warning')
	plt.xlabel('Msg_number')
	plt.ylabel('Transmission Time')
	filename = f'W{i}.png'
	filenames.append(filename)
	plt.savefig(filename)
	plt.close()	
	
with imageio.get_writer('demo/AWW.mp4', mode='I') as writer:
	for filename in filenames:
		image = imageio.imread(filename)
		writer.append_data(image)
		
for filename in set(filenames):
	os.remove(filename)		

		
			
			

