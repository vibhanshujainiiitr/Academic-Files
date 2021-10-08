/* 
Vibhanshu Jain
CS19B1027
 */
#include <bits/stdc++.h>
#include <iostream>
#include <thread>
#include <sys/time.h>
#include <sys/times.h>
#include <fstream>
#include <random>
#include <cstdio>
#include <atomic>
#include <string>
#include <unistd.h>
#include <mutex>
#include <semaphore.h> 
#include <condition_variable>
#include <sys/time.h>
#include <ctime>

using namespace std;

// Output File
ofstream log_file;

// global variables
int R, W, k;
int rc = 0;
float  lambdaR, lambdaW;
/*
rc : Reader Count
R : number of read threads
W : number of writer threads
lambdaR : the parameter for the exponential wait between 2 successive read requests
lambdaW : the parameter for the exponential wait between 2 successive write requests
k : no. of times each process perform the task
 */


/* Default random engine */
default_random_engine randomNumber;

// Semaphores
sem_t mutexLock, db;


/* Obtaining the time in correct format */
string time_format(time_t present_time)
{
  struct tm* clock;
  char time[9];

  clock = localtime(&present_time);
  sprintf(time, "%.2d:%.2d:%.2d", clock->tm_hour, clock->tm_min, clock->tm_sec);
  return (string)time;
}


// Reader Function
void reader(int i){
    
    // Exponential Distribution
    exponential_distribution<double> readerTime(lambdaR);
    
    // Helper strings
    string enter, start, end;


    int temp=0;
    // Number of times threads is running
    
    while(true)
    {   
        // The entering time    
        time_t enterTime = time(NULL);
        enter = time_format(enterTime);
        
        // Request for access the database
        log_file<<i+1<<"th Reader ask access request at "<<enter<<"\n";
        
        // Decreasing the value of semaphore
        sem_wait(&mutexLock);
        
        // If reader count is zero then only allow the writer to go in
        if(rc==0)
            sem_wait(&db);
        rc = rc + 1;
        // Increasing the count of reader inside
       
        // Incresing the value of semaphore
        sem_post(&mutexLock);

        // The Database Access section
        time_t readingStartTime = time(NULL);
        start = time_format(readingStartTime);
        log_file<<i+1<<"th Reader given access at "<<start<<", there are "<<rc<<" readers currently inside."<<"\n";
        
        // Increasing the temp variable
        temp++;
        
        // Sleeping the thread
        usleep(readerTime(randomNumber));

        // Locking the section so that we can change the value of rc 
        sem_wait(&mutexLock);
        rc = rc - 1;
        if(rc==0)
            sem_post(&db);
        
        sem_post(&mutexLock);
    
        // Printing the current time and status
        time_t readingEndTime = time(NULL);
        end = time_format(readingEndTime);
        log_file<<i+1<<"th Reader exit at "<<end<<"\n";
        
        // If the temp is equal to k means this thread worked k time, this exit the code
        if(temp==k)    
            return;
    }
    
}

// The write access the section
void writer(int i){

    // The exponential distribution    
    exponential_distribution<double> writerTime(lambdaW);

    // Helper strings
    string enter, start, end;


    int temp=0;    
    // Number of times the threads executed
    
    while(true)
    {
        // The entering time    
        time_t enterTime = time(NULL);
        enter = time_format(enterTime);
        
        // requesting the critical section
        log_file<<i+1<<"th Writer access request at "<<enter<<"\n";

        sem_wait(&db);    

        // The Database access section
        time_t eatingStartTime = time(NULL);
        start = time_format(eatingStartTime);
        log_file<<i+1<<"th -------------------  Writer given access at "<<start<<", there are "<<rc<<" readers currently inside."<<"\n";
        temp++;
        
        // Sleeping the thread
        usleep(writerTime(randomNumber));

        sem_post(&db);
    
        time_t writerEndTime = time(NULL);
        end = time_format(writerEndTime);
        log_file<<i+1<<"th Writer exit at "<<end<<"\n";
        
        // If this thread is executed k time then exit the loop
        if(temp==k)           
            return;
    }

    
}

int main(){

    // Time variables
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    // input file
    ifstream input;
    input.open("inp-params.txt");
    input>>R>>W>>lambdaR>>lambdaW>>k;
    input.close();

    // Creating threads
    thread *rth = new thread[R];
    thread *wth = new thread[W];
    
    // Opening the log file    
    log_file.open("log.txt");

    // Initializing the semaphores
    sem_init(&mutexLock,0,1);
    sem_init(&db,0,1);
    
    // Checking whether the semaphore created successfully or not
    if(&mutexLock == SEM_FAILED)
    {
        log_file<<("ERROR: Couldn't create semaphore");
        return -1;
    } 

    if(&db == SEM_FAILED)
    {
        log_file<<("ERROR: Couldn't create semaphore");
        return -1;
    }

    // Calling the threads 
    for(int i=0; i<R; i++)
    {
        rth[i] = thread(reader,i);
    }
    for(int i=0; i<W; i++)
    {
        wth[i] = thread(writer,i);
    }

    // Joining the threads
    for(int i=0; i<R; i++)
    {
        rth[i].join();
    }
    for(int i=0; i<W; i++)
    {
        wth[i].join();
    }

    // noting the end time
    gettimeofday(&endTime, NULL);
    
    // Converting the time to miliseconds
    long long Etime = endTime.tv_usec + 1000000*endTime.tv_sec;
    long long Stime = startTime.tv_usec + 1000000*startTime.tv_sec;
    
    // Printing the execution time
    log_file<<"\n\n"<<"Time taken "<<Etime-Stime<<"\n\n";
    
    // Closing the log file
    log_file.close();
}