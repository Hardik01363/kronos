# Kronos:

## Why this name?
In Greek Mythology, Kronos is titled as theGod of Time. Since my project is based on CPU Scheduling algorithms, and, CPU time is the resource that these scheduling algorithms hope to utilise efficiently, thus this  seemed to be an appropriate name.

## What does Kronos do?
In Kronos, 4 CPU scheduling algorithms (namely FCFS, SJF, RR, MLFQ) have been implemented and are compared based on various metrics for a set of processes given by the user. User input can be taken in 3 ways.
1. User can input structs for each process of the form (PID, Arrival Time, Burst Time). Default Priority will be set to 0 and changed by MLFQ algorithm. Default initial state will be ready.
2. User can enter a file containing all the processes' information.
3. User can enter an integer and that many number of processes with random initial values will be used.\
The Processes deliberately do not contain any information about I/O time as including I/O and Blocking processes for it will not add much meaningful value to our metrics, as, the main target of Kronos is to compare the different algorithms, not simulate a scheduler. Also, the task of simulating hardware interrupts that trap into the OS and the return-from-trap instructions would add many more levels of complexity, destroying the elegance of the simulation.

## Time quantum benchmarking in RR
In the RR implementation, Kronos doesnt use a predefined Time quantum value, but, tests on various values for it and chooses the best performing one. The metrics for all the tried time quantum values will also be provided. I chose this form of implementation of RR despite its additional complexity as it provides a significant and meaningful boost to the performance of RR algorithm, and, in turn, also boosts performance for MLFQ as well.

## Simulation Model
For the simulation model, I had 2 options, tick-based or event-based scheduling. I debated this decision for a while and then landed on the conclusion that tick-based scheduling would be a better fit for my project as it is more ideal for periodic tasks, highly predictable and deterministic, unlike the event-based approach. Also, tick-based scheduling has needs less overheads in scheduling the processes and thus would keep our metrics closer to real hardware implementation.

## Process struct
The process struct will contain the following fields:
1. PID: An integer process identifier to differentiate between the processes.
2, Arrival Time: The time at which the process entered the CPU.
3. Burst Time: The time for which the process needs to run on the CPU. It will get deducted each time the process runs for some time and when it hits 0, the process state will change to completed. This value will not be accessed by any algorithm except SJF, but, the signal to change process state to completed will be sent and used for all the 4 algorithms.
4. Original Burst Time: This value will be initialised to the value of the burst time provided by the user. This will be used later during the simulation and metrics calculation, but, will be a constant value throughout.
5. Priority: This value will not be given by User and its initial default value will be set to 0. This  value will be used and dynamically changed by the MLFQ algorithm.
6. enum State: The state enum will have 3 possible states to be in (ready, running, completed). We have no need for a blocked state as we are not considering I/O in our metrics calculations.
Note: Completion time is deliberately left out as it is a result of our simulation and not a part of user input

## Scheduler interface
The base scheduler interface will consist of a part taking in the user input in one of the 3 provided ways they prefer. Then, it will simulate the processes running in all the 4 algorithms and then provide the relevant graphs and metrics and comparison tables for all the 4 processes. Every scheduler implements a schedule() method that takes the ready queue and current time and returns the next process to run. This process is facilitated by the base scheduler by arranging these function calls and storing the outputs of these calls in the corresponding structs.

## Metrics
For the metrics, Kronos will give out a complete table of the turnaround time, response time and waiting time for each process, for each algorithm. It will also show the comparisons if these values across the 4 processes. These values will be stored in a struct specifically designed for simulation output and result values (completion time, turnaround time, waiting time, response time). Also, tables and graphs containing information about the RR algorith for the different tested values of time quantum and the final selected values for shortest turnaround time, response time and waiting time will also be provided. Generally, when response time needs to be reduced, the turnaround time would in turn increase and vice versa. This a commonly presented tradeoff for interactivity Vs progress visibility in scheduling algorithms. So, for our cross algorithm comparison, we will use the time quantum value that minimises the value (turnaround time + response time)/2 due to its simplicity of implementation and gives equal weighted importance to both the metrics as we have no context about what type of system these schedules are implemented are and what they are optimizing for.
- turnaround time = completion time - arrival time
- waiting time = turnaround time - original burst time
- response time = time of first CPU run - arrival time
## MLFQ Specs
For implementing MLFQ, a lot of decisions and tradeoffs had to be made and considered. The number of queues I've decided upon is 5, as it is neither too short to not be able to distinguish the processes, nor is it too large, making the number of parameters manageable to tune. Time quantum value for the highest priority queue would be decided by the RR algorithm run for that queue, and for those after that, it will be 1.25 times the previous queue's value, as, generally, more interactive processes needing shorter response time reside in the top layers while the more computationally heavy processes needing less response time fall down to the lower priority queues. A process will be demoted in priority after running for 1.5 times the amount of time as the time quantum value for that level. This value will be calculated as a cumulative of multiple CPU runs on that level, as, resetting it after each run woul make the Scheduler gameable so that a process would be able to hod the CPU by running for about 99% of the demotion time value and thus staying in the higher levels of priority. After every 4 time slice values of the lowest priority level, all processes will be promoted to the highest priority level to prevent starvation of lower priority processes and also to account for possible change in behaviour of processes from computationally expensive to more interactive. Even though we are not accounting for I/O, the decisions made in MLFQ reflect those of real-world algorithm concerened about I/O too, as, this would help push the metric towards those of actual schedulers implemented on hardware.

## Why no overhead for context switches?
A decision that I debated upon was whether i should add an overhead for each context switch, as, different algorithms use different number of switches to complete a certain set of processes. But, the overhead of a context switch depends on far too many factors, what the state and specifics of the hardware are, what the state of the TLB is, etc. and thus no standard value could be referred to as a context switch could take anywhere from a few nanoseconds to tens of microseconds. Thus, I decided that adding in a value for simulating the cost of the overhead would add noise in the metrics and would do more harm than good and decided not to add it into my calculations despite its simplicity of implementation.
