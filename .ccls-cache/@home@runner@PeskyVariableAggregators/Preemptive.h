#ifndef PREEMPTIVE_H
#define PREEMPTIVE_H

#include "Process.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Preemptive{
  // private:
    vector<Process*> processes;
  public:
    Preemptive(vector<Process*> processes){
        this->processes = processes;
    }
    void run(){
      int choice;
        cout<<"Enter 1 for RoundRobin, 2 for SRTF and 3 for Priority: "<<endl;
        cin>>choice;
        if(choice==1){
            roundRobin();
        }
        else if(choice==2){
            srtf();
        }
        else if(choice==3){
            priority();
        }
    }
  private:
    void roundRobin(){
  
    }
    void priority(){
  
    }  
    void srtf(){
  
    }
};
#endif
