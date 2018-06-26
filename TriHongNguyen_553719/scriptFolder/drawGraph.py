# script result.txt "./sequantialization ../input/InputTest.txt 3 0 0 0 1"
# python2.7
import os
import subprocess
import matplotlib.pyplot as plt
"""
app = ["./threads", "./ff", "./seq"]
numberThread = ['5', '6', '8', '10', '12', '14']
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
for icommand in range(0,len(listCommand)):
	total=0
	print(listCommand[icommand])
	for i in range(0,times):
	#	print(listCommand[icommand])
		tempOutput = commands.getstatusoutput(listCommand[icommand])[1]
	#	listRunning.append(tempOutput)
	#	print(tempOutput)
	#	print(tempOutput.rsplit(None, 1)[-1])
		total = total + float(tempOutput.rsplit(None, 1)[-1])

	check = listCommand[icommand].split(' ', 1)[0]
#	print(check)
	if check == './threads':
		threadC.append(total/times)
	elif check == './seq':
		seqC.append(total/times)
	elif check == './ff':
		ffC.append(total/times)
print(threadC)
print(ffC)
for i in range(1, len(ffC)):
	seqC.append(seqC[0])
print(seqC)


import matplotlib.pyplot as plt

#fig, ax = plt.subplots( nrows=1, ncols=1 )  # create figure & 1 axis
#ax.plot([0,1,2], [10,20,3])
#fig.savefig('to.png')   # save the figure to file
#plt.close(fig)    # close the figure

"""

threadC = [0.4924603333333333, 0.8510240000000001, 0.706085, 0.5669776666666667, 0.5291476666666667, 0.485439] 
ffC = [0.513056, 0.504669, 0.506017, 0.5101316666666666, 0.5068573333333334, 0.504054]
seqC = [0.8888349999999999, 0.8888349999999999, 0.8888349999999999, 0.8888349999999999, 0.8888349999999999, 0.8888349999999999] 

numberThread =['5', '6', '8', '10', '12', '14'] 

fig, bx = plt.subplots(nrows=1,ncols=1)

plt.xlabel('Number of Thread')
plt.ylabel('Compeletion Time')

bx.plot(numberThread, threadC, ls='--', label='C++Thread')
bx.plot(numberThread, ffC, ls='-', label='FF')
bx.plot(numberThread, seqC, ls=':', label='Seq')
bx.legend(['Thread', 'FF', 'Seq'], loc='upper right')

fig.savefig('testingGraph.png')
plt.close(fig)
plt.show()


# os.system('script Thread_resutlt.txt -e')	# start script command
#for i in range(0,3):	# range start from 0 end at 2
#	os.system('./thread

# os.system('../thread 6 ../input/Input100.txt 3 0 0 0 1')
# os.system('exit') # exit script command
