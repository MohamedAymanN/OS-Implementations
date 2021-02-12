# -*- coding: utf-8 -*-
"""
Created on Sun Jan 20 00:40:19 2019

@author: Mohamed Ayman Naguib
"""

from operator import itemgetter
import numpy as np
import random as rand
import matplotlib.pyplot as plt

''' Frames Printing Function '''
def printFrame(q):
    print("Page Frames: ")
    for i in range(len(q)):
        print("--- ",end=" ")
    print("")
    for i in range(len(q)):
        print("|%s|"%q[i][0],end="  ")
    print("")
    for i in range(len(q)):
        print("--- ",end=" ")
    print("")

''' First in First out Algorithm'''
def FIFO(refString):
    q = []
    currentIndex = 0
    pageFaults=0
    for page in refString.split(","):
        if page not in q:
            if len(q) == pageFrames:
                q[currentIndex]=page
                currentIndex = (currentIndex+1) % pageFrames
            else:
                q.append(page)
            pageFaults+=1
        printFrame(q)
    print("Page Faults = %d" %pageFaults)
    return pageFaults
''' Least Frequently Used Algorithm'''
def LFU(refString):
    q = []
    pageFaults=0
    for page in refString.split(","):
        if not [el for el in q if page == el[0]]:
            if len(q) == pageFrames:
                q[q.index(min(q,key=itemgetter(1)))] = [page,1]
            else:
                q.append([page,1])
            pageFaults+=1
        else:
            q=[[page,el[1]+1] if el[0]==page else el for el in q]
        printFrame(q)
    print("Page Faults = %d" %pageFaults)
    return pageFaults
'''Least Recently Used Algorithm'''
def LRU(refString):
    q = []
    pageFaults=0
    for idx,page in enumerate(refString.split(",")):
        if not [el for el in q if page == el[0]]:
            if len(q) == pageFrames:
                q[q.index(min(q,key=itemgetter(1)))] = [page,idx]
            else:
                q.append([page,idx])
            pageFaults+=1
        else:
            q=[[page,idx] if el[0]==page else el for el in q]
        printFrame(q)
    print("Page Faults = %d" %pageFaults)
    return pageFaults
'''Inputs'''
meanValuePoisson = 5
physicalMemSize = 3
virtualMemSize = 10
pageFrames = 3
elementsSize = 1
poissonSamples = 10
'''Poission Generation'''
poissonData=[]
for i in range(poissonSamples):
        poisson = np.random.poisson(meanValuePoisson, elementsSize)[0]
        poissonData.append([str(rand.randint(0,virtualMemSize-1)) for el in range(poisson)])

keys   = []
values = []
for ref in poissonData:
    keys.append(len(ref))
    values.append(FIFO(",".join(ref)))
plt.bar(keys,values,0.5,color="red")
plt.show()
keys   = []
values = []
for ref in poissonData:
    keys.append(len(ref))
    values.append(LFU(",".join(ref)))
plt.bar(keys,values,0.5,color="green")
plt.show()
keys   = []
values = []
for ref in poissonData:
    keys.append(len(ref))
    values.append(LRU(",".join(ref)))
plt.bar(keys,values,0.5,color = "brown")
plt.show()
refString = "7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1"
