#ifndef PROCESS_H
#define PROCESS_H
#include<bits/stdc++.h>
using namespace std;
class Process{
  public:
    int arrivalTime;
    int burstTime;
    int responseTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    string ID;
    int priority;
    Process(string ID,int arrivalTime,int burstTime){
        this->ID = ID;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->priority = 1;
    }
    Process(string ID,int arrivalTime,int burstTime,int priority){
        this->ID = ID;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->priority = priority;
    }
    void printDetails(){
        cout<<this->ID;
    }
};
#endif