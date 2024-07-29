#ifndef COMPARISON_H
#define COMPARISON_H
#include<bits/stdc++.h>
#include "Process.h"
#include "Preemptive.h"
#include "NonPreemptive.h"
using namespace std;
class Comparison{
  vector<Process*> processes;
  public:
    Comparison(vector<Process*> processes){
        this->processes = processes;
    }
    void run(){
      
    }
};
#endif