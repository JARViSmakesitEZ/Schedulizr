#ifndef PREEMPTIVE_H
#define PREEMPTIVE_H

#include "Process.h"
#include "Summary.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Preemptive{
  private:
    vector<Process*> processes;
    bool simulation;
  public:
    Preemptive(vector<Process*> processes,bool simulation){
        this->processes = processes;
        this->simulation = simulation;
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
  public:
    Summary* roundRobin() {
        int timeQuantum;
        cout << "Enter time quantum: " << endl;
        cin >> timeQuantum;
    
        // Sort processes based on arrival time
        sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
            return a->arrivalTime < b->arrivalTime;
        });
    
        queue<Process*> readyQueue;
        map<string, bool> inReadyQueue;
        map<string, bool> completed;
        map<string, int> remainingBurstTime;
        int remainingProcesses = processes.size();
        int processesIncluded = 0;
        int currentTime = 0;
        vector<pair<string, int>> ganttChart;
    
        // Initialize remaining burst times
        for (Process* process : processes) {
            remainingBurstTime[process->ID] = process->burstTime;
        }
    
        while (remainingProcesses > 0) {
            // Add newly arrived processes to the ready queue
            for (Process* process : processes) {
                if (currentTime >= process->arrivalTime && !completed[process->ID] && !inReadyQueue[process->ID]) {
                    inReadyQueue[process->ID] = true;
                    readyQueue.push(process);
                    processesIncluded++;
                }
            }
    
            // If ready queue is empty, move to the next arriving process
            if (readyQueue.empty()) {
                for (Process* process : processes) {
                    if (!completed[process->ID]) {
                        currentTime = process->arrivalTime;
                        readyQueue.push(process);
                        inReadyQueue[process->ID] = true;
                        processesIncluded++;
                        break;
                    }
                }
            }
    
            Process* process = readyQueue.front();
            readyQueue.pop();
    
            if (process->responseTime == -1) {
                process->responseTime = currentTime - process->arrivalTime;
            }
    
            
            int timeRemaining = timeQuantum;
            while(remainingBurstTime[process->ID]>0 && timeRemaining>0){


                for (Process* process : processes) {
                    if (currentTime >= process->arrivalTime && !completed[process->ID] && !inReadyQueue[process->ID]) {
                        inReadyQueue[process->ID] = true;
                        readyQueue.push(process);
                        processesIncluded++;
                    }
                }
                
                currentTime++;
                timeRemaining--;
                remainingBurstTime[process->ID]--;
                if(remainingBurstTime[process->ID]==0){
                    process->completionTime = currentTime;
                    process->turnaroundTime = process->completionTime - process->arrivalTime;
                    process->waitingTime = process->turnaroundTime - process->burstTime;
                    completed[process->ID] = true;
                    remainingProcesses--;
                    break;
                }
                
            }
            if(!completed[process->ID]) readyQueue.push(process);
            ganttChart.push_back({process->ID, currentTime});
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

        if(simulation){
            // Print Gantt Chart
            cout << "\nGantt Chart:\n|";
            for (const auto& entry : ganttChart) {
                cout << "  " << entry.first << "  |";
            }
            cout << "\n0";
            for (const auto& entry : ganttChart) {
                cout << "      " << entry.second;
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
        // Sort processes based on arrival time
        sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
            return a->arrivalTime < b->arrivalTime;
        });
    
        map<string, int> remainingBurstTime;
        map<string, bool> completed;
        int remainingProcesses = processes.size();
        int currentTime = 0;
        vector<pair<string, int>> ganttChart;
    
        // Initialize remaining burst times
        for (Process* process : processes) {
            remainingBurstTime[process->ID] = process->burstTime;
        }
    
        while (remainingProcesses > 0) {
            Process* highestPriorityProcess = nullptr;
    
            // Find the process with the highest priority (lowest priority number) that has arrived
            for (Process* process : processes) {
                if (process->arrivalTime <= currentTime && !completed[process->ID]) {
                    if (highestPriorityProcess == nullptr || process->priority < highestPriorityProcess->priority) {
                        highestPriorityProcess = process;
                    }
                }
            }
    
            if (highestPriorityProcess == nullptr) {
                currentTime++;
                continue;
            }
    
            // Process execution
            if (highestPriorityProcess->responseTime == -1) {
                highestPriorityProcess->responseTime = currentTime - highestPriorityProcess->arrivalTime;
            }
    
            remainingBurstTime[highestPriorityProcess->ID]--;
            currentTime++;
            ganttChart.push_back({highestPriorityProcess->ID, currentTime});
    
            if (remainingBurstTime[highestPriorityProcess->ID] == 0) {
                highestPriorityProcess->completionTime = currentTime;
                highestPriorityProcess->turnaroundTime = highestPriorityProcess->completionTime - highestPriorityProcess->arrivalTime;
                highestPriorityProcess->waitingTime = highestPriorityProcess->turnaroundTime - highestPriorityProcess->burstTime;
                completed[highestPriorityProcess->ID] = true;
                remainingProcesses--;
            }
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

        if(simulation){
            // Print Gantt Chart
            cout << "\nGantt Chart:\n|";
            for (const auto& entry : ganttChart) {
                cout << "  " << entry.first << "  |";
            }
            cout << "\n0";
            for (const auto& entry : ganttChart) {
                cout << "      " << entry.second;
            }
            cout << "\n";
        
            // Print detailed information
            cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tResponse Time\tCompletion Time\n";
            for (const Process* process : processes) {
                cout << process->ID << "\t\t" << process->arrivalTime << "\t\t" << process->burstTime << "\t\t" << process->priority << "\t\t" 
                     << process->waitingTime << "\t\t" << process->turnaroundTime << "\t\t" 
                     << process->responseTime << "\t\t" << process->completionTime << "\n";
            }
        
            cout << "\nAverage Waiting Time: " << avgWaitingTime << "\n";
            cout << "Average Turnaround Time: " << avgTurnaroundTime << "\n";
            cout << "Average Response Time: " << avgResponseTime << "\n";
        }

        return new Summary(avgWaitingTime, avgTurnaroundTime, avgResponseTime);
    }
 
    Summary* srtf() {
        // Sort processes based on arrival time
        sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
            return a->arrivalTime < b->arrivalTime;
        });
    
        map<string, int> remainingBurstTime;
        map<string, bool> completed;
        int remainingProcesses = processes.size();
        int currentTime = 0;
        vector<pair<string, int>> ganttChart;
    
        // Initialize remaining burst times
        for (Process* process : processes) {
            remainingBurstTime[process->ID] = process->burstTime;
        }
    
        while (remainingProcesses > 0) {
            Process* shortestProcess = nullptr;
    
            // Find the process with the shortest remaining burst time that has arrived
            for (Process* process : processes) {
                if (process->arrivalTime <= currentTime && !completed[process->ID]) {
                    if (shortestProcess == nullptr || remainingBurstTime[process->ID] < remainingBurstTime[shortestProcess->ID]) {
                        shortestProcess = process;
                    }
                }
            }
    
            if (shortestProcess == nullptr) {
                currentTime++;
                continue;
            }
    
            // Process execution
            if (shortestProcess->responseTime == -1) {
                shortestProcess->responseTime = currentTime - shortestProcess->arrivalTime;
            }
    
            remainingBurstTime[shortestProcess->ID]--;
            currentTime++;
            ganttChart.push_back({shortestProcess->ID, currentTime});
    
            if (remainingBurstTime[shortestProcess->ID] == 0) {
                shortestProcess->completionTime = currentTime;
                shortestProcess->turnaroundTime = shortestProcess->completionTime - shortestProcess->arrivalTime;
                shortestProcess->waitingTime = shortestProcess->turnaroundTime - shortestProcess->burstTime;
                completed[shortestProcess->ID] = true;
                remainingProcesses--;
            }
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


        if(simulation){
            // Print Gantt Chart
            cout << "\nGantt Chart:\n|";
            for (const auto& entry : ganttChart) {
                cout << "  " << entry.first << "  |";
            }
            cout << "\n0";
            for (const auto& entry : ganttChart) {
                cout << "      " << entry.second;
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
