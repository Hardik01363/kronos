# Kronos

## About Kronos
In Greek Mythology, Kronos is titled as the God of Time. Since my project is based on CPU Scheduling algorithms, and CPU time is the resource that these scheduling algorithms hope to utilise efficiently, this seemed to be an appropriate name.

Kronos is a tick based simulation tool designed to implement and compare 4 primary CPU scheduling algorithms: FCFS, SJF, RR, and MLFQ. The simulation focuses heavily on raw algorithm performance and deliberately excludes I/O or blocked states to keep the metrics pure and focused on comparing the algorithms directly without simulating a full scheduler.

## Features and Implementation

### Input Methods
User input can be taken in 3 ways:
1. User can input structs for each process of the form (PID, Arrival Time, Burst Time). Default Priority will be set to 0 and changed by MLFQ algorithm. Default initial state will be ready.
2. User can enter a file containing all the processes information.
3. User can enter an integer and that many number of processes with random initial values will be used.

### Process Structure
The internal process struct tracks the following fields:
* PID: An integer process identifier to differentiate between the processes.
* Arrival Time: The time at which the process entered the CPU.
* Burst Time: The time for which the process needs to run on the CPU. It will get deducted each time the process runs for some time and when it hits 0, the process state will change to completed.
* Original Burst Time: Initialised to the value of the burst time provided by the user. Kept constant for metrics calculation throughout.
* Priority: Dynamically changed by the MLFQ algorithm.
* State: Enum with 4 possible states (Ready, Running, Completed, NotArrived).

Note: Completion time is deliberately left out as it is a result of our simulation and not a part of user input.

### Scheduling Algorithms
Kronos runs the provided processes through all 4 algorithms to generate comparison metrics. Every scheduler implements a schedule() method that takes the ready queue and current time and returns the next process to run.

* Round Robin: Instead of a predefined time quantum, Kronos tests various values and chooses the best performing one. This provides a significant and meaningful boost to the performance of the RR algorithm, and, in turn, also boosts performance for MLFQ as well.
* MLFQ Specs: Implemented with 5 queues. The time quantum for the highest priority queue is decided by the best RR run. Lower priority queues have a time quantum 1.25 times the previous queue. A process is demoted after running for 1.5 times the time quantum value cumulatively to prevent gaming the Scheduler. To prevent starvation and account for possible change in behaviour of processes, all processes are promoted to the highest priority after every 4 time slice values of the lowest priority level.

### Simulation Design Choices
* Tick Based Scheduling: Chosen over event based scheduling because it is more ideal for periodic tasks, highly predictable, deterministic, and keeps metrics closer to real hardware implementations due to less overhead values.
* No Context Switch Overhead: Adding overhead would depend on too many hardware specific factors like TLB state. Including an arbitrary value for simulating the cost would add noise to the metrics and do more harm than good.

## Metrics and Output
Kronos gives out a complete table of the turnaround time, response time and waiting time for each process, for each algorithm. 

The calculated metrics include:
* Turnaround time: completion time - arrival time
* Waiting time: turnaround time - original burst time
* Response time: time of first CPU run - arrival time

For cross algorithm comparison, the simulation uses the time quantum value that minimises the average of turnaround time and response time. This represents a commonly presented tradeoff for interactivity Vs progress visibility in scheduling algorithms.

## How to build this project on your local machine


## Requirements of the build environment for Kronos


## Text file format for method 2 input

