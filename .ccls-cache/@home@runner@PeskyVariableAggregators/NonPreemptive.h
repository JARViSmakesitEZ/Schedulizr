#ifndef NONPREEMPTIVE_H
#define NONPREEMPTIVE_H

#include "Process.h"
#include "Summary.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class NonPreemptive{
  private:
    vector<Process*> processes;
    bool simulation;
  public:
    NonPreemptive(vector<Process*> processes,bool simulation){
        this->processes = processes;
        this->simulation = simulation;
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
  public:
    Summary* fcfs() {
        // Sort processes based on arrival time
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
        int totalResponseTime = 0;
    
        for (const Process* process : processes) {
            totalWaitingTime += process->waitingTime;
            totalTurnaroundTime += process->turnaroundTime;
            totalResponseTime += process->responseTime;
        }
    
        double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
        double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();
        double avgResponseTime = static_cast<double>(totalResponseTime) / processes.size();
    
        if (simulation) {
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
            cout << "Average Response Time: " << avgResponseTime << "\n";
        }
    
        return new Summary(avgWaitingTime, avgTurnaroundTime, avgResponseTime);
    }



    Summary* sjf() {
        sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
            if(a->arrivalTime == b->arrivalTime){
                return a->burstTime < b->burstTime;
            }
            return a->arrivalTime < b->arrivalTime;
        });

        int currentTime = 0;
        map<Process*,bool> completed;
        int totalCompleted = 0;
        int totalProcesses = processes.size();
        while(totalCompleted < totalProcesses){
            vector<Process*> readyQueue;
            Process* toBeExecuted = NULL;
            int minBurstTime = INT_MAX;
            for(Process* process : processes){
                if(currentTime >= process->arrivalTime && !completed[process] && process->burstTime < minBurstTime){
                    toBeExecuted = process;
                    minBurstTime = process->burstTime;
                }
            }
            if(toBeExecuted == NULL){
                for(Process* process : processes){
                    if(!completed[process]){
                        toBeExecuted = process;
                        break;
                    }
                }
            }
            if (currentTime < toBeExecuted->arrivalTime) {
                currentTime = toBeExecuted->arrivalTime;
            }
            toBeExecuted->responseTime = currentTime - toBeExecuted->arrivalTime;
            toBeExecuted->waitingTime = currentTime - toBeExecuted->arrivalTime;
            toBeExecuted->completionTime = currentTime + toBeExecuted->burstTime;
            toBeExecuted->turnaroundTime = toBeExecuted->completionTime - toBeExecuted->arrivalTime;
            currentTime += toBeExecuted->burstTime;
            completed[toBeExecuted] = true;
            totalCompleted++;
        }

        // Calculate total waiting time and turnaround time
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;
        int totalResponseTime = 0;

        for (const Process* process : processes) {
            totalWaitingTime += process->waitingTime;
            totalTurnaroundTime += process->turnaroundTime;
            totalResponseTime += process->responseTime;
        }

        double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
        double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();

        double avgResponseTime = static_cast<double>(totalResponseTime) / processes.size();

        sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
            return a->completionTime < b->completionTime;
        });

        if(simulation){
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
            cout << "Average Response Time: " << avgResponseTime << "\n";
        }
        return new Summary(avgWaitingTime, avgTurnaroundTime, avgResponseTime);
    }


        Summary* priority() {
            sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
                if(a->arrivalTime == b->arrivalTime){
                    return a->burstTime < b->burstTime;
                }
                return a->arrivalTime < b->arrivalTime;
            });

            int currentTime = 0;
            map<Process*,bool> completed;
            int totalCompleted = 0;
            int totalProcesses = processes.size();
            while(totalCompleted < totalProcesses){
                Process* toBeExecuted = NULL;
                int maxPriority = INT_MAX;
                for(Process* process : processes){
                    if(currentTime >= process->arrivalTime && !completed[process] && process->priority < maxPriority){
                        toBeExecuted = process;
                        maxPriority = process->priority;
                    }
                }
                if(toBeExecuted == NULL){
                    for(Process* process : processes){
                        if(!completed[process]){
                            toBeExecuted = process;
                            break;
                        }
                    }
                }
                if (currentTime < toBeExecuted->arrivalTime) {
                    currentTime = toBeExecuted->arrivalTime;
                }
                toBeExecuted->responseTime = currentTime - toBeExecuted->arrivalTime;
                toBeExecuted->waitingTime = currentTime - toBeExecuted->arrivalTime;
                toBeExecuted->completionTime = currentTime + toBeExecuted->burstTime;
                toBeExecuted->turnaroundTime = toBeExecuted->completionTime - toBeExecuted->arrivalTime;
                currentTime += toBeExecuted->burstTime;
                completed[toBeExecuted] = true;
                totalCompleted++;
            }

            // Calculate total waiting time and turnaround time
            int totalWaitingTime = 0;
            int totalTurnaroundTime = 0;
            int totalResponseTime = 0;
            
            for (const Process* process : processes) {
                totalWaitingTime += process->waitingTime;
                totalTurnaroundTime += process->turnaroundTime;
                totalResponseTime += process->responseTime;
            }

            double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
            double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();

            double avgResponseTime = static_cast<double>(totalResponseTime) / processes.size();

            sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
                return a->completionTime < b->completionTime;
            });

            if(simulation){
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
                cout << "Average Response Time: " << avgResponseTime << "\n";
            }

            return new Summary(avgWaitingTime, avgTurnaroundTime, avgResponseTime);
        }
};
#endif
