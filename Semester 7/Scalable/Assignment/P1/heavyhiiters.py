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

# read data
data1 = ReadData('/content/drive/MyDrive/scalable/T10I4D100K.dat')
data2 = ReadData('/content/drive/MyDrive/scalable/T40I10D100K.dat')
data3 = ReadData('/content/drive/MyDrive/scalable/kosarak.dat')

k = 10

def heavyHitters(data):
  # two arrays of size k to store top k elements
  top = np.zeros(k)
  freq = np.zeros(k)
  for i in data:
    # check if element is already present in top
    if i in top:
      # if present, increment its frequency
      freq[top == i] += 1
    else:
      # if not present, check if there is a space in top
      if 0 in top:
        # if there is a space, add the element
        top[top == 0] = i
        freq[top == i] += 1
      else:
        # if there is no space, decrement the frequency of all elements
        freq -= 1
        # if frequency becomes 0, remove the element
        top[freq == 0] = 0
        freq[freq == 0] = 0
  return top, freq

# verification function to check if the top k elements are correct
def verifyFunction(top, data):
    count = 0
    result = []
    for i in top:
        if i in data:
            count += 1
        if count > len(data)/k:
            result.append(i)
    return result

# calling the heavy hitters function
top1, freq1 = heavyHitters(data1)
top2, freq2 = heavyHitters(data2)
top3, freq3 = heavyHitters(data3)

# calling the verification function
result1 = verifyFunction(top1, data1)
result2 = verifyFunction(top2, data2)
result3 = verifyFunction(top3, data3)

# printing the results
print("Top elements in T10I4D100K.dat are: ", result1)
print("Top elements in T40I10D100K.dat are: ", result2)
print("Top elements in kosarak.dat are: ", result3)