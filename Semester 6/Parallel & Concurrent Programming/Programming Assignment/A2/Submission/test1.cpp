/*
Vibhanshu Jain
CS19B1027
 */
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

// // File input and output
// ifstream inputFile;
// ofstream outputFile;

// Average time calculations
atomic_llong csEnterTime, csExitTime;

// The lock class as used by the program
// Note: we are using virtual functions as all of them will be used for overwriting
class Lock
{
public:
    virtual void lock(int x) = 0;
    virtual void unlock(int x) = 0;
};

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
        Level.resize(N, 0);
        Victim.resize(N);
    }

    // the lock function
    void lock(int id)
    {
        for (int i = 1; i < n; i++)
        {
            Level[id] = i;
            Victim[i] = id;
            for (int j = 0; j < n; j++)
            {
                while (j != 0 && Level[j] >= i && Victim[i] == id)
                {
                    // Empty loop
                }
            }
        }
    }

    // The unlock method
    void unlock(int id)
    {
        Level[id] = 0;
    }
};

// The Peterson Lock Implementation
class PetersonLock : public Lock
{
private:
    int n;
    vector<vector<int>> peterSon;

public:
    // the default constructure
    PetersonLock(int N)
    {
        n = N;
        peterSon.resize(N - 1, vector<int>(3, 0));
    }

    // The lock function
    void lock(int id)
    {
        for (int i = n + id; i > 1; i /= 2)
        {
            peterSon[(i >> 1) - 1][i % 2] = 1;
            peterSon[(i >> 1) - 1][2] = i % 2;
            while (peterSon[(i >> 1) - 1][1 - (i % 2)] && peterSon[(i >> 1) - 1][2] == (i % 2))
            {
                // Empty while loop
            }
        }
    }

    // The unlock function
    void unlock(int id)
    {
        for (int i = n + id; i > 1; i /= 2)
        {
            peterSon[(i >> 1) - 1][i % 2] = 0;
        }
    }

};

// The test function
void
testCS(int thread_id, Lock *Test, FILE *output, int k, int lamda1, int lamda2)
{
    int id = thread_id;
    for (int i = 1; i < k; i++)
    {
        time_point<system_clock> start, end;

        // Request enter
        start = system_clock::now();
        time_t reqEnterTime = system_clock::to_time_t(start);

        tm *lmt1 = localtime(&reqEnterTime);
        fprintf(output, "%dth CS Entry Request at %d:%d:%d by thread %d (mesg 1)\n", i, lmt1->tm_hour, lmt1->tm_min, lmt1->tm_sec, id);

        // locking the thread
        Test->lock(id);

        // Entering the system

        end = system_clock::now();
        time_t actEnterTime = system_clock::to_time_t(end);

        csEnterTime += duration_cast<microseconds>(end - start).count();

        tm *ltm2 = localtime(&actEnterTime);

        fprintf(output, "%dth CS Entry at %d:%d:%d by thread %d (mesg 2)\n", i, ltm2->tm_hour, ltm2->tm_min, ltm2->tm_sec, id);

        sleep(lamda1 * exp(-1 * lamda1 * i));

        // Request Exit time
        start = system_clock::now();
        time_t reqExitTime = system_clock::to_time_t(start);
        tm *lmt3 = localtime(&reqExitTime);
        fprintf(output, "%dth CS Exit Request at %d:%d:%d by thread %d (mesg 3)\n", i, lmt3->tm_hour, lmt3->tm_min, lmt3->tm_sec, id);

        end = system_clock::now();
        time_t actExitTime = system_clock::to_time_t(end);

        csExitTime += duration_cast<microseconds>(end - start).count();

        tm *ltm4 = localtime(&actExitTime);

        fprintf(output, "%dth CS Entry at %d:%d:%d by thread %d (mesg 4)\n", i, ltm4->tm_hour, ltm4->tm_min, ltm4->tm_sec, id);

        sleep(lamda2 * exp(-1 * lamda2 * i));
    }
}

// The main function
int main()
{
    cout<<"This is test";
    // inputFile.open("inp-params.txt", ios::in);
    int n, k, lamda1, lamda2;
    // inputFile >> n >> k >> lamda1 >> lamda2;
    // inputFile.close();

    FILE *inp = fopen("inp-params.txt","r");
    fscanf(inp,"%d %d %d %d",&n,&k,&lamda1,&lamda2);
    fclose(inp);

    cout<<n<<k<<lamda1<<lamda2;
    // Input file closes

    cout << "The given value of n and k are " << n << k;

    FILE *out = fopen("output.txt", "w");

    // Creating n threads
    thread test[n];
    int data[n];

    // Filter lock
    fprintf(out, "Filter Lock Outputs:\n");
    FilterLock *filterLock = new FilterLock(n);

    csEnterTime = csExitTime - 0;

    for (int i = 0; i < n; i++)
    {
        data[i] = i;
        test[i] = thread(&testCS, data[i], filterLock, out, k, lamda1, lamda2);
    }

    for (int i = 0; i < n; i++)
    {
        test[i].join();
    }

    cout << "Average CS Enter time for Filter Lock is: " << (double)csEnterTime / (n * k) << "\n";
    cout << "Average CS Exit time for Filter Lock is: " << (double)csExitTime / (n * k) << "\n";

    // Peterson lock
    PetersonLock *petersonlock = new PetersonLock(n);
    csEnterTime = csExitTime - 0;

    for (int i = 0; i < n; i++)
    {
        data[i] = i;
        test[i] = thread(&testCS, data[i], petersonlock, out, k, lamda1, lamda2);
    }

    for (int i = 0; i < n; i++)
    {
        test[i].join();
    }

    cout << "Average CS Enter time for Peterson Lock is: " << (double)csEnterTime / (n * k) << "\n";
    cout << "Average CS Exit time for Peterson Lock is: " << (double)csExitTime / (n * k) << "\n";

    fclose(out);
}
