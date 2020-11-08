#include <bits/stdc++.h>
using namespace std;


// Function to find the value of x^y
// The time complexity of the function will be O(log n)
// This function is also available in maths library, but for this question we don't have to use it.
int power ( int x, unsigned int y)
{
    int temp;
    if (y == 0)                     //  y  equals zero  means just return the value 1, irrespective of the value of x
        return 1;

    temp = power(x, y/2);           // reducing the y to half and again recusive call to the function
    if( y%2 == 0)
        return temp * temp;         // Returning the value temp * temp if y is even
    else
        return x * temp * temp;     // Returning the value x * temp * temp if it is odd
}


// Function to find the kth root of the number N
// Here we are using the binary search method.
int nrootsearch ( int low, int high, int N, int K)
{
    if( low <= high )                                       // To check the valid range
    {
        int mid = (low + high)/2;                           // mid is the index of middle element

        if( (power(mid, K) <= N) && ( power( mid + 1, K) > N))
            return mid;                                             // The middle element is our answer and thus we return that directly

        else if ( power( mid, K ) < N)                              // The answer lies in right half
            return nrootsearch( mid +1, high, N, K);                // Recursively searching in the right half
        else
            return nrootsearch( low, mid -1, N, K);                 // The answer lies in left half and recursively searching in left half
    }

    return low;                                                     // All the recursive funtion calling are done and we left with a final value which is closest.
}

// The main function
int main()
{
    int input;                      // The number of input given by user
    cin >> input;
    for (int i = 0 ; i < input ; i++)
    {
        int N, K;                   // We have to find the Kth root of the number N
        cin >> N >>K ;                   // Taking the values from user
        cout << nrootsearch( 0, N, N, K )       // Calling our function and printing the answer to the terminal
             <<endl;
    }
    return 0;
}
