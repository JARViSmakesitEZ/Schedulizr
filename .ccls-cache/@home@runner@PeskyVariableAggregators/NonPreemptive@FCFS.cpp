#include "../Process.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<Process*> processes; 
    int n;
    cout << "Enter the number of processes:" << std::endl;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time, burst time and priority for process " << (i + 1) << ":" << endl;
        int arrivalTime;
        int burstTime;
        int priority;
        cin >> arrivalTime >> burstTime >> priority;

        string processName = "P" + to_string(i + 1);
        processes.push_back(new Process(processName.c_str(), arrivalTime, burstTime,priority));
    }


  

    for (Process* p : processes) {
        delete p;
    }

    return 0;
}
