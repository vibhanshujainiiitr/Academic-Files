Homework Assignment 3

Team Members.
S. Reethu
CS19B1023

Vibhanshu Jain 
CS19B1027


List of files Submitted

matmul.c
README.txt
REPORT.pdf


Compilation:

The code can be compiled on any linux machine using this command
$gcc matmul.c -o matmul -pthread

Note: we are including -pthread so that it can compile the code recognising the pthread.h header file

Running the command:

INTERACTIVE MODE: $./matmul --ar 3 --ac 4 --br 4 --bc 5 --interactive  
NON-INERACTIVE MODE: $./matmul --ar 3 --ac 4 --br 4 --bc 5

--ar : number of rows in first matrix
--ac : number of column in first matrix

--br : number of rows in second matrix
--bc : number of column in second matrix

Sample Outputs:

the_looser@vibhanshu:~/Desktop$ ./matmul --ar 3 --ac 3 --br 3 --bc 3
Time taken for single threaded: 1 us
Time taken for multi process: 790 us
Time taken for multi threaded: 114 us
Speedup for multi process : 0.00 x
Speedup for multi threaded : 0.01 x

the_looser@vibhanshu:~/Desktop$ ./matmul --ar 50 --ac 50 --br 50 --bc 50
Time taken for single threaded: 772 us
Time taken for multi process: 940 us
Time taken for multi threaded: 461 us
Speedup for multi process : 0.82 x
Speedup for multi threaded : 1.67 x

the_looser@vibhanshu:~/Desktop$ ./matmul --ar 400 --ac 400 --br 400 --bc 400
Time taken for single threaded: 376899 us
Time taken for multi process: 289966 us
Time taken for multi threaded: 12034 us
Speedup for multi process : 1.30 x
Speedup for multi threaded : 31.32 x

the_looser@vibhanshu:~/Desktop$ ./matmul --ar 100 --ac 100 --br 100 --bc 100
Time taken for single threaded: 10938 us
Time taken for multi process: 4880 us
Time taken for multi threaded: 2303 us
Speedup for multi process : 2.24 x
Speedup for multi threaded : 4.75 x


the_looser@vibhanshu:~/Desktop$ ./matmul --ar 3 --ac 3 --br 3 --bc 3 --interactive
Enter A:
1 2 3
4 5 6
7 8 9
Enter B:
1 2 3 
4 5 6
7 8 9
Result:
30 36 42 
66 81 96 
102 126 150 
Matrix A: 
1 2 3
4 5 6
7 8 9
Matrix B 
1 2 3
4 5 6
7 8 9
Result: 
30 36 42 
66 81 96 
102 126 150 
Matrix A: 
1 2 3
4 5 6
7 8 9
Matrix B: 
1 2 3  
4 5 6
7 8 9
Result: 
30 36 42 
66 81 96 
102 126 150 
Time taken for single threaded: 2 us
Time taken for multi process: 820 us
Time taken for multi threaded: 52 us
Speedup for multi process : 0.00 x
Speedup for multi threaded : 0.04 x

