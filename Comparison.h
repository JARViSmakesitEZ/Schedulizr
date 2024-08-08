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
    Preemptive* p1;
    NonPreemptive* p2;

public:
    Comparison(vector<Process*> processes) {
        this->processes = processes;
        p1 = new Preemptive(processes, false);
        p2 = new NonPreemptive(processes, false);
    }

    // Function to run the scheduling algorithm and return the Summary
    Summary* runFunction(Summary*(NonPreemptive::*func)(), NonPreemptive* scheduler) {
        return (scheduler->*func)();
    }

    void printSummary(const string& algoName, Summary* summary) {
        cout << setw(15) << left << algoName
             << setw(20) << left << summary->avgWaitingTime
             << setw(20) << left << summary->avgTurnaroundTime
             << setw(20) << left << summary->avgResponseTime << endl;
    }

public:
    void run() {
        // Create Summary pointers to hold results
        Summary* summaryFCFS = nullptr;
        Summary* summarySJF = nullptr;
        Summary* summaryNPPriority = nullptr;
        Summary* summaryRR = nullptr;
        Summary* summarySRTF = nullptr;
        Summary* summaryPPriority = nullptr;

        // Create threads for each scheduling algorithm
        thread t1([&]() { summaryFCFS = runFunction(&NonPreemptive::fcfs, p2); });
        thread t2([&]() { summarySJF = runFunction(&NonPreemptive::sjf, p2); });
        thread t3([&]() { summaryNPPriority = runFunction(&NonPreemptive::priority, p2); });
        thread t4([&]() { summaryRR = p1->roundRobin(); });
        thread t5([&]() { summarySRTF = p1->srtf(); });
        thread t6([&]() { summaryPPriority = p1->priority(); });

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
