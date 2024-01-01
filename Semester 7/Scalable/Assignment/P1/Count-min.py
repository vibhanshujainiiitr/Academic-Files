Values = [(50, 50),(25, 100),(250, 10),(500, 5)]

# class of hash functions
class HashFunction:
  def __init__(self,k):
    self.a = np.random.randint(0, 100)
    self.b = np.random.randint(0, 100)
    self.k = k
  
  def hash(self, x):
    return (np.dot(self.a,x) + self.b) % self.k

# diving the dataset into training and testing, 95% training and 5% testing
train1 = data1[:int(0.95*len(data1))]
test1 = data1[int(0.95*len(data1)):]
train2 = data2[:int(0.95*len(data2))]
test2 = data2[int(0.95*len(data2)):]
train3 = data3[:int(0.95*len(data3))]
test3 = data3[int(0.95*len(data3)):]


# count min-sketch function
def CountMinFunction(data, hash_functions, countMin, t):
  for ele in data:
    for i in range(t):
      countMin[i][hash_functions[i].hash(ele)] += 1
  return countMin

# count min-sketch query function
def CountMinQuery(data, hash_functions, countMin, t):
  count = 0
  for ele in data:
    count += min([countMin[i][hash_functions[i].hash(ele)] for i in range(t)])
  return count

# loop over the different values
for m in Values:
  for data in [(train1,test1,"T10I4D100K"), (train2,test2,"T40I10D100K"), (train3,test3, "kosarak")]:
    # an 2d array of t*k 
    countMin = np.zeros((m[0],m[1]))

    # creating k hash functions
    hash_functions = []
    for i in range(m[1]):
      hash_functions.append(HashFunction(m[1]))
    # the count min result 
    countMinResult = CountMinFunction(data[0], hash_functions, countMin, m[0])

    # count min query function 
    countMinQueryResult = CountMinQuery(data[1], hash_functions, countMinResult, m[0])
    print("Count Min Query Result for dataset: ", data[2], " is ", countMinQueryResult)

    