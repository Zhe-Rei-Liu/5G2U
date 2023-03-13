# -*- coding: utf-8 -*-
import tkinter as tk
import subprocess
from PIL import ImageTk, Image

window = tk.Tk()
window.title("Tool")
window.geometry('400x300')
window.configure(bg='white')

var = tk.StringVar()  # 这是文字变量存储器
l = tk.Label(window, textvariable=var, bg='grey', font=('Arial', 12), width=30, height=3)
l.pack()
l.place(x=60,y=20)


on_hit = False  # 默认初始状态为False

def radiobutton_event1(widget):
    global selection
    selection = 'light'
    
def radiobutton_event2(widget):
	global selection
	selection = 'heavy'

def hit_me1():
    global on_hit
    if on_hit == False:  # 从False状态变成True状态
        #on_hit = True
        var.set('Packet Captured !!!')  
        subprocess.run(["./capture.sh"])
    else:  # 从True状态变成False状态
        on_hit = False
        var.set('')  # 设置文字为空   
        
def hit_me2():
	global on_hit
	if on_hit == False:  # 从False状态变成True状态
		#on_hit = True
		if selection == 'light':
			var.set('Clear CPU Loading!!!')  
			subprocess.run(["./cpu_lightload.sh"])
		elif selection == 'heavy':
			var.set('Clear CPU Loading!!!')  
			subprocess.run(["./cpu_heavyload.sh"])
	else:  # 从True状态变成False状态
		on_hit = False
		var.set('')  # 设置文字为空          
        
photo1=tk.PhotoImage(file='icons/tshark.gif')
canvas1 = tk.Canvas(window, width=70, height=70)
canvas1.create_image(0, 0, anchor='nw', image=photo1)   # 在 Canvas 中放入圖片
canvas1.pack()
canvas1.place(x=50,y=120)
canvas1.config(highlightthickness=0)
b1 = tk.Button(window, anchor='n',text='tshark', bg="snow3", fg="black", width=5, height=1, font=('Arial', 10), command=hit_me1)
b1.pack()
b1.place(x=50,y=190)

myradiobutton1 = tk.Radiobutton(window, text='Light Load   (30%)', font=('Arial', 10),variable=var, value='CPU Light Load (30%)',width=18, height=1,command=lambda:radiobutton_event1(myradiobutton1))
myradiobutton1.pack()
myradiobutton1.place(x=230,y=200)
myradiobutton2 = tk.Radiobutton(window, text='Heavy Load (90%)', font=('Arial', 10),variable=var, value='CPU Heavy Load (90%)',width=18, height=1,command=lambda:radiobutton_event2(myradiobutton2))
myradiobutton2.pack()
myradiobutton2.place(x=230,y=220)

photo2=tk.PhotoImage(file='icons/cpu.gif')
canvas2 = tk.Canvas(window, width=110, height=100)
canvas2.create_image(0, 0, anchor='nw', image=photo2)   # 在 Canvas 中放入圖片
canvas2.pack()
canvas2.place(x=250,y=100)
canvas2.config(highlightthickness=0)

b2 = tk.Button(window, text='Create Stress', bg="snow3", fg="black", font=('Arial', 10), width=10, height=1, command=hit_me2)
b2.pack()
b2.place(x=258,y=242)

window.mainloop()
