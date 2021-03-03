/* 
Name: Vibhanshu Jain
Roll No: CS19B1027
*/
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

    /* Input and output file details */
    ifstream input;
    ofstream output_log, output_stat;

    input.open("inp-params.txt");
    output_log.open("EDF-Log.txt");
    output_stat.open("EDF-Stats.txt");

    int n;
    // The total number of process
    input>>n;


    /*
    Creating an array of process 
    */
    process A[n];


    /* Taking the input for each process */
    for(int x=0; x<n;x++)
    {
        input>>A[x].i>>A[x].t>>A[x].p>>A[x].k;
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
        output_log<<endl<<"This Problem cannot be scheduled" <<endl;
        exit(0);
    }

    int process[time], min=0,next_process;

    /* Running the scheduling */
    for(int x=0; x<time; x++){
        min = INT_MAX;
        // The min to be the maximum integer value

        for(int y=0; y<n;y++){
            if(A[y].remaining_time > 0){
                if(min > A[y].p){
                    min = A[y].p;
                    next_process = y;
                    output_log<<"The process is preemted"<<y;
                }
            }
        }


        if(A[next_process].remaining_time > 0){
            process[x] = next_process;
            A[next_process].remaining_time -= -1;
        }

        for(int z=0; z<n;z++){
            if((x+1)%A[z].p == 0){
                A[z].remaining_time = A[z].i;
                next_process = z;
            }
        }
    }


    // The process completed excuting and now we can 
    // calculate the other varibales
}
