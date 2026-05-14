#ifndef PROCESS_H
#define PROCESS_H

enum class State { Ready, Running, Completed };

struct  Process {
int pid;
int arr_t; //Arrival Time
int burst_t;
int oburst_t; //Original Burst Time
int priority;
State state;
};

#endif
