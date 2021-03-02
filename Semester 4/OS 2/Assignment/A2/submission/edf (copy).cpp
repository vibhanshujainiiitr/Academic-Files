/* 
Name: Vibhanshu Jain
Roll No: CS19B1027
*/
#include <bits/types/time_t.h>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <math.h>
#include <numeric>
#include <limits.h>

using namespace std;
/* 
The class will contain the details of each process
*/
class Process
{
public:
    int id, time, period, arrival_time;
    Process(int id, int time, int period, int arrival_time){
        this->id = id;
        this->time = time;
        this->period = period;
        this->arrival_time = arrival_time;
    };
    Process(Process &&) = default;
    Process(const Process &) = default;
    Process &operator=(Process &&) = default;
    Process &operator=(const Process &) = default;
    ~Process();

private:
    
};

int main(){

    int total_process;

    /* Input and output file details */
    ifstream input;
    ofstream output_log, output_stat;

    input.open("inp-params.txt");
    output_log.open("EDF-Log.txt");
    output_stat.open("EDF-Stats.txt");

    int n;
    // The total number of process
    input>>n;

    /* We will add all the processes here according to the time
    they came. */
    priority_queue<Process> process_queue;

    /* Inputing the processes from input file */
    for(int i =0; i<n;i++){
        int id, time, period, arrival_time, k;
        input>>id>>time>>period>>k;
        /* Outputting the details of the given process */
        output_log<<"Process ID:"<<id<<" ;Processing time:"<<time<<" ;Period: "<<period<<" ;Arrival time: "<<arrival_time<<endl;
        total_process = total_process+k;

        for(int j=0; j<k;j++){
            // Pushing the process in the total process queue.
            process_queue.push(Process(id,time,period,j*arrival_time));
            // Arrival time will be the period*k
        }
    }


    /* Implementation of the processes */
    while(!process_queue.empty()){
        
    }
}