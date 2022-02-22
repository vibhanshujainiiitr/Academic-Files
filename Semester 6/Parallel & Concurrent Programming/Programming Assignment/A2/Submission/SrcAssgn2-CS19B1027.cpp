/*
Vibhanshu Jain
CS19B1027
 */

// Library Imports
#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/times.h>
#include <fstream>
#include <random>
#include <cstdio>
#include <atomic>
#include <string>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

// File input and output
ifstream inputFile;
ofstream outputFile;

// Average time calculations variables
atomic_llong csEnterTime, csExitTime;

// The lock class as used by the program
// Note: we are using virtual functions as all of them will be used for overwriting
class Lock
{
public:
    virtual void lock(int id) = 0;
    virtual void unlock(int id) = 0;
};
// both the lock and unlock fuctions will be overriden by the different locks-----

// The Filter Lock Implementation
class FilterLock : public Lock
{
private:
    int n;
    // the number of threads
    vector<int> Level;
    // The array to store levels
    vector<int> Victim;
    // The array to store victims

public:
    // The constructor
    FilterLock(int N)
    {
        n = N;
        // Initializing the level (all to 0 initial values) and victim vector according to the n passed.
        Level.resize(n, 0);
        Victim.resize(n);
    }

    // the lock function
    void lock(int id)
    {
        // checking for all n threads
        for (int i = 1; i < n; i++)
        {
            Level[id] = i;
            Victim[i] = id;
            for (int j = 0; j < n; j++)
            {
                // the function will remain here until the while condition is false
                while (j != id && Level[j] >= i && Victim[i] == id)
                    ;
            }
        }
    }

    // The unlock method
    void unlock(int id)
    {
        // Making the level of current thread zero
        Level[id] = 0;
    }
};

// The Peterson Lock Implementation
class PetersonLock : public Lock
{
private:
    int n;

    // the tree structure for storing the values
    vector<vector<int>> peterSon;

public:
    // the default constructure
    PetersonLock(int N)
    {
        n = N;
        // resizing the vector and the complete structure
        peterSon.resize(n - 1, vector<int>(3, 0));
    }

    // The lock function
    void lock(int id)
    {

        for (int i = n + id; i > 1; i /= 2)
        {
            peterSon[(i/2) - 1][i % 2] = 1;
            peterSon[(i/2) - 1][2] = i % 2;
            while (peterSon[(i/2) - 1][1 - (i % 2)] && peterSon[(i/2) - 1][2] == (i % 2))
            {
                // the function will remain here until the while condition is false
            }
        }
    }

    // The unlock function
    void unlock(int id)
    {
        for (int i = n + id; i > 1; i /= 2)
        {
            peterSon[(i/2) - 1][i % 2] = 0;
        }
    }
};

