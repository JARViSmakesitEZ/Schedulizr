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
        this->responseTime = -1;
        this->waitingTime = -1;
        this->completionTime = -1;
        this->turnaroundTime = -1;
        
    }
    Process(string ID,int arrivalTime,int burstTime,int priority){
        this->ID = ID;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->priority = priority;
        this->responseTime = -1;
        this->waitingTime = -1;
        this->completionTime = -1;
        this->turnaroundTime = -1;
    }
    void printDetails(){
        cout<<this->ID;
    }
};
#endif