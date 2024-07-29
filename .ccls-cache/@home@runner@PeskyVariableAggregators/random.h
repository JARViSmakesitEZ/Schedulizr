#ifndef NONPREEMPTIVE_H
#define NONPREEMPTIVE_H

#include "Process.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class NonPreemptive{
  private:
    vector<Process*> processes;
  public:
    NonPreemptive(vector<Process*> processes){
        this->processes = processes;
    }
  void run(){
    
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
