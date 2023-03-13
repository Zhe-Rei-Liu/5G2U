# -*- coding: utf-8 -*-
import tkinter as tk
import subprocess
import os
import matplotlib.pyplot as plt
import statistics
import matplotlib.mlab as mlab
import numpy as np

from PIL import ImageTk, Image

window = tk.Tk()
window.title("Work Cell Simulator")
window.geometry('750x670')
window.configure(bg='white')

var = tk.StringVar()  # 这是文字变量存储器
l = tk.Label(window, textvariable=var, bg='grey', font=('Arial', 12), width=40, height=4)
l.pack()
l.place(x=20,y=5)

def radiobutton_event1(widget):
    global selection
    selection = 'bar'
    
def radiobutton_event2(widget):
	global selection
	selection = 'line'
	
def radiobutton_event3(widget):
    global selection_1
    selection_1 = 'WGCL'
    
def radiobutton_event4(widget):
	global selection_1
	selection_1 = 'LCP'	
"""	
def radiobutton_event5(widget):
	global selection_1
	selection_1 = 'RR'		
"""
on_hit = False  # 默认初始状态为False

def hit_me():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True
        var.set('OPC UA is running!!!')  
        subprocess.run(["./run_all.sh"])
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空
        
def hit_me1():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True 
        subprocess.run(["./traffic_heavy"])
        subprocess.run(["./PCP_tagger"])
        var.set('TSN header is added !!!') 
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空 
        
def hit_me2():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True
        subprocess.run(["./Translator"])
        var.set('5G header is added !!!')
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空      
        
def hit_me3():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True  
        subprocess.run(["./RRC_SRLCC"])
        var.set('Logic channels are configured !!!')
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空     
        
def hit_me4():
	global on_hit
	if on_hit == False:  # 从False状态变成True状态
		subprocess.run(["./txt_pass.sh"])
		if selection == 'bar':
			var.set('Avg. Bar Chart is ploted!!!')
			os.system('python3 plot/exe_avgbar.py')
		elif selection == 'line':
			var.set('Line Chart is ploted!!!')
			os.system('python3 plot/exe_line.py')
	else:  # 从True状态变成False状态
		on_hit = False
		var.set('')  # 设置文字为空        
		
def hit_me5():
	global on_hit
	if on_hit == False:  # 从False状态变成True状态
		subprocess.run(["./../result/trans_time"])
		var.set('Line chart of APP. QoS is ploted!!!')
		os.system('python3 ../result/output/plot_trans_time.py')
	else:  # 从True状态变成False状态
		on_hit = False
		var.set('')  # 设置文字为空  
				
def hit_me6():
	global on_hit
	if on_hit == False:  # 从False状态变成True状态
		subprocess.run(["./../result/trans_time"])
		var.set('Histogram of APP. QoS is ploted!!!')
		os.system('python3 ../result/output/hist_trans_time.py')
	else:  # 从True状态变成False状态
		on_hit = False
		var.set('')  # 设置文字为空  	
		
def hit_me7():
	global on_hit
	if on_hit == False:  # 从False状态变成True状态
		#subprocess.run(["./../result/trans_time"])
		if selection_1 == 'WGCL':
			var.set('Comparison of bandwidth allocation is ploted!!!')
			os.system('python3 ../result/output/comparewc_WGCL.py')
		elif selection_1 == 'LCP':
			var.set('Comparison of bandwidth allocation is ploted!!!')
			os.system('python3 ../result/output/comparewc_LCP.py')
		#elif selection_1 == 'RR':
			#var.set('Comparison of bandwidth allocation is ploted!!!')
			#os.system('python3 ../result/output/comparewc_RR.py')
	else:  # 从True状态变成False状态
		on_hit = False
		var.set('')  # 设置文字为空 		
		
def hit_me8():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True
        var.set('Demo of AW-WGCL is prepared !!!')  
        subprocess.run(["./pre_AW_WGCL.sh"])
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空			   
        
def hit_me9():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True
        var.set('Demo of WGCL is prepared !!!')  
        subprocess.run(["./pre_WGCL.sh"])
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空	  
        
def hit_me10():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True
        var.set('Demo of LCP is prepared !!!')  
        subprocess.run(["./pre_LCP.sh"])
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空	

def hit_me11():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True
        var.set('Video of AW-WGCL is played !!!')  
        subprocess.run(["./AW_WGCL.sh"])
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空	  

def hit_me12():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True
        var.set('Video of WGCL is played !!!')  
        subprocess.run(["./WGCL.sh"])
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空	         
        
def hit_me13():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True
        var.set('Video of LCP is played !!!')  
        subprocess.run(["./LCP.sh"])
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空	 

