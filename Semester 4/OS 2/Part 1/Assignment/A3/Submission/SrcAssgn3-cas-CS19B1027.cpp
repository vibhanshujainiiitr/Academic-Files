/*
Vibhanshu Jain
CS19B1027
CAS
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
typedef long long int var;
/* Variable for long long Integer  */


using namespace std;

/* Atomic Integer */
atomic<int> lock(0);


/* Output file */
ofstream logFile;

/* Time calculations */

var waiting_time = 0, worst_time = 0;
/* Time Initilization
   waiting_time for waiting time calculations
   worst_time for worst time calculations
 */

/* Obtaing the time in correct format */
string time_format(time_t present_time)
{
  struct tm* clock;
  char time[9];

  clock = localtime(&present_time);
  sprintf(time, "%.2d:%.2d:%.2d", clock->tm_hour, clock->tm_min, clock->tm_sec);
  return (string)time;
}

/* Testing CS Functions */
 
void testCS(int id, int k, exponential_distribution<double> &csTime, exponential_distribution<double> &rmTime, default_random_engine &gen)
{ 
  string print;
  string temp;

  for(int i= 0; i<k; i++)
  { 

    /* Helping function for temp */
    if(i == 0)
      temp = "st";
    else if(i==1)
      temp = "nd";
    else if(i==2)
      temp = "rd";
    else 
      temp = "th";
    
    time_t reqEnterTime = time(NULL);
    print = to_string( i + 1 ) + temp + " CS Request at " +  time_format(reqEnterTime) + " by thread " + to_string( id + 1 ) + '\n';
    logFile << print;


    /* Critical Section  */
    int expected = 0;

    while(!lock.compare_exchange_strong(expected, 1)){
      expected = 0;
    }
      
    time_t actEnterTime = time(NULL);
    time_t alpha = actEnterTime - reqEnterTime;
    
    /* Waiting time calculations */
    waiting_time = waiting_time + alpha;

    /* If this time is greater than previous worst time */
    if(alpha > worst_time){
      worst_time = alpha;       
    }

    print = to_string( i + 1 ) + temp + " CS entry at " +  time_format(actEnterTime) + " by thread " + to_string( id + 1 ) + '\n';
    logFile << print;


    usleep(csTime(gen)*1000);
    /* Simualtion of critical section */

    /* Calculations for exit time */
    time_t exitTime = time(NULL);
    print= to_string( i + 1 ) + temp + " CS Exit at " +  time_format(exitTime) + " by thread " + to_string( id + 1 ) + '\n';
    logFile << print;

    /* Releasing the lock again */
    lock = 0;

    /* Remainder Section Simualtion */
    usleep(rmTime(gen)*1000);
  }
}

int main(){
  
  
  int n, k, lambda1, lambda2;
  /* lambda1 and lambda2 are the paramters for generating random numbers */

  /* Input will contain the input file whoes name is "inp-params.txt" according to the question */
  ifstream input;
  input.open("inp-params.txt");

  /* Checking wether the input file is there or not */
  if(!input.is_open()){
    cerr<<"Input file not found"<<endl;
    return 0;
  }

  /* Taking the inputs */
  input>>n>>k>>lambda1>>lambda2;

  /* Closing the input file */
  input.close(); 


  /* Random number generator */
  default_random_engine randomNumber;

  exponential_distribution<double> csTime((double)1/lambda1);
  exponential_distribution<double> rmTime((double)1/lambda2);
   

  /* Opening the log file for putting the outputs */
  logFile.open("CAS-Log.txt");

  /* Creating and calling the threads */
  thread *th = new thread[n];
  
  for(int i=0; i<n; i++)
  {
    th[i] = thread(testCS, i, k, ref(csTime), ref(rmTime), ref(randomNumber));
  }

  for(int i=0; i<n;i++)
  {
    th[i].join();
  }


  /* Outputing the results */
  logFile<< "Average waiting time to enter CS: "<<(double)waiting_time / (n*k) <<endl;
  logFile<< "Worst Case time to enter CS: "<<(double)worst_time <<endl;


  /* Closing the output file */
  logFile.close();
}
