#include <stdio.h>

// The merge funtion which merged the two sorted arrays.

int Merge( int a[], int temp[], int left, int mid, int right )
{
    int k = left, i = left, j = mid+1;
    int inversion_count = 0;                          //The counter to store the values of inversion pair

                                                    // While there are elements in the left and right runs

    while ( i<= mid && j<= right)
    {
        if( a[i] <= a[j])                           // If a[j] is greater then a[i] then simply fill the temp array with it.
        {
            temp[k] = a[i];
            k++;                                    // Increamenting the index of temp array
            i++;                                    // Increamenting the index of right array
        }
        else
        {
            temp[k] = a[j];                         // If a[j] is less then a[i] then too fill the temp array with it, but here will have inversion pairs
            k++;
            j++;
            inversion_count = inversion_count + ( mid - i + 1);                         // Counting the number of inversion pair. The elements on the remaining array will also form inversion with the element a[j], therefore we need to increase the count carefully.
        }
    }

    while ( i <= mid )                              // Copying the remaining element in right array if any to temp array
    {
        temp[k] = a[i];
        i++; k++;
    }

    while ( j <= right )                            // Copying the remaining elements in the left array if any to temp array
    {
        temp[k] = a[j];
        j++; k++;
    }

    for ( int i = left; i <=right; i++)
    {
        a[i] = temp[i];                             // Modifying the original array
    }

    return inversion_count;
}


// Sort array a [left..right] using tempiliary array temp
int Mergesort(int a[], int temp[], int left, int right)
{

	if (right == left)	                            // if run size == 1
		return 0;


	int mid = (left + right)/2;                     // Finding the mid point
	int inversion_count = 0;                        // Initilizing the inversion count number with 0

	// recursively split runs into two halves until run size == 1,
	// then merge them and return back up the call chain

	inversion_count += Mergesort(a, temp, left, mid);           //Spliting and merging the left part

	inversion_count += Mergesort(a, temp, mid + 1, right);      //Spliting and merging the right part

	inversion_count += Merge(a, temp, left, mid, right);        // Merging the two halfs, left and right

	return inversion_count;
}

int main()
{
	int N;              // The number of elements in the array
	scanf("%d", &N);
	int a[N];           // A new array a with N elements
    for ( int i =0; i< N; i++)
    {
        scanf("%d", &a[i]);                     // Taking input of the values in the array
    }
	int temp[N];
	for (int i = 0; i < N; i++)
		temp[i] = a[i];                         // Initialising the temp array


	printf("%d", Mergesort(a, temp, 0, N - 1));             // The final answer by function call

	return 0;
}
