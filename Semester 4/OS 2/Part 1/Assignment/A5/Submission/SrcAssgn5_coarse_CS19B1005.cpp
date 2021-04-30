#include <iostream>
#include<vector>
#include <list>
#include<iterator>
#include <thread>
#include <semaphore.h>
#include<vector>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <cstdlib>
using namespace std;
int* colour; //to assign colour
bool*available;//to check whether colour is available or not
sem_t mutex;// mutexe
int v,p;
ofstream outfile;
void addEdge(list<int> m[], int u, int v)
{
    m[u].push_back(v);//add edge symmetrically to both vertices
    m[v].push_back(u);
}
void greedyColoring(list<int> m[],int*colour,bool*available,int u)
{
        list<int>::iterator i;
        int j;
        for (i = m[u].begin(); i != m[u].end(); ++i)
            if (colour[*i] != -1)
                available[colour[*i]] = true;
        for ( j = 0; j < v; j++)
            if (available[j] == false)
                break;
        colour[u] = j;
        for (i = m[u].begin(); i != m[u].end(); ++i)
            if (colour[*i] != -1)
                available[colour[*i]] = false;
}
int isexternal(int v1,list<int> m[],int start,int end){//to check whether the vertex is boundary or not
   for (auto x : m[v1]){
        if(x<start || x >=end ){
            return 1;
          }
       }
  return 0;
}
void append_number(int x ,list<int> m[]) {
  int start=x*v/p;//partition
  int end=(x+1)*v/p;
  for(int i=start;i<end;i++){
  int t=isexternal(i,m,start,end);
  if(t){
        sem_wait(&mutex);
   }
   greedyColoring(m,colour,available,i);
   if(t){
       sem_post(&mutex);
   }
   }
}
int main() {
  ifstream indata;
  indata.open("input_params.txt");
  outfile.open("Output_coarse.txt");
  outfile1.open("input.txt");
  indata>>p>>v;
  sem_init(&mutex, 0, 1);
  int i,j,randNum;
  list<int> *m;
  m = new list<int>[v];
  int b[v][v];
  for(i=0;i<v;i++){
      for(j=0;j<v;j++){
          b[i][j]=0;//intialise all elements of matrix to 0
       }
  }
  for(i=0;i<v;i++){
      for(j=i+1;j<v;j++){
          randNum =rand()%(1-0 + 1);//random generator
          b[i][j]=randNum;
          b[j][i]=randNum;//symmetric
          if(randNum==1){
               addEdge(m,i,j);//addEdge if 1
          }
       }
    }
   for(i=0;i<v;i++){
       for(j=0;j<v;j++){
           outfile1<<" "<<b[i][j]<<" ";
      }
      outfile1<<"\n";
   }
   colour=(int*)malloc(v*sizeof(int));
   colour[0]  = 0;
   for (int i = 1; i< v; i++)
        colour[i] = -1;//intialise colours to -1
   available=(bool*)malloc(v*sizeof(bool));
   for (int i = 0; i < v; i++)
        available[i] = false;
  std::vector<std::thread> threads;
  clock_t t;
  t = clock();
  for (int i=0; i<p; ++i) threads.push_back(std::thread(append_number,i,m));
  for (auto& th : threads) th.join();
  t = clock()-t;
  int a=colour[0];
  for (int i = 1; i < v; ++i) {/* findout how many colours are used*/
      if (a < colour[i]) {
          a = colour[i];
      }
  }
 outfile<<"Coarse Lock\n";
 outfile<<"No. of colours used:"<<a+1<<" \n"<<"Time taken by the algorithm using:"<<t<<" Millisecond"<<"\n";
  outfile<<"Colours:\n";
for (int i = 0; i < v; ++i){
outfile<<"v"<<i+1<<"-"<<colour[i]+1<<", ";
}
outfile<<"\n";
}


