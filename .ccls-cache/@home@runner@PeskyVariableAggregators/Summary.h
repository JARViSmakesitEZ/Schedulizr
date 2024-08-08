#ifndef SUMMARY_H
#define SUMMARY_H
#include<iostream>
using namespace std;
struct Summary {
    double avgWaitingTime;
    double avgTurnaroundTime;
    double avgResponseTime;

    Summary(double awt, double att, double art) : avgWaitingTime(awt), avgTurnaroundTime(att), avgResponseTime(art) {}
};

#endif