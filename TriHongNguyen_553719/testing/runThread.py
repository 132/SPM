# script result.txt "./sequantialization ../input/InputTest.txt 3 0 0 0 1"
# python2.7
import os
import subprocess
#import numpy as np
from operator import itemgetter

app = ["./threads", "./ff", "./seq"]
numberThread = ['6', '8']
inputFile = ["../input/Input100.txt"]
Func = ["10 1 2 3 4 5 6 7 8 9 10 11"]

#runCommand = app[0] + " " + numberThread[0] + " " + inputFile[0] + " " + Func[0]

listCommand = []
for iapp in range(0,len(app)):
	for ithread in range(0,len(numberThread)):
		if app[iapp] == './seq':
			runCommand = app[iapp] + " " + inputFile[0] + " " + Func[0]
			listCommand.append(runCommand)
			break
		else:	
			runCommand = app[iapp] + " " + numberThread[ithread] + " " + inputFile[0] + " " + Func[0]
			listCommand.append(runCommand)
	
		#runCommand = app[index] + " " + numberThread[index] + " " inputFile[index] + " " + Func[index]
			#	print(runCommand)

#print (runCommand)
print(listCommand)
#listCommand = list(set(listCommand)) 
#print(listCommand)
import commands
# import subprocess   # for python3
#print commands.getstatusoutput(runCommand)[1]



threadC = []
ffC = []
seqC = []
times = 3
farmC = []
"""
for icommand in range(0,len(listCommand)):
        total=0
        print(listCommand[icommand])
        for i in range(0,times):
        #       print(listCommand[icommand])
                tempOutput = commands.getstatusoutput(listCommand[icommand])[1]
        #       listRunning.append(tempOutput)
        #       print(tempOutput)
        #       print(tempOutput.rsplit(None, 1)[-1])
                total = total + float(tempOutput.rsplit(None, 1)[-1])

        check = listCommand[icommand].split(' ', 1)[0]
#       print(check)
        if check == './threads':
                threadC.append(total/times)
        elif check == './seq':
                seqC.append(total/times)
        elif check == './ff':
                ffC.append(total/times)
"""
for icommand in range(0,len(listCommand)):
        total=0
        print(listCommand[icommand])
	
	listNumber = []
	farmNumber = []
        for i in range(0,times):
		
        #       print(listCommand[icommand])
                tempOutput = commands.getstatusoutput(listCommand[icommand])[1]
        #       listRunning.append(tempOutput)
                print(tempOutput)
        #       print(tempOutput.rsplit(None, 1)[-1])
	#       total = total + float(tempOutput.rsplit(None, 1)[-1])
	#	print(tempOutput.split(' ', 1)[0])
		listNumber.append(float(tempOutput.rsplit(None, 1)[-1]))
		
		if listCommand[icommand].split(' ', 1)[0] == './threads':
			farmNumber.append(float(tempOutput.split(' ', 1)[0]))
	
        check = listCommand[icommand].split(' ', 1)[0]
#       print(check)
        if check == './threads':
                threadC.append(min(listNumber))
		#farmC.append(farmNumber[min(enumerate(listNumber), key=itemgetter(1))[0]]/(float(numberThread[icommand])-5))
		farmC.append(farmNumber[min(enumerate(listNumber), key=itemgetter(1))[0]])
        elif check == './seq':
                seqC.append(min(listNumber))
        elif check == './ff':
                ffC.append(min(listNumber))


print(threadC)
print(ffC)
for i in range(1, len(ffC)):
	seqC.append(seqC[0])
print(seqC)
print(farmC)

#modelCthread = [threadC[0]]
#modelFF = [ffC[0]]
#for i in range(0, len(numberThread)):
#	modelCthread.append(modelCthread[0]/

#thefile = open('test.txt', 'w')

#for item in threadC: 
#  print>>thefile, item

"""
with open('test.txt','w') as out_file:
	out_file.write('threadC = [')
	for item in threadC: 
		out_file.write("'%s'" % item)
	out_file.write(']')
"""

import matplotlib.pyplot as plt

#fig, ax = plt.subplots( nrows=1, ncols=1 )  # create figure & 1 axis
#ax.plot([0,1,2], [10,20,3])
#fig.savefig('to.png')   # save the figure to file
#plt.close(fig)    # close the figure


fig, bx = plt.subplots(nrows=1,ncols=1)

plt.xlabel('Number of Thread')
plt.ylabel('Compeletion Time')

bx.plot(numberThread, threadC, ls='--', label='C++Thread')
bx.plot(numberThread, ffC, ls='-', label='FF')
bx.plot(numberThread, seqC, ls=':', label='Seq')
bx.legend(['Thread', 'FF', 'Seq'], loc='upper right')

fig.savefig('graph/pow10.png')
plt.close(fig)
plt.show()


# os.system('script Thread_resutlt.txt -e')	# start script command
#for i in range(0,3):	# range start from 0 end at 2
#	os.system('./thread

# os.system('../thread 6 ../input/Input100.txt 3 0 0 0 1')
# os.system('exit') # exit script command
