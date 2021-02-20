* All the initial steps are understandable by the comments in the code only. I didn’t include them here, because these are some basic functions.


* e) We first create an empty queue using the previously defined function createQueue(). Also, we create a new node pointer ‘temp’ which is initialized to the front of the given queue. Next, we traverse the complete queue and at every step, we enqueue the data stored in the temp pointers in the new queue formed earlier.
For this, we are using the while loop, with the break condition when the temp is NULL. It will enqueue and then change the temp pointer to the next pointer stored in itself which will take it one step forward in the queue.


* f) For storing we are using the basic concept of bubble sort. Firstly we will store the front in ‘a’ pointer. Now we initialize the first while and inside it set and the pointer next to the ‘a’ in ‘b’ pointer. Again we start the next while loop, and this that we check for a condition then is the data stored in ‘a’ is greater then the data stored in ‘b’, if yes then swap these two values. Also at the end, we point b to the next pointer stored in itself. With this operation we traverse all the elements other than ‘a’ and it’s previous elements, and set the data in ‘a’ to be the minimum of all. Now at the end of the loop, we are changing the ‘a’ pointer to the next element pointer stored in itself. With this loop, we are checking the conditions of all the elements as same as we did previously for ‘a’. 
In this approach, firstly the lowest will come on top, then the second-lowest will come and so on.


* g) Play queue: We are first creating the new queue and storing the data as the position of the player. Next, we are linking the front and rear parts so as to create a circular queue. Now we are going into the while loop which will break when only one element is remaining in the queue. We also initialized the count with ‘1’ at starting. Now when we travel in the queue and at each step we increase the count by one. Once we come at the element with count k, then we will just remove it from the queue, and set count to one again. In this way the loop will run till only one element is remaining because it is a circular loop. We are using condition for loop, note this carefully, how itis helpful to us. Now once only one element is remaining, we will return its data. 


* h) Remove Duplicate: we are using the same concept for transversing the queue used in f part, and checking whether the particular element has occurred earlier or not. Previously we are coming whether it is big or not, now are comparing whether they are similar or not. If they are similar then we will remove the node of the one which comes later, in our notation we will remove ‘b’ if the data stored in both ‘a’ and ‘b’ are the same.
Also according to our break condition in the while loop, we have to check separately if the data stored in the last element is the same as the data stored in ‘a’.
