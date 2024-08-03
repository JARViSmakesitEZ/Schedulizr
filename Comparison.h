#ifndef COMPARISON_H
#define COMPARISON_H

#include <bits/stdc++.h>
#include <thread>
#include "Process.h"
#include "Preemptive.h"
#include "NonPreemptive.h"
#include "Summary.h"

using namespace std;

class Comparison {
    vector<Process*> processes;

    Summary* runFunction(function<Summary*()> func) {
        return func();
    }

    void printSummary(const string& algoName, Summary* summary) {
        cout << setw(15) << left << algoName
             << setw(20) << left << summary->avgWaitingTime
             << setw(20) << left << summary->avgTurnaroundTime
             << setw(20) << left << summary->avgResponseTime << endl;
    }

public:
    Comparison(vector<Process*> processes) : processes(processes) {}

    void run() {
        // Create copies of processes for each algorithm
        vector<Process*> processesFCFS = processes;
        vector<Process*> processesSJF = processes;
        vector<Process*> processesNPPriority = processes;
        vector<Process*> processesRR = processes;
        vector<Process*> processesSRTF = processes;
        vector<Process*> processesPPriority = processes;

        // Create Summary pointers to hold results
        Summary* summaryFCFS = nullptr;
        Summary* summarySJF = nullptr;
        Summary* summaryNPPriority = nullptr;
        Summary* summaryRR = nullptr;
        Summary* summarySRTF = nullptr;
        Summary* summaryPPriority = nullptr;

        // Create threads for each scheduling algorithm
        thread t1([&]() { summaryFCFS = fcfs(processesFCFS); });
        thread t2([&]() { summarySJF = sjf(processesSJF); });
        thread t3([&]() { summaryNPPriority = priorityNonPreemptive(processesNPPriority); });
        thread t4([&]() { summaryRR = roundRobin(processesRR); });
        thread t5([&]() { summarySRTF = srtf(processesSRTF); });
        thread t6([&]() { summaryPPriority = priorityPreemptive(processesPPriority); });

        // Wait for all threads to complete
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();

        // Print the results in a nice table
        cout << setw(15) << left << "Algorithm"
             << setw(20) << left << "Avg Waiting Time"
             << setw(20) << left << "Avg Turnaround Time"
             << setw(20) << left << "Avg Response Time" << endl;
        cout << string(75, '-') << endl;

        printSummary("FCFS", summaryFCFS);
        printSummary("SJF", summarySJF);
        printSummary("Non-Preemptive Priority", summaryNPPriority);
        printSummary("Round Robin", summaryRR);
        printSummary("SRTF", summarySRTF);
        printSummary("Preemptive Priority", summaryPPriority);

        // Clean up allocated memory
        delete summaryFCFS;
        delete summarySJF;
        delete summaryNPPriority;
        delete summaryRR;
        delete summarySRTF;
        delete summaryPPriority;
    }
};

#endif // COMPARISON_H
