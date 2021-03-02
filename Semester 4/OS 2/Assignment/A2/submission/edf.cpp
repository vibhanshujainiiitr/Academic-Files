/* 
Name: Vibhanshu Jain
Roll No: CS19B1027
*/
#include <bits/types/time_t.h>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <numeric>
#include <limits.h>

using namespace std;
/* 
The class will contain the details of each process
*/
class process{
    public:
        int i;  // ID
        int t;  // Processing time
        int p;  // Period
        int k;  // Number of time it repeats
        int remaining_time;
};

int main(){
    int n;
    // The total number of process
    cin>>n;


    /*
    Creating an array of process 
    */
    process A[n];


    /* Taking the input for each process */
    for(int x=0; x<n;x++)
    {
        cin>>A[x].i>>A[x].t>>A[x].p>>A[x].k;
        // Adding the values of the process
    }


    /* Calculating the total time to run the execution 
    */  
    int time;
    for(int x=0; x<n;x++){
        if(time < A[x].p*A[x].k)
            time = A[x].p*A[x].k;
    }


    /*
        The CPU Utilization during the process 
     */
    float utilization;
    for(int x=0; x<n;x++){
        utilization += (1.0*A[x].t/A[x].p);
    }
    
    if(utilization > n*(pow(2, 1.0/n)-1)){
        cout<<endl<<"This Problem cannot be scheduled" <<endl;
        exit(0);
    }

    int max_deadline, current_process = 0, min_deadline, process[n];
    bool is_ready[n];

    /* Making each process ready */
    for(int x=0; x<n; x++){
        is_ready[x] = true;
    }

    // The process completed excuting and now we can 
    // calculate the other varibales
}