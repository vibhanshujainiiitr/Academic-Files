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
    int id, time, period, arrival_time, deadline;
    Process(int id, int time, int period, int arrival_time){
        this->id = id;
        this->time = time;
        this->period = period;
        this->arrival_time = arrival_time;
        this->deadline = this->arrival_time + this->period;
    };
    Process(Process &&) = default;
    Process(const Process &) = default;
    Process &operator=(Process &&) = default;
    Process &operator=(const Process &) = default;
    ~Process();

private:
    
};

int main(){

    int total_process, curr_time, waiting_time, missed_process=0;;
    /* The current time which must be equal to the arrival time of first process */

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
    priority_queue<Process> waiting_queue;
    priority_queue<Process> ready_queue;

    /* Inputing the processes from input file */
    for(int i =0; i<n;i++){
        int id, time, period, arrival_time, k;
        input>>id>>time>>period>>k;
        /* Outputting the details of the given process */
        output_log<<"Process ID:"<<id<<" ;Processing time:"<<time<<" ;Period: "<<period<<" ;Arrival time: "<<arrival_time<<endl;
        total_process = total_process+k;

        for(int j=0; j<k;j++){
            // Pushing the process in the total process queue.
            
            waiting_queue.push(Process(id,time,period,j*arrival_time));
            // Arrival time will be the period*k
        }
    }

    /* Some process variables for storing the temproary processes */
    Process current = waiting_queue.top();
    

    /* Implementation of the processes */
    while(!waiting_queue.empty()){
        curr_time = (waiting_queue.top()).arrival_time;

        /* if(previous_process.deadline <= curr_time && previous_process.id > 0){
            output_log<<"Deadline missed by Process"<<previous_process.id<<" at time "<<curr_time<<endl;
            waiting_time += curr_time - previous_process.time;
        } */

        /* If the current time & arrival time are same */
        while ((waiting_queue.top()).arrival_time == curr_time && !waiting_queue.empty()) {
            Process temp = waiting_queue.top();
            if(temp.id>0){
                ready_queue.push(temp);
            }
            waiting_queue.pop();
        }

        

        /* Till here we are just adding the processes in a waiting queue. Now we need to check what is happening with ready queue */
        
    }
}