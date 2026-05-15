#include "process.h"
#include "scheduler.h"
#include "simulation.h"
#include <iostream>
#include <vector>

std::vector<Process> input1() {
    std::vector<Process> pq;
    std::cout << "How many processes do you want to simulate? (Please enter a positive integer)" << std::endl;
    int num_pr; std::cin >> num_pr;
    while(1) {
        if(!cin || num_pr <= 0) {
            std::cin.clear(); std::cin.ignore();
            std::cout << "Please enter a valid number" << std::endl;
            std::cin >> num_pr;
        }
        else break;
    }
    for(int i=0; i<num_pr; i++) {
        std::cout << "Please enter PID. (Please enter a positive integer or 0)" << std::endl;
        int pid; std::cin >> pid;
        while(1) {
            if(!cin || pid < 0) {
                std::cin.clear(); std::cin.ignore();
                std::cout << "Please enter a valid number" << std::endl;
                std::cin >> pid;
            }
            else break;
        }
        std::cout << "Please enter Arrival Time. (Please enter a positive integer or 0)" << std::endl;
        int arr_t; std::cin >> arr_t;
        while(1) {
            if(!cin || arr_t < 0) {
                std::cin.clear(); std::cin.ignore();
                std::cout << "Please enter a valid number" << std::endl;
                std::cin >> arr_t;
            }
            else break;
        }
        std::cout << "Please enter Burst Time. (Please enter a positive integer)" << std::endl;
        int burst_t; std::cin >> burst_t;
        while(1) {
            if(!cin || burst_t <= 0) {
                std::cin.clear(); std::cin.ignore();
                std::cout << "Please enter a valid number" << std::endl;
                std::cin >> burst_t;
            }
            else break;
        }
        Process temp = {pid, arr_t, burst_t, burst_t, 0, NotArrived};
        pq.push_back(temp);
    }
    return pq
}

std::vector<Process> input2() {
    std::vector<Process> pq;
    //Implement file input and parsing
}

std::vector<Process> input3() {
    std::vector<Process> pq;
    //Implement random number generator and also decide appropriate ranges for the processes' values
}

int main() {
    std::vector<Process> process_queue;
    std::cout << "Welcome to Kronos. Please input a number for the method of inputting processes you want to use for this simulation." << std::endl;
    std::cout << "1. Input process structs manually" << std:::endl;
    std::cout << "2. Input a File with the process structs in it in the predefined format found in README.md" << std::endl;
    std::cout << "3. Input a number and that many processes with random initial vlaues (within an appropriate range) will be generated" << std::endl;
    int input_method; std::cin >> input_method;
    while(1) {
        if(!cin || input_method < 1 || input_method > 3) {
            std::cin.clear(); std::cin.ignore();
            std::cout << "Please enter a valid number" << std::endl;
            std::cin >> input_method;
        }
        else break;
    }
    if(input_method == 1) process_queue = input1();
    else if(input_method == 2) process_queue = input2();
    else if(input_method == 3) process_queue = input3();
    
    FCFS fcfs_sched;
    std::vector<Cprocess> fcfs_data = simulate(process_queue, &fcfs_sched);

    SJF sjf_sched;
    std::vector<Cprocess> sjf_data = simulate(process_queue, &sjf_sched);

    std::vector<std::vector<Cprocess>> rr_data;
    for(int i=1; i<=16; i++) {
        RR rr_sched(i);
        std::vector<Cprocess> rr_quan_data = simulate(process_queue, &rr_sched(i));
        rr_data.push_back(rr_quan_data);
    }

    std::vector<std::vector<Cprocess>> mlfq_data;
    for(int i=0; i<=16; i++) {
        MLFQ mlfq_sched(i);
        std::vector<Cprocess> mlfq_quan_data = simulate(process_queue, &mlfq_sched(i));
        mlfq_data.push_back(mlfq_quan_data);
    }
}
