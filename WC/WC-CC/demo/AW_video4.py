import cv2

video1 = cv2.VideoCapture("/home/lukelin/Desktop/WC-CC/demo/warning.mp4")
video2 = cv2.VideoCapture("/home/lukelin/Desktop/WC-CC/demo/warning.mp4")
video3 = cv2.VideoCapture("/home/lukelin/Desktop/WC-CC/demo/AWW.mp4")

video1.set(cv2.CAP_PROP_FPS, int(25))
video2.set(cv2.CAP_PROP_FPS, int(25))
video3.set(cv2.CAP_PROP_FPS, int(25))
bad = cv2.imread('/home/lukelin/Desktop/WC-CC/demo/broke.png')
fine = cv2.imread('/home/lukelin/Desktop/WC-CC/demo/health.png')

input_1 = '/home/lukelin/Desktop/result/output/AW-WGCL_Att.txt'

x = []
y = [] 
all_frames = []
frame_count = 0
ratio = 0
waitpara = 0
msg_num = 1
error_count = 0

f = open(input_1)
with open(input_1,'r') as f:
	lines = f.readlines()
	for line in lines:
		val = [float(s) for s in line.split()]
		x.append(msg_num)
		y.append(float(val[0]))		
		msg_num = msg_num + 1
	f.close()

while(True):
	ret1, frame1 = video1.read()
	if ret1 is False:
		break
	all_frames.append(frame1)
	frame_count = frame_count + 1
	
print(len(all_frames), " ", len(x), " ", frame_count)	

ratio = int(len(x)/frame_count) + 1


for i in range(len(x)):
	if(y[i] > 0.03):
		print("Message[%d] transmission time:%3f <<<<<< Error!!!!"%(x[i],y[i]))	
		error_count = error_count + 1
	if i%ratio==0:
		ret2, frame2 = video2.read()
		ret3, frame3 = video3.read()
		cv2.namedWindow("[AW-WGCL] Warning", cv2.WINDOW_NORMAL)
		cv2.imshow("[AW-WGCL] Warning", frame2)
		cv2.moveWindow("[AW-WGCL] Warning",650,370)
		cv2.resizeWindow("[AW-WGCL] Warning",600,300)
		
		cv2.namedWindow("[AW-WGCL] Transmission Time", cv2.WINDOW_NORMAL)
		cv2.imshow("[AW-WGCL] Transmission Time", frame3)
		cv2.moveWindow("[AW-WGCL] Transmission Time",1250,370)
		cv2.resizeWindow("[AW-WGCL] Transmission Time",600,300)
		
		if y[i] < 0.03:
			waitpara = 1
		else:
			waitpara = int(y[i]/0.03)*10 
		if cv2.waitKey(int(30*waitpara)) & 0xFF == ord('q'):
			break
			
if float(error_count/i) < 0.001:
	cv2.imshow("[AW-WGCL] Warning", fine)
else:
	cv2.imshow("[AW-WGCL] Warning", bad)
cv2.moveWindow("[AW-WGCL] Warning",650,370)
cv2.resizeWindow("[AW-WGCL] Warning",600,300)
cv2.waitKey(0)							
#cv2.destroyAllWindows()
		
			
			

