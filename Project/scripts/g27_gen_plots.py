import os
import scipy.stats
import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt 
import matplotlib.cbook as cbook
from pylab import *
if not os.path.exists("../data"):
    os.makedirs("../data")

####################################################################


f=open('../data/g27_lab09data_01.csv','r')

x=[]
y1_step=[]
y1_loop=[]
iter_num=75
rerun=15
for i in range(iter_num) :
	sum_temp=0
	x.append(i+1)
	for j in range(rerun) :
		line=f.readline()
		#print(line.split()[2][:-1])
		sum_temp=sum_temp+float(line.split()[2][:-1])
	sum_temp=sum_temp/rerun
	y1_step.append(sum_temp)
f=open('../data/g27_lab09data_01.csv','r')
for i in range(iter_num) :
	sum_temp=0
	for j in range(rerun) :
		line=f.readline()
		#print(line.split()[6][:-1])
		sum_temp=sum_temp+float(line.split()[6][:-1])
	sum_temp=sum_temp/rerun
	y1_loop.append(sum_temp)
fig, p1 = plt.subplots()
p1.bar(x,y1_step,0.01, color='r',label="Steptime")
p1.plot(x,y1_loop,'g-',label="Loop time")
p1.set_title("Iteration number vs average steptime,loop time")    
p1.set_xlabel('Iteration Number')
p1.set_ylabel('Average step time/looptime')
p1.legend(loc='best')
fig.savefig('../data/g27_lab09_plot01.png')

####################################################################

f=open('../data/g27_lab09data_01.csv','r')

y2_step=y1_step
y2_col=[]
y2_vel=[]
y2_pos=[]
y2_avg_sum=[]
for i in range(iter_num) :
	sum_temp1=0
	sum_temp2=0
	sum_temp3=0
	sum_temp4=0
	for j in range(rerun) :
		line=f.readline()
		#print(line.split())
		sum_temp1=sum_temp1+float(line.split()[3][:-1])
		sum_temp2=sum_temp2+float(line.split()[4][:-1])
		sum_temp3=sum_temp3+float(line.split()[5][:-1])
	sum_temp1=sum_temp1/rerun
	sum_temp2=sum_temp2/rerun
	sum_temp3=sum_temp3/rerun
	sum_temp4=sum_temp1+sum_temp2+sum_temp3
	y2_col.append(sum_temp1)
	y2_vel.append(sum_temp2)
	y2_pos.append(sum_temp3)
	y2_avg_sum.append(sum_temp4)	

fig = plt.figure()
p2 = fig.add_subplot(111)
p2.set_title('Iteration number vs Average times')    
p2.set_xlabel('Iteration Number')
p2.set_ylabel('Average Times')
p2.plot(x,y2_step,'r',label='Step Time')
p2.plot(x,y2_col,'b-',label='Collision Time')
p2.plot(x,y2_vel,'g',label='Velocity Time')
p2.plot(x,y2_pos,'m',label='Position Time')
p2.plot(x,y2_avg_sum,'k',label='Total Time')
p2.legend()
fig.savefig('../data/g27_lab09_plot02.png')

####################################################################

yerror=[x/5 for x in y1_step]
fig = plt.figure()
p3 = fig.add_subplot(111)
p3.set_title("Iteration number vs Average Step Time")    
p3.set_xlabel('Iteration Number')
p3.set_ylabel('Average Step Time')
p3.errorbar(x,y1_step,yerror,c='b',label='Step Time')
p3.legend()
fig.savefig('../data/g27_lab09_plot03.png')

####################################################################

f=open('../data/g27_lab09data_01.csv','r')

x1=[]
y4_step=[]
roll=66
for i in range((roll-1)*rerun) :
	f.readline()
for j in range((roll-1)*rerun,roll*rerun) :
	#print(j)
	x1.append(j+1)
	line=f.readline()
	#print(line.split()[2][:-1])
	y4_step.append(float(line.split()[2][:-1]))
	
counts=[]
x2=[]
min_step=min(y4_step)
max_step=max(y4_step)
avg_step=min_step
bins=15
diff=(max_step-min_step)/bins
for i in range(bins+1) :
	counts.append(0)
	x2.append(avg_step)
	avg_step+=diff
#print(counts)
for i in range(len(y4_step)) :
	start_value=min_step
	for j in range(bins) :
		if(y4_step[i]<=start_value and y4_step[i]<start_value+diff) :
			counts[j]+=1
			start_value+=diff
print(diff)
#print(max_step)
#print(min_step)
#print(y4_step)
print(x2)
print(counts)

fig, p4 = plt.subplots()
p4.hist(y4_step,15,histtype='bar',color='r',label="Steptime")
#p4.plot(x2,counts,'r',label='Cumulative Frequency')
p4.set_title("Iteration number vs average steptime")    
p4.set_xlabel('Step Time')
p4.set_ylabel('Frequency')
p4.legend()
fig.savefig('../data/g27_lab09_plot04.png')
####################################################################

f=open('../data/g27_lab09data_random.csv','r')

y5_step=[]

random_num=15
for i in range(iter_num) :
	sum_temp=0
	for j in range(random_num) :
		line=f.readline()
		#print(line.split()[2][:-1])
		sum_temp=sum_temp+float(line.split()[2][:-1])
	sum_temp=sum_temp/rerun
	y5_step.append(sum_temp)
line1=polyfit(x,y5_step,1)
line2=polyfit(x,y1_step,1)
fit_fn1=poly1d(line1)
fit_fn2=poly1d(line2)
fig = plt.figure()
p5 = fig.add_subplot(111)
p5.set_title('Iteration number vs Average times')    
p5.set_xlabel('Iteration Number')
p5.set_ylabel('Average Times')
p5.plot(x,y5_step,'r-',x,fit_fn1(x),label='Step Time using random data')
p5.plot(x,y1_step,'m-',x,fit_fn2(x),label='Step Time using regular data')
p5.legend(loc='best')
fig.savefig('../data/g27_lab09_plot05.png')
