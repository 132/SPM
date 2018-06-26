# script result.txt "./sequantialization ../input/InputTest.txt 3 0 0 0 1"
# python2.7
import os
import subprocess
import matplotlib.pyplot as plt
"""
app = ["./threads", "./ff", "./seq"]
numberThread = ['5', '6', '8']
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
"""
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
"""
"""
print(threadC)
print(ffC)
for i in range(1, len(ffC)):
	seqC.append(seqC[0])
print(seqC)


#thefile = open('test.txt', 'w')

#for item in threadC: 
#  print>>thefile, item


with open('test.txt','w') as out_file:
	out_file.write('threadC = [')
	for item in threadC: 
		out_file.write("'%s'" % item)
	out_file.write(']')




#fig, ax = plt.subplots( nrows=1, ncols=1 )  # create figure & 1 axis
#ax.plot([0,1,2], [10,20,3])
#fig.savefig('to.png')   # save the figure to file
#plt.close(fig)    # close the figure
"""
threadC = [15.703070000000002, 11.001985000000001, 10.594075000000002, 10.707980000000003, 10.691865000000004, 10.97121, 11.042955, 11.154900000000001, 10.998980000000001, 11.764510000000001, 12.169114999999998]
ffC = [10.905124999999998, 10.904914999999999, 10.901240000000001, 10.897129999999999, 10.898304999999999, 10.898344999999999, 10.897784999999997, 10.911555, 10.914874999999999, 10.913899999999998, 10.914735]
seqC = [15.663599999999999, 15.663599999999999, 15.663599999999999, 15.663599999999999, 15.663599999999999, 15.663599999999999, 15.663599999999999, 15.663599999999999, 15.663599999999999, 15.663599999999999, 15.663599999999999]
numberThread = ['6', '10', '20', '30', '40', '50', '60', '70', '80', '90', '130']
farmThread = [1, 5, 15, 25, 35, 45, 55, 65, 75, 85, 125]
farmC = [15.630785, 1.6878089399999996, 0.28461920499999993, 0.5495270050000001, 0.453475555, 1.20140393, 1.3831943999999998, 1.7273380500000002, 1.223013065, 3.12673555, 4.1341516]
modelSeq = [15.6531]

ModelThread = []
ModelThread.append(threadC[0])

ModelFarm = []
ModelFarm.append(modelSeq[0])

print(str(farmC[0]))
for i in range(1, len(farmThread)):
	ModelFarm.append(ModelFarm[0]/farmThread[i])
	print(str(farmC[i])+' vs ' + str(ModelFarm[i]))
#	ModelThread.append(threadC[i]-farmC[i]+ModelFarm[i])
	ModelThread.append(seqC[i] - modelSeq[0] + modelSeq[0]/farmThread[i])

fig, bx = plt.subplots(nrows=1,ncols=1)

plt.xlabel('Number of Thread')
plt.ylabel('Compeletion Time')

#plt.xlim(0, 43)
plt.ylim(0, 20)
bx.plot(numberThread, threadC, ls='--', label='C++Thread')
bx.plot(numberThread, ffC, ls='-', label='FF')
bx.plot(numberThread, seqC, ls=':', label='Seq')
bx.plot(numberThread, ModelThread, ls='-.', label='Model')
bx.legend(['Thread', 'FF', 'Seq', 'Model'], loc='upper right')

fig.savefig('graph/pow07_2000_0_130.png')
plt.close(fig)
plt.show()


fig, ax = plt.subplots(nrows=1,ncols=1)

plt.xlabel('Number of Thread')
plt.ylabel('Compeletion Time of Farm Stage')

#plt.xlim(0, 43)
plt.ylim(0, 20)
ax.plot(farmThread, ModelFarm, ls='--', label='Model')
ax.plot(farmThread, farmC, ls='-', label='Farm')
ax.legend(['Model', 'Farm'], loc='upper right')

fig.savefig('graph/Farm_pow07_2000_0_130.png')
plt.close(fig)
plt.show()

# os.system('script Thread_resutlt.txt -e')	# start script command
#for i in range(0,3):	# range start from 0 end at 2
#	os.system('./thread

# os.system('../thread 6 ../input/Input100.txt 3 0 0 0 1')
# os.system('exit') # exit script command
