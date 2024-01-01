# Pair wise independent hash functions

from sklearn.metrics import confusion_matrix

# the k value given in the question / size of the bloom filter
k = 10

# sketch size
sketchValues = [50, 70, 100, 150, 500, 1000, 2000]
# class of hash functions
class HashFunction:
  def __init__(self, N, K):
    self.N = N
    self.K = K
    self.a = np.random.randint(0, 100)
    self.b = np.random.randint(0, 100)
  
  # the function to calculate the hash value
  def hash(self, x):
    return (np.dot(self.a,x) + self.b) % k

# diving the dataset into training and testing, 95% training and 5% testing
train1 = data1[:int(0.95*len(data1))]
test1 = data1[int(0.95*len(data1)):]
train2 = data2[:int(0.95*len(data2))]
test2 = data2[int(0.95*len(data2)):]
train3 = data3[:int(0.95*len(data3))]
test3 = data3[int(0.95*len(data3)):]

# creating k hash functions
hash_functions = []
for i in range(k):
  hash_functions.append(HashFunction(N,K))


# bloom filter function
def bloom_filter(data, hash_functions, bloomFilter):
  for i in data:
    for j in hash_functions:
      bloomFilter[j.hash(i)] = 1
    
# query the bloom filter
def query_bloom_filter(hash_functions,ele, bloomFilter):
  for hash in hash_functions:
    if bool(bloomFilter[int(hash.hash(ele))]) == 0:
      return False
  return True

# loop over the different values of m
for m in sketchValues:
  for data in [(train1,test1), (train2,test2), (train3,test3)]:
    bloomFilter = np.zeros(m)

    # add elements to the bloom filter
    bloom_filter(data[0], hash_functions, bloomFilter)

    # Query the bloom filter
    res=[0]*len(data[1])

    # actual result array
    actual=[0]*len(data[1])

    # Testing the function
    for i in range(len(data[1])):
      res[i] = query_bloom_filter(hash_functions,data[1][i],bloomFilter)  
      if data[1][i] in data[0]:
        actual[i] = 1

    # calculate the false positive rate
    false_positive_rate = sum(res)/len(res)
    # print("False positive rate for T10I4D100K.dat is: ", false_positive_rate)

    # calculate the true positive rate
    true_positive_rate = sum([res[i] == actual[i] for i in range(len(res))])/len(res)
    # print("True positive rate for T10I4D100K.dat is: ", true_positive_rate)
    
    # calculate the confusion matrix
    cm = confusion_matrix(actual, res)  
    print("Confusion matrix for dataset and m ", m ," is: ", cm)
