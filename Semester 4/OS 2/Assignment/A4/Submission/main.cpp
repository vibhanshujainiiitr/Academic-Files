/*
Vibhanshu Jain
CS19B1027
 */

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
#include <pthread.h>

#include <semaphore.h>
// Including the library

using namespace std;

/* File output */
ofstream log_file;

int n, x, k=0;
float lambda, r, t;

default_random_engine randomNumber;
/* Some global variables */
int eating = 0, waiting = 0 ;
// eating and waiting keep track of the number of threads sitting at the table and waiting respectively.

sem_t mutex, block, lock;
bool must_wait = 0;

/* Time calculations */
int waiting_time = 0;


/* Obtaing the time in correct format */
string time_format(time_t present_time)
{
  struct tm* clock;
  char time[9];

  clock = localtime(&present_time);
  sprintf(time, "%.2d:%.2d:%.2d", clock->tm_hour, clock->tm_min, clock->tm_sec);
  return (string)time;
}


void algorithm(int i) 
  { 
    string enter,start,end;
		
    exponential_distribution<double> eatingTime(t);
  

    time_t enterTime = time(NULL);
    enter = time_format(enterTime);
    // Entering the critical section
    log_file<<i+1<<"th customer acccess request at "<<enter<<"\n";
    sem_wait(&mutex);
    
    if( must_wait == 1 || eating+1 > x)
    {
      waiting++;
      must_wait = 1;
      sem_post(&mutex);
      sem_wait(&block);
    }

    else
    {
      eating++;
      must_wait = (waiting > 0 && eating == x);
      sem_post(&mutex);
    }

    // Customer Starts eating on the table

    // Time calculations
    time_t eatingStartTime = time(NULL);
    start = time_format(eatingStartTime);

    log_file<<i+1<<"th customer given access at "<<start<<"\n";
    sem_wait(&mutex);

    // Exponential Delay
    sleep(eatingTime(randomNumber));
    
    eating--;


    // Customer ends eating on the table
    // time_t eatingEndTime = time(NULL);
    // end = time_format(eatingEndTime);
    // log_file<<i+1<<" customer finishes eating at "<<end<<" ."<<endl;

    time_t alpha = eatingStartTime - enterTime;
    waiting_time = waiting_time + alpha;


    if(eating == 0)
    {
      k = min(x, waiting);
      waiting -= k;
      eating += k;
      must_wait = (waiting > 0 && eating == x);
      for(int a = 0; a<k; a++)
      {
        sem_post(&block);
      }
      
    }

    sem_post(&mutex);
  }


int main(){

  ifstream input;
  input.open("input.txt");

  input>>n>>x>>lambda>>r>>t;
  
  input.close();
  


  exponential_distribution<double> comingTime(lambda);
  
   
  thread *th = new thread[n];
  // Creating the array of n threads
  
  log_file.open("Log.txt");

  // Initilizing the semaphores
  sem_init(&mutex,0,1);
  sem_init(&lock,0,1);
  sem_init(&block,0,0);
  // cout<<"\n This is \n";
  // Checking whether the semaphore created successfully or not
  if(&mutex == SEM_FAILED)
  {
    log_file<<("ERROR: Couldn't create semaphore");
    return -1;
  } 

  if(&mutex == SEM_FAILED)
  {
    log_file<<("ERROR: Couldn't create semaphore");
    return -1;
  }

  // Creating threads and passing the value of current customer
	////////

	int came = 0;
	int maxValue = r*x;
	while(came < n)
	{
	
	int s = rand()%maxValue + 1;
	if(came+s > n)
		s = n-came;
		
  for(int i=came; i<came+s; i++){
    th[i] = thread(algorithm,i);
	}

	came = s + came;
		sleep(comingTime(randomNumber));
	 
  }

  // Joining the threads created
  for(int i=0; i<n; i++){
    th[i].join();
  }

  log_file << "\n\nAverage waiting time: "<<(double)waiting_time/n<<endl;
  
  // Closing the log file
  log_file.close();
}