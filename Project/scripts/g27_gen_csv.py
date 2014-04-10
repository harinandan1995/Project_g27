import os
import subprocess
import random
if not os.path.exists("../data"):
    os.makedirs("../data")
filename=open('../data/g27_lab09data_01.csv','w')
final=""
for i in range(150) :
	for j in range(50) :
		final=str(i+1)+", "+str(j+1)+", "
		name = "../mybins/cs296_exe_27 "+str(i+1)+" > output.txt"
		os.system(name)		
		with open('output.txt') as lines :
			w_help=0
			for line in lines :
				for w in line.split() :
					#print(w)
					if w[0].isdigit() :
						#print(w)
						if w_help>=1 :
							final=final+w+", "
						w_help+=1
		final=final[:-2]
		#print(final)
		filename.write(final+"\n")
os.system("rm -r -f output.txt")

filename=open('../data/g27_lab09data_random.csv','w')
final=""
for i in range(150) :
	rand=sorted(random.sample(range(1,51),15))
	for j in rand :
		final=str(i+1)+", "+str(j+1)+", "
		name = "../mybins/cs296_exe_27 "+str(i+1)+" > output.txt"
		os.system(name)		
		with open('output.txt') as lines :
			for line in lines :
				for w in line.split() :
					if w[0].isdigit() and not w.isdigit() :
						final=final+w+", "
		final=final[:-2]
		#print(final)
		filename.write(final+"\n")
os.system("rm -r -f output.txt")
	#print()
