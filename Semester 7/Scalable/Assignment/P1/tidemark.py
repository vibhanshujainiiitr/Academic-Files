# tidemark algorithm implementation python 

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Function to read the data
def ReadData(filepath):
  a = []
  with open(filepath, "r") as file:
    for t in file:
      t = t.strip().split()
      l = list(map(int,t))
      a.extend(l)
  return a

# tidemark algorithm implementation python

# Pair wise independent hash functions
# K > N 
N = 20
K = 30

# random matrix of size N*K
A = np.random.randint(0, 100, size=(K, N))

# random matrix of size N
B = np.random.randint(0, 100, size=(K, 1))

def hash_function(x):
    return np.dot(A, x) + B

# For an integer p > 0, zeros(p) is the number of zeros that the binary representation of p ends with.

def zeroes(p):
    if p > 0:
        # print(bin(p))
        temp = [i for i in str(bin(p))[2:]]
        # print(temp)
        zero = 0
        for j in range(len(temp)-1,0,-1):
            if temp[j] == '0':
                zero+=1
            else:
                break
        return zero

# read data
data1 = ReadData('/content/drive/MyDrive/scalable/T10I4D100K.dat')
data2 = ReadData('/content/drive/MyDrive/scalable/T40I10D100K.dat')
data3 = ReadData('/content/drive/MyDrive/scalable/kosarak.dat')

# function to calculate the tidemark

def tidemark(data):
    z = 0
    for i in data:
        z = max(zeroes(hash_function(i)), z)
        
    return 2**(z+0.5)

def tidemark_implemention(data,k):
    # find the length and divide the data 50000 each and then call time mark function on each of them
    data_len = len(data)
    data_tm = []
    for i in range(0,data_len,50000):
        data_tm.append(tidemark(data[i:i+50000]))
    return data_tm

            
# function to calculate the tidemark for each data set
data1_tm = tidemark(data1, 50000)
data2_tm = tidemark(data2, 50000)
data3_tm = tidemark(data3, 50000)


# function to print the results
def print_results(data, data_tm):
    print('The tidemark for data set ' + str(data) + ' is ' + str(data_tm))

print_results(1, data1_tm)
print_results(2, data2_tm)
print_results(3, data3_tm)


# ground truth values are number of distinct value in the chunk return by the tidemark function
# for data1
data1_gt = [len(set(data1[i:i+50000])) for i in range(0,len(data1),50000)]

# for data2
data2_gt = [len(set(data2[i:i+50000])) for i in range(0,len(data2),50000)]

# for data3
data3_gt = [len(set(data3[i:i+50000])) for i in range(0,len(data3),50000)]

# Plot for data 1
fig, ax = plt.subplots(1, 1, figsize=(10, 5))
ax.plot(data1_gt, label='ground truth')
ax.plot(data1_tm, label='tidemark')
plt.show()

# plot for data 2
fig, ax = plt.subplots(1, 1, figsize=(10, 5))
ax.plot(data2_gt, label='ground truth')
ax.plot(data2_tm, label='tidemark')
plt.show()

# plot for data 3
fig, ax = plt.subplots(1, 1, figsize=(10, 5))
ax.plot(data3_gt, label='ground truth')
ax.plot(data3_tm, label='tidemark')
plt.show()