// The test function
void testCS(int thread_id, Lock *Test, FILE *output, int k, int lamda1, int lamda2)
{
    // The thread Id
    int id = thread_id;

    // running for k times so that it can enter k times
    for (int i = 1; i <= k; i++)
    {
        // The time variables to maintain the time record
        time_point<system_clock> start, end;

        // Request enter to the CS
        start = system_clock::now();

        time_t reqEnterTime = system_clock::to_time_t(start);
        // saving the enter request time

        // Chainging into time variable so that we can print it easily.
        tm *TimeVal1 = localtime(&reqEnterTime);
        fprintf(output, "%dth CS Entry Request at %d:%d:%d by thread %d (mesg 1)\n", i, TimeVal1->tm_hour, TimeVal1->tm_min, TimeVal1->tm_sec, id);
        // outputFile << i << "th CS Entry Request at " << TimeVal1->tm_hour << ":" << TimeVal1->tm_min << ":" << TimeVal1->tm_sec << " by thread " << id << "(mesg 1)\n";
        // Adding to log file

        // locking the thread
        Test->lock(id);

        // Entering the system
        end = system_clock::now();

        // saving the cs enter time
        time_t actEnterTime = system_clock::to_time_t(end);

        // Calculating the time needed for the request to get accepted
        csEnterTime += duration_cast<microseconds>(end - start).count();

        // Chainging into time variable so that we can print it easily.
        tm *TimeVal2 = localtime(&actEnterTime);

        fprintf(output, "%dth CS Entry at %d:%d:%d by thread %d (mesg 2)\n", i, TimeVal2->tm_hour, TimeVal2->tm_min, TimeVal2->tm_sec, id);
        // outputFile << i << "th CS Entry Request at " << TimeVal2->tm_hour << ":" << TimeVal2->tm_min << ":" << TimeVal2->tm_sec  << actEnterTime << " by thread " << id << "(mesg 2)\n";

        // Sleep timing as exponentail time delay as a fuction of lamda1
        sleep(lamda1 * exp(-1 * lamda1 * i));

        // Request Exit time
        start = system_clock::now();
        time_t reqExitTime = system_clock::to_time_t(start);

        // Chainging into time variable so that we can print it easily.
        tm *TimeVal3 = localtime(&reqExitTime);
        fprintf(output, "%dth CS Exit Request at %d:%d:%d by thread %d (mesg 3)\n", i, TimeVal3->tm_hour, TimeVal3->tm_min, TimeVal3->tm_sec, id);

        // outputFile << i << "th CS Entry Request at " << TimeVal3->tm_hour << ":" << TimeVal3->tm_min << ":" << TimeVal3->tm_sec << reqExitTime << " by thread " << id << "(mesg 3)\n";

        // Unlocking the thread so that the next threads can come
        Test->unlock(id);

        end = system_clock::now();
        time_t actExitTime = system_clock::to_time_t(end);
        // Saving the exit time of the thread

        // Calculting the time between the request and exit from the CS
        csExitTime += duration_cast<microseconds>(end - start).count();

        // Chainging into time variable so that we can print it easily.
        tm *TimeVal4 = localtime(&actExitTime);

        // outputFile << i << "th CS Entry Request at " << TimeVal4->tm_hour << ":" << TimeVal4->tm_min << ":" << TimeVal4->tm_sec << actExitTime << " by thread " << id << "(mesg 4)\n";
        fprintf(output, "%dth CS Entry at %d:%d:%d by thread %d (mesg 4)\n", i, TimeVal4->tm_hour, TimeVal4->tm_min, TimeVal4->tm_sec, id);

        // Sleep timing as exponentail time delay as a fuction of lamda2
        sleep(lamda2 * exp(-1 * lamda2 * i));
    }
}

// The main function
int main()
{
    // Input file open for getting the inputs
    inputFile.open("inp-params.txt", ios::in);
    int n, k, lamda1, lamda2;
    inputFile >> n >> k >> lamda1 >> lamda2;
    inputFile.close();
    // Input file closed

    // Printing the values for testing
    cout << "The given value of n, k, lamda1 and lamda2 are " << n << "," << k << "," << lamda1 << "," << lamda2 << endl;

    // outputFile.open("output.txt", ios::out);
    FILE *outputLog = fopen("output.txt", "w");

    // Creating n threads
    thread test[n];
    int data[n];

    // Filter lock
    // outputFile << "Filter Lock Outputs:\n";
    fprintf(outputLog, "Filter Lock Outputs:\n");

    // Creating n filter locks
    FilterLock *filterLock = new FilterLock(n);

    // Initializing the timings to 0
    csEnterTime = 0;
    csExitTime = 0;

    // Assigning the functions to each thread of filter lock
    for (int i = 0; i < n; i++)
    {
        data[i] = i;
        test[i] = thread(&testCS, data[i], filterLock, outputLog, k, lamda1, lamda2);
        // Calling testCS and passing the data
    }

    // Joining all the threads again
    for (int i = 0; i < n; i++)
    {
        test[i].join();
    }

    cout << "Avg CS Enter time for Filter Lock: " << (double)csEnterTime / (n * k) << "\n";
    cout << "Avg CS Exit time for Filter Lock: " << (double)csExitTime / (n * k) << "\n";

    // Peterson lock functions
    fprintf(outputLog, "\nPeterson Lock Outputs:\n");
    // Creatign n perterson locks
    PetersonLock *petersonlock = new PetersonLock(n);

    // Initializing the timings to 0
    csEnterTime = 0;
    csExitTime = 0;

    // Assigning the functions to each thread of peterson lock
    for (int i = 0; i < n; i++)
    {
        data[i] = i;
        test[i] = thread(&testCS, data[i], petersonlock, outputLog, k, lamda1, lamda2);
        // Calling testCS and passing the data
    }

    // Joining all the threads again
    for (int i = 0; i < n; i++)
    {
        test[i].join();
    }

    // Outing the results to terminal for the observation
    cout << "Avg CS Enter time for Peterson Lock: " << (double)csEnterTime / (n * k) << "\n";
    cout << "Avg CS Exit time for Peterson Lock: " << (double)csExitTime / (n * k) << "\n";

    // Closing the output
    // outputFile.close();
    fclose(outputLog);
}
