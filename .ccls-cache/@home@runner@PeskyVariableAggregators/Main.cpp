#include "Process.h"
#include "Simulation.h"
#include "Comparison.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<Process*> processes; 
    int n;
    int choice;
    cout << "Enter the number of processes:" << endl;
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

    cout<<"Enter 1 for simulation, 2 for comparison:";
    cin>>choice;
    if(choice==1){
      Simulation* app = new Simulation(processes);
      app->run();
      delete app;
    }
    else if(choice==2){
      Comparison* app = new Comparison(processes);
      app->run();
      delete app;
    }

    for (Process* p : processes) {
        delete p;
    }

    return 0;
}