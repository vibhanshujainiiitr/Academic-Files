/*
Vibhanshu Jain
CS19B1027
TAS
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

using namespace std;

/* Atomic boolean */
atomic<bool> lock = ATOMIC_FLAG_INIT;

/* File output */
ofstream log_file;


/* Time variables */
typedef long long t;
t waiting_time = 0;
t worst_time = 0;

/* Obtaing the time in correct format */
string cal_time(time_t present_time)
{
  struct tm* clock;
  char time[9];

  clock = localtime(&present_time);
  sprintf(time, "%.2d:%.2d:%.2d", clock->tm_hour, clock->tm_min, clock->tm_sec);
  return (string)time;
}

bool test_and_set( bool *target){
  bool rv = *target;
  *target = true;
  return rv;
}


/* Test CS Functions */
 
void testCS(int id, int k, exponential_distribution<double> &csTime, exponential_distribution<double> &rmTime, default_random_engine &gen)
{ 
  string print_helper;
  string index;

  for( int i= 0; i<k; i++)
  { 
    if(i == 0)
      index = "st";
    else if(i==1)
      index = "nd";
    else if(i==2)
      index = "rd";
    else 
      index = "th";
    
    time_t reqEnterTime = time(NULL);
    print_helper = to_string(i+1) + index + " CS Request at " +  cal_time(reqEnterTime) + " by thread " + to_string(id+1) + '\n';
    log_file << print_helper;


    /* Critical Section  */
    while(lock.exchange(true, memory_order_acquire))
      ;
      
    time_t actEnterTime = time(NULL);
    time_t temp = actEnterTime - reqEnterTime;
    waiting_time += temp;

    if(temp > worst_time)
      worst_time = temp; 


    print_helper = to_string(i+1) + index + " CS entry at " +  cal_time(actEnterTime) + " by thread " + to_string(id+1) + '\n';
    log_file << print_helper;


    usleep(csTime(gen)*1000);
    /* Simualtion of critical section */

    time_t exitTime = time(NULL);
    print_helper = to_string(i+1) + index + " CS Exit at " +  cal_time(exitTime) + " by thread " + to_string(id+1) + '\n';
    log_file << print_helper;

    lock.exchange(false ,memory_order_release);

    /* Remainder Section Simualtion */
    usleep(rmTime(gen)*1000);
  }
}


int main(){
  int n, k, lambda1, lambda2;

  ifstream input;
  input.open("inp-params.txt");

  input>>n>>k>>lambda1>>lambda2;

  input.close();


  default_random_engine randomNumber;

  exponential_distribution<double> csTime((double)1 / lambda1);
  exponential_distribution<double> rmTime((double)1 / lambda2);


  thread *th = new thread[n];

  log_file.open("TAS-Log.txt");

  for(int i=0; i<n; i++){
    th[i] = thread(testCS, i, k, ref(csTime), ref(rmTime), ref(randomNumber));
  }

  for(int i=0; i<n; i++){
    th[i].join();
  }

  log_file<<"Average Waiting time to enter CS: "<< (double)waiting_time / (n*k)<<endl;
  log_file<<"Worst case time taken to enter CS: "<< (double)worst_time <<endl;

  log_file.close();
}