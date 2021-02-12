# -*- coding: utf-8 -*-
"""
Created on Mon Jan 21 21:44:31 2019

@author: Mohamed Ayman Naguib
"""
import numpy as np

maxList       = []
neededList    = []
availableList = []

fin = open("Test Data.csv",'r')
lines = fin.readlines()

processesNumber, resourcesNumber = map(int, lines[0].strip().split(","))

for process in range(1, processesNumber + 1, 1):
    ls = []
    currentLine = lines[process].split(",")
    for maxResource in range(1, resourcesNumber + 1, 1):
        ls.append(int(currentLine[maxResource]))
    maxList.append(ls)

for process in range(1, processesNumber + 1, 1):
    ls = []
    currentLine = lines[process].split(",")
    for neededResource in range(resourcesNumber + 2, len(currentLine), 1):
        ls.append(int(currentLine[neededResource]))
    neededList.append(ls)

for resource in lines[-1].split(","):
    availableList = np.append(availableList, int(resource))

maxList    = np.array(maxList)
neededList = np.array(neededList)

def isSafeState():
    global availableList
    processTaken = np.zeros(shape=(processesNumber),dtype=int)
    sequence = []
    processCount = 0
    
    while(True):
        change = False
        for process in range(processesNumber):
            currentResource = neededList[process]
            lessNeed = all(currentResource[idx] <= availableList[idx] for idx in range(len(currentResource)))
            if  lessNeed and (processTaken[process] == 0):
                availableList = availableList + (maxList[process] - neededList[process])
                processTaken[process] = 1
                sequence.append(process)
                processCount += 1
                change = True
                
        if change == False and processCount == processesNumber:
            return sequence
        elif change == False and processCount < processesNumber:
            return []
                
def request(processIndex,requestValue):
    global availableList,neededList
    lessThanNeed = all(requestValue[idx]<=neededList[processIndex][idx] for idx in range(len(requestValue)))
    lessThanAval = all(requestValue[idx]<=neededList[processIndex][idx] for idx in range(len(requestValue)))
    if lessThanNeed and lessThanAval:
        neededList[processIndex] = neededList[processIndex] - requestValue
        availableList = availableList - requestValue
        isSafe = isSafeState()
        print(isSafe)
        if(len(isSafe)>0):
            print("System is Safe and Request Granted\n Sequence is %s"%isSafe)
            return True
    print("Could Not Resolve Request, as system is not safe")
    return False