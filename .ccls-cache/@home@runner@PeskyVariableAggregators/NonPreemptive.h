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
      int choice;
        cout<<"Enter 1 for FCFS, 2 for SJF and 3 for Priority: "<<endl;
        cin>>choice;
        if(choice==1){
            fcfs();
        }
        else if(choice==2){
            sjf();
        }
        else if(choice==3){
            priority();
        }
    }
  private:
    void fcfs() {
        sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
            return a->arrivalTime < b->arrivalTime;
        });
    
        int currentTime = 0;
        for (Process* process : processes) {
            if (currentTime < process->arrivalTime) {
                currentTime = process->arrivalTime;
            }
            process->responseTime = currentTime - process->arrivalTime;
            process->waitingTime = currentTime - process->arrivalTime;
            process->completionTime = currentTime + process->burstTime;
            process->turnaroundTime = process->completionTime - process->arrivalTime;
            currentTime += process->burstTime;
        }
    
        // Calculate total waiting time and turnaround time
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;
        for (const Process* process : processes) {
            totalWaitingTime += process->waitingTime;
            totalTurnaroundTime += process->turnaroundTime;
        }
    
        double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
        double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();
    
        // Print Gantt Chart
        cout << "\nGantt Chart:\n";
        for (const Process* process : processes) {
            cout << "|  " << process->ID << "   ";
        }
        cout << "|\n0";
        for (const Process* process : processes) {
            cout << "       " << process->completionTime;
        }
        cout << "\n";
    
        // Print detailed information
        cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tResponse Time\tCompletion Time\n";
        for (const Process* process : processes) {
            cout << process->ID << "\t\t" << process->arrivalTime << "\t\t" << process->burstTime << "\t\t" 
                 << process->waitingTime << "\t\t" << process->turnaroundTime << "\t\t" 
                 << process->responseTime << "\t\t" << process->completionTime << "\n";
        }
    
        cout << "\nAverage Waiting Time: " << avgWaitingTime << "\n";
        cout << "Average Turnaround Time: " << avgTurnaroundTime << "\n";
    }


    void sjf() {
        sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
            return a->arrivalTime < b->arrivalTime;
        });
    
        int currentTime = 0;
        vector<Process*> readyQueue;
        unordered_map<string,int> completedProcesses;
        int completed = 0;
        int totalProcesses = processes.size();
    
        while (completed < totalProcesses) {
            // Add all processes that have arrived by the current time to the ready queue
            for (auto& process : processes) {
                if (process->arrivalTime <= currentTime && !completedProcesses[process->ID]) {
                    readyQueue.push_back(process);
                }
            }
    
            if (!readyQueue.empty()) {
                // Sort readyQueue by burst time, then by arrival time
                sort(readyQueue.begin(), readyQueue.end(), [](const Process* a, const Process* b) {
                    if (a->burstTime == b->burstTime) {
                        return a->arrivalTime < b->arrivalTime;
                    }
                    return a->burstTime < b->burstTime;
                });
    
                // Select the process with the shortest burst time
                Process* nextProcess = readyQueue.front();
                readyQueue.erase(readyQueue.begin());
    
                if (currentTime < nextProcess->arrivalTime) {
                    currentTime = nextProcess->arrivalTime;
                }
    
                nextProcess->responseTime = currentTime - nextProcess->arrivalTime;
                nextProcess->waitingTime = currentTime - nextProcess->arrivalTime;
                nextProcess->completionTime = currentTime + nextProcess->burstTime;
                nextProcess->turnaroundTime = nextProcess->completionTime - nextProcess->arrivalTime;
    
                currentTime += nextProcess->burstTime;
                completed++;
            } else {
                // If no process is ready, move the current time forward
                currentTime++;
            }
        }
    
        // Calculate total waiting time and turnaround time
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;
        for (const Process* process : processes) {
            totalWaitingTime += process->waitingTime;
            totalTurnaroundTime += process->turnaroundTime;
        }
    
        double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
        double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();
    
        // Print Gantt Chart
        cout << "\nGantt Chart:\n";
        for (const Process* process : processes) {
            cout << "|  " << process->ID << "   ";
        }
        cout << "|\n0";
        for (const Process* process : processes) {
            cout << "       " << process->completionTime;
        }
        cout << "\n";
    
        // Print detailed information
        cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tResponse Time\tCompletion Time\n";
        for (const Process* process : processes) {
            cout << process->ID << "\t\t" << process->arrivalTime << "\t\t" << process->burstTime << "\t\t" 
                 << process->waitingTime << "\t\t" << process->turnaroundTime << "\t\t" 
                 << process->responseTime << "\t\t" << process->completionTime << "\n";
        }
    
        cout << "\nAverage Waiting Time: " << avgWaitingTime << "\n";
        cout << "Average Turnaround Time: " << avgTurnaroundTime << "\n";
    }


    void priority() {
        sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
            if(a->arrivalTime == b->arrivalTime){
              return a->priority < b->priority;
            }
            return a->arrivalTime < b->arrivalTime;
        });
        int currentTime = 0;
        for (Process* process : processes) {
            if (currentTime < process->arrivalTime) {
                currentTime = process->arrivalTime;
            }
            process->responseTime = currentTime - process->arrivalTime;
            process->waitingTime = currentTime - process->arrivalTime;
            process->completionTime = currentTime + process->burstTime;
            process->turnaroundTime = process->completionTime - process->arrivalTime;
            currentTime += process->burstTime;
        }
    
        // Calculate total waiting time and turnaround time
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;
        for (const Process* process : processes) {
            totalWaitingTime += process->waitingTime;
            totalTurnaroundTime += process->turnaroundTime;
        }
    
        double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
        double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();
    
        // Print Gantt Chart
        cout << "\nGantt Chart:\n";
        for (const Process* process : processes) {
            cout << "|  " << process->ID << "   ";
        }
        cout << "|\n0";
        for (const Process* process : processes) {
            cout << "       " << process->completionTime;
        }
        cout << "\n";
    
        // Print detailed information
        cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tResponse Time\tCompletion Time\n";
        for (const Process* process : processes) {
            cout << process->ID << "\t\t" << process->arrivalTime << "\t\t" << process->burstTime << "\t\t" 
                 << process->waitingTime << "\t\t" << process->turnaroundTime << "\t\t" 
                 << process->responseTime << "\t\t" << process->completionTime << "\n";
        }
    
        cout << "\nAverage Waiting Time: " << avgWaitingTime << "\n";
        cout << "Average Turnaround Time: " << avgTurnaroundTime << "\n";
    }
};
#endif