def hit_me14():
	global on_hit  
	if on_hit == False:  # 从False状态变成True状态
		subprocess.run(["./ttxt_pass.sh"])
		subprocess.run(["./cal_traffic"])
		var.set('BW Utilization Chart is ploted!!!')
		os.system('python3 demo/ana_traffic.py')
	else:  # 从True状态变成False状态
		on_hit = False
		var.set('')  # 设置文字为空                                     
        
line1=tk.PhotoImage(file='icons/line1.gif')    
line2=tk.PhotoImage(file='icons/line2.gif')            

canvas1 = tk.Canvas(window, width=2, height=50)
canvas1.create_image(0, 0, anchor='c', image=line1)   # 在 Canvas 中放入圖片
canvas1.pack()
canvas1.place(x=560,y=100)

canvas2 = tk.Canvas(window, width=2, height=50)
canvas2.create_image(0, 0, anchor='c', image=line1)   # 在 Canvas 中放入圖片
canvas2.pack()
canvas2.place(x=560,y=280)

canvas3 = tk.Canvas(window, width=300, height=2)
canvas3.create_image(0, 0, anchor='c', image=line2)   # 在 Canvas 中放入圖片
canvas3.pack()
canvas3.place(x=280,y=465)


#		Blocks			
photo1=tk.PhotoImage(file='icons/Program.gif')
b1 = tk.Button(window,image=photo1, text='Work Cell',font=('Arial', 12, 'bold'),compound='top', bg="black", fg="white", width=275, height=80, command=hit_me)
b1.pack()
b1.place(x=415,y=15)

photo2=tk.PhotoImage(file='icons/PCP.gif')
l1 = tk.Label(window,image = photo2, anchor='n', text='PCP Tagger',compound='bottom', bg='maroon',font=('Arial', 12, 'bold'), width=120, height=130)
l1.pack()
l1.place(x=508,y=150)
b2 = tk.Button(window, text='IEEE 802.1Q',font=('Arial', 12, 'bold'), bg="dark green", fg="white", width=9, height=1, command=hit_me1)
b2.pack()
b2.place(x=515,y=243)

photo3=tk.PhotoImage(file='icons/5QI.gif')
l2 = tk.Label(window,image = photo3, anchor='n', text='Translator',compound='bottom', bg='red4',font=('Arial', 12, 'bold'), width=120, height=155)
l2.pack()
l2.place(x=508,y=330)
b3 = tk.Button(window, text='TS 23.501',font=('Arial', 12, 'bold'), bg="forest green", fg="white", width=8, height=1, command=hit_me2)
b3.pack()
b3.place(x=518,y=450)

l3 = tk.Label(window, anchor='n', text='WC UE', bg='darkorange',font=('Arial', 12, 'bold'), width=13, height=5)
l3.pack()
l3.place(x=180,y=390)
b4 = tk.Button(window, text='Priority\nHandling',font=('Arial', 12, 'bold'), bg="SpringGreen4", fg="white", width=8, height=2, command=hit_me3)
b4.pack()
b4.place(x=190,y=432)

photo4=tk.PhotoImage(file='icons/UE.gif')
canvas4 = tk.Canvas(window, width=60, height=50)
canvas4.create_image(0, 0, anchor='nw', image=photo4)   # 在 Canvas 中放入圖片
canvas4.pack()
canvas4.place(x=170,y=340)
canvas4.config(highlightthickness=0)

photo5=tk.PhotoImage(file='icons/communication.gif')
canvas5 = tk.Canvas(window, width=90, height=65)
canvas5.create_image(0, 0, anchor='nw', image=photo5)   # 在 Canvas 中放入圖片
canvas5.pack()
canvas5.place(x=120,y=270)
canvas5.config(highlightthickness=0)

photo6=tk.PhotoImage(file='icons/timer.gif')
canvas6 = tk.Canvas(window, width=45, height=45)
canvas6.create_image(0, 0, anchor='nw', image=photo6)   # 在 Canvas 中放入圖片
canvas6.pack()
canvas6.place(x=380,y=120)
canvas6.config(highlightthickness=0)

l4 = tk.Label(window, anchor='n', text='OPC UA Excution Delay', bg='white',font=('Arial', 10, 'bold'), width=24, height=1)
l4.pack()
l4.place(x=315,y=110)

myradiobutton1 = tk.Radiobutton(window, text='Avg. Bar Chart ', font=('Arial', 10),variable=var, value='Avg. Bar Chart', width=15, height=1,command=lambda:radiobutton_event1(myradiobutton1))
myradiobutton1.pack()
myradiobutton1.place(x=335,y=166)
myradiobutton2 = tk.Radiobutton(window, text='Line Chart        ', font=('Arial', 10),variable=var, value='Line Chart', width=15, height=1,command=lambda:radiobutton_event2(myradiobutton2))
myradiobutton2.pack()
myradiobutton2.place(x=335,y=186)

