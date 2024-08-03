#ifndef SIMULATION_H
#define SIMULATION_H
#include<bits/stdc++.h>
#include "Process.h"
#include "Preemptive.h"
#include "NonPreemptive.h"
using namespace std;
class Simulation{
  vector<Process*> processes;
  public:
    Simulation(vector<Process*> processes){
        this->processes = processes;
    }
    void run(){
      int choice;
      cout<<"Enter 1 for Preemptive Scheduling, 2 for Non-Preemptive Scheduling: "<<endl;
      cin>>choice;
      if(choice==1){
        Preemptive* app = new Preemptive(processes,true);
        app->run();
        delete app;
      }
      else{
        NonPreemptive* app = new NonPreemptive(processes,true);
        app->run();
        delete app;
      }
    }
};

#endif