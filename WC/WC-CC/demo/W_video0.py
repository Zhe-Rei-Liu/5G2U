import cv2

video1 = cv2.VideoCapture("/home/lukelin/Desktop/WC-CC/demo/SDU.mp4")
video2 = cv2.VideoCapture("/home/lukelin/Desktop/WC-CC/demo/SDU.mp4")
video3 = cv2.VideoCapture("/home/lukelin/Desktop/WC-CC/demo/WS.mp4")

video1.set(cv2.CAP_PROP_FPS, int(25))
video2.set(cv2.CAP_PROP_FPS, int(25))
video3.set(cv2.CAP_PROP_FPS, int(25))
bad = cv2.imread('/home/lukelin/Desktop/WC-CC/demo/broke.png')
fine = cv2.imread('/home/lukelin/Desktop/WC-CC/demo/health.png')

input_1 = '/home/lukelin/Desktop/result/output/WGCL_Mtt.txt'

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
	if(y[i] > 0.3):
		print("Message[%d] transmission time:%3f <<<<<< Error!!!!"%(x[i],y[i]))	
		error_count = error_count + 1
	if i%ratio==0:
		ret2, frame2 = video2.read()
		ret3, frame3 = video3.read()
		cv2.namedWindow("[WGCL] S.D Uploading", cv2.WINDOW_NORMAL)
		cv2.imshow("[WGCL] S.D Uploading", frame2)
		cv2.moveWindow("[WGCL] S.D Uploading",650,720)
		cv2.resizeWindow("[WGCL] S.D Uploading",600,300)
		
		cv2.namedWindow("[WGCL] Transmission Time", cv2.WINDOW_NORMAL)
		cv2.imshow("[WGCL] Transmission Time", frame3)
		cv2.moveWindow("[WGCL] Transmission Time",1250,720)
		cv2.resizeWindow("[WGCL] Transmission Time",600,300)
		"""
		if y[i] < 0.3:
			waitpara = 1
		else:
			waitpara = int(y[i]/0.3)*10 
		if cv2.waitKey(int(25*waitpara)) & 0xFF == ord('q'):
			break
		"""
		if cv2.waitKey(int(y[i]*1000)) & 0xFF == ord('q'):
			break
			
		if y[i] < 0.1:
			waitpara = 1
		else:
			waitpara = int(y[i]/0.1)	
		if cv2.waitKey(int(100*waitpara)) & 0xFF == ord('q'):
			break	

if float(error_count/i) < 0.1:
	cv2.imshow("[WGCL] S.D Uploading", fine)
else:
	cv2.imshow("[WGCL] S.D Uploading", bad)
cv2.moveWindow("[WGCL] S.D Uploading",650,720)
cv2.resizeWindow("[WGCL] S.D Uploading",600,300)
cv2.waitKey(0)							
#cv2.destroyAllWindows()
		
			
			