b5 = tk.Button(window, text='Plot', bg="snow3", fg="black", font=('Arial', 10), width=8, height=1, command=hit_me4)
b5.pack()
b5.place(x=360,y=207)

photo7=tk.PhotoImage(file='icons/PC.gif')
canvas7 = tk.Canvas(window, width=75, height=55)
canvas7.create_image(0, 0, anchor='nw', image=photo7)   # 在 Canvas 中放入圖片
canvas7.pack()
canvas7.place(x=45,y=580)
canvas7.config(highlightthickness=0)

l5 = tk.Label(window, anchor='n', text='Performance Analyze', bg='white',font=('Arial', 10, 'bold'), width=20, height=1)
l5.pack()
l5.place(x=15,y=560)

b5 = tk.Button(window, text='Bar Chart', bg="snow3", fg="black", font=('Arial', 10), width=8, height=1, command=hit_me5)
b5.pack()
b5.place(x=160,y=565)

b6 = tk.Button(window, text='Histogram', bg="snow3", fg="black", font=('Arial', 10), width=8, height=1, command=hit_me6)
b6.pack()
b6.place(x=160,y=610)


myradiobutton3 = tk.Radiobutton(window, text='    vs WGCL       ', font=('Arial', 10),variable=var, value='vs WGCL', width=15, height=1,command=lambda:radiobutton_event3(myradiobutton3))
myradiobutton3.pack()
myradiobutton3.place(x=265,y=570)
myradiobutton4 = tk.Radiobutton(window, text='    vs LCP           ', font=('Arial', 10),variable=var, value='vs LCP', width=15, height=1,command=lambda:radiobutton_event4(myradiobutton4))
myradiobutton4.pack()
myradiobutton4.place(x=265,y=590)
#myradiobutton5 = tk.Radiobutton(window, text='      vs RR              ', font=('Arial', 8),variable=var, value='vs RR',command=lambda:radiobutton_event5(myradiobutton5))
#myradiobutton5.pack()
#myradiobutton5.place(x=280,y=600)

b7 = tk.Button(window, text='BW Comparison', bg="snow3", fg="black", font=('Arial', 10), width=12, height=1, command=hit_me7)
b7.pack()
b7.place(x=275,y=612)

l6 = tk.Label(window, anchor='n', text='Video Demo', bg='white',font=('Arial', 10, 'bold'), width=18, height=1)
l6.pack()
l6.place(x=410,y=562)

photo8=tk.PhotoImage(file='icons/video.gif')
canvas8 = tk.Canvas(window, width=50, height=45)
canvas8.create_image(0, 0, anchor='nw', image=photo8)   # 在 Canvas 中放入圖片
canvas8.pack()
canvas8.place(x=450,y=590)
canvas8.config(highlightthickness=0)

b8 = tk.Button(window, text='AW-WGCL', bg="black", fg="white", font=('Arial', 10, 'bold'), width=9, height=2, command=hit_me8)
b8.pack()
b8.place(x=530,y=518)

b9 = tk.Button(window, text='WGCL', bg="black", fg="white", font=('Arial', 10, 'bold'), width=9, height=2, command=hit_me9)
b9.pack()
b9.place(x=530,y=568)

b10 = tk.Button(window, text='LCP', bg="black", fg="white", font=('Arial', 10, 'bold'), width=9, height=2, command=hit_me10)
b10.pack()
b10.place(x=530,y=618)

photo9=tk.PhotoImage(file='icons/play.gif')
b11 = tk.Button(window,image=photo9, bg="snow3",command=hit_me11)
b11.pack()
b11.place(x=620,y=520)

b12 = tk.Button(window,image=photo9, bg="snow3",command=hit_me12)
b12.pack()
b12.place(x=620,y=570)

b13 = tk.Button(window,image=photo9, bg="snow3",command=hit_me13)
b13.pack()
b13.place(x=620,y=620)

photo10=tk.PhotoImage(file='icons/analyze.gif')
canvas10 = tk.Canvas(window, width=50, height=50)
canvas10.create_image(0, 0, anchor='nw', image=photo10)   # 在 Canvas 中放入圖片
canvas10.pack()
canvas10.place(x=215,y=135)
canvas10.config(highlightthickness=0)

l7 = tk.Label(window, anchor='n', text='BW Utilization', bg='white',font=('Arial', 10, 'bold'), width=20, height=1)
l7.pack()
l7.place(x=170,y=110)

b14 = tk.Button(window, text='Plot', bg="snow3", fg="black", font=('Arial', 10), width=8, height=1, command=hit_me14)
b14.pack()
b14.place(x=200,y=185)

window.mainloop()
