# script result.txt "./sequantialization ../input/InputTest.txt 3 0 0 0 1"
# python2.7
import os
import subprocess


app = ["./threads", "./ff", "./seq"]
numberThread = ['6', '8', '10', '12','14','16', '18', '20', '22', '24']
inputFile = ["../input/Input100.txt"]
Func = ["3 0 0 0 1"]

#runCommand = app[0] + " " + numberThread[0] + " " + inputFile[0] + " " + Func[0]

listCommand = []
for iapp in range(0,len(app)):
	for ithread in range(0,len(numberThread)):
		if app[iapp] == './seq':
			runCommand = app[iapp] + " " + inputFile[0] + " " + Func[0]
		else:	
			runCommand = app[iapp] + " " + numberThread[ithread] + " " + inputFile[0] + " " + Func[0]
		#runCommand = app[index] + " " + numberThread[index] + " " inputFile[index] + " " + Func[index]
		listCommand.append(runCommand)
	#	print(runCommand)

#print (runCommand)
print(listCommand)
import commands
# import subprocess   # for python3
#print commands.getstatusoutput(runCommand)[1]


threadC = []
ffC = []
seqC = []
times = 3 
for icommand in range(0,len(listCommand)):
	total=0
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
print(seqC)


import matplotlib.pyplot as plt

fig, ax = plt.subplots( nrows=1, ncols=1 )  # create figure & 1 axis
ax.plot([0,1,2], [10,20,3])
fig.savefig('to.png')   # save the figure to file
plt.close(fig)    # close the figure


fig,

plt.xlabel('Number of Thread')
plt.ylabel('Compeletion Time')

plt.plot(numberThread, threadC, ls='--', label='C++Thread')
plt.plot(numberThread, ffC, ls='-', label='FF')
plt.plot(numberThread, seqC, ls=':', label='Seq')

#plt.legend(['Thread', 'FF', 'Seq'], loc='upper right')
plt.show()


# os.system('script Thread_resutlt.txt -e')	# start script command
#for i in range(0,3):	# range start from 0 end at 2
#	os.system('./thread

# os.system('../thread 6 ../input/Input100.txt 3 0 0 0 1')
# os.system('exit') # exit script command
