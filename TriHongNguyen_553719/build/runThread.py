# script result.txt "./sequantialization ../input/InputTest.txt 3 0 0 0 1"

import os
import subprocess


app = "./thread"
numberThread = "6"
inputFile = "../input/Input100.txt"
powFunc = "3"
paraList = "0 0 0 1"

runCommand = app + " " + numberThread + " " + inputFile + " " + powFunc + " " + paraList

print (runCommand)


import commands
print commands.getstatusoutput(runCommand)[1]

listRunning = []
total = 0
for i in range(0,3):
	tempOutput = commands.getstatusoutput(runCommand)[1]
	listRunning.append(tempOutput)
	print(tempOutput.rsplit(None, 1)[-1])
	total = total + float(tempOutput.rsplit(None, 1)[-1])

print(listRunning)
print(total/3)

# os.system('script Thread_resutlt.txt -e')	# start script command
#for i in range(0,3):	# range start from 0 end at 2
#	os.system('./thread

# os.system('../thread 6 ../input/Input100.txt 3 0 0 0 1')
# os.system('exit') # exit script command
