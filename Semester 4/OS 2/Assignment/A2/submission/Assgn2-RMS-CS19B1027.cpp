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
#include <fstream>

using namespace std;
/* 
The class will contain the details of each process
*/
class process{
    public:
        int i;  // ID
        int t;  // Processing time
        int p;  // Period
        int start_time;  // Number of time it repeats
        int remaining_time;
};

int main(){

    /* Input and output file details */
    ifstream input;
    ofstream output_log, output_stat;

    input.open("inp-params.txt");
    output_log.open("RMS-Log.txt");
    output_stat.open("RMS-Stats.txt");

    int n;
    // The total number of process
    input>>n;


    /*
    Creating an array of process 
    */
    int total_process=0;
    process A[INT_MAX];


    /* Taking the input for each process */
    int max_time_period=-1;
    for(int x=0; x<n;x++)
    {   
        int i,t,p,k;
        input>>i>>t>>p>>k;
        if(max_time_period <t)  
            max_time_period = t;
        for(int i=0;i<k;i++){
            int process_number = ++total_process;
            A[process_number].i = i;
            A[process_number].t = t;
            A[process_number].p = p;
            A[process_number].remaining_time = p;
            A[process_number].start_time = i*p;
            // Adding the values of the process
        }
        
    }


    /* Calculating the total time to run the execution 
    */  
    int time=n*max_time_period;

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

    int process[time], min=0,next_process, waiting_time=0;

    /* Running the scheduling */
    for(int x=0; x<time; x++){
        min = INT_MAX;
        // The min to be the maximum integer value

        for(int y=0; y<n;y++){
            if(A[y].remaining_time > 0 && A[y].start_time <= x){
                // Run this part only when the process and has arrived
                if(min > A[y].p){
                    min = A[y].p;
                    next_process = y;
                    output_log<<"The process is preemted"<<y<<endl;
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
