Values = [(50, 50),(25, 100),(250, 10),(500, 5)]

# class of hash functions
class HashFunction:
  def __init__(self, k):
    self.a = np.random.randint(0, 100)
    self.b = np.random.randint(0, 100)
    self.k = k
  def hash(self, x):
    return (np.dot(self.a,x) + self.b) % self.k
    
# class of count sketch hash functions
class CountSketchHashFunction:
  def __init__(self):
    self.a = np.random.randint(0, 100)
    self.b = np.random.randint(0, 100)
  
  def hash(self, x):
    if (np.dot(self.a,x) + self.b) % 2 == 1:
      return 1
    else:
      return -1

# diving the dataset into training and testing, 95% training and 5% testing
train1 = data1[:int(0.95*len(data1))]
test1 = data1[int(0.95*len(data1)):]
train2 = data2[:int(0.95*len(data2))]
test2 = data2[int(0.95*len(data2)):]
train3 = data3[:int(0.95*len(data3))]
test3 = data3[int(0.95*len(data3)):]


# count sketch function 
def CountSketchFunction(data, hash_functions, countSketch, t):
  for ele in data:
    for i in range(t):
      countSketch[i][hash_functions[i].hash(ele)] += hash_functions2[i].hash(ele)

# count sketch query function
def CountSketchQuery(data, hash_functions, countSketch, t):
  count = 0
  for ele in data:
    count += np.median([ countSketch[i][hash_functions[i].hash(ele)] for i in range(t) ])
  return count

Values = [(50, 50),(25, 100),(250, 10),(500, 5)]
for m in Values:
  for data in [(train1,test1,"T10I4D100K"), (train2,test2,"T40I10D100K"), (train3,test3, "kosarak")]:
    # creating k hash functions
    hash_functions = []
    for i in range(m[0]):
      hash_functions.append(HashFunction())
    # creating second k hash function array for count sketch
    hash_functions2 = []
    for i in range(m[0]):
      hash_functions2.append(CountSketchHashFunction(m[0]))

    # calculating the result
    countSketch = np.zeros((m[0],m[1]))
    countSketchResult = CountSketchFunction(data[0], hash_functions, countSketch, m[0])

    # testing the data
    countSketchQueryResult = CountSketchQuery(data[1], hash_functions, countSketch, m[0])
    print("Count-sketch Query Result for dataset: ", data[2], " is ", countSketchQueryResult)