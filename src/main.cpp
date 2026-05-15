#include "process.h"
#include "scheduler.h"
#include "simulation.h"
#include "schedulers/fcfs.h"
#include "schedulers/sjf.h"
#include "schedulers/rr.h"
#include "schedulers/mlfq.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

std::vector<Process> input1() {
    std::vector<Process> pq;
    std::cout << "How many processes do you want to simulate? (Please enter a positive integer)" << std::endl;
    int num_pr; std::cin >> num_pr;
    while(1) {
        if(!std::cin || num_pr <= 0) {
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
            if(!std::cin || pid < 0) {
                std::cin.clear(); std::cin.ignore();
                std::cout << "Please enter a valid number" << std::endl;
                std::cin >> pid;
            }
            else break;
        }
        std::cout << "Please enter Arrival Time. (Please enter a positive integer or 0)" << std::endl;
        int arr_t; std::cin >> arr_t;
        while(1) {
            if(!std::cin || arr_t < 0) {
                std::cin.clear(); std::cin.ignore();
                std::cout << "Please enter a valid number" << std::endl;
                std::cin >> arr_t;
            }
            else break;
        }
        std::cout << "Please enter Burst Time. (Please enter a positive integer)" << std::endl;
        int burst_t; std::cin >> burst_t;
        while(1) {
            if(!std::cin || burst_t <= 0) {
                std::cin.clear(); std::cin.ignore();
                std::cout << "Please enter a valid number" << std::endl;
                std::cin >> burst_t;
            }
            else break;
        }
        Process temp = {pid, arr_t, burst_t, burst_t, 0, State::NotArrived};
        pq.push_back(temp);
    }
    return pq;
}

std::vector<Process> input2() {
    std::vector<Process> pq;
    std::string filename;
    
    std::cout << "Please enter the filename." << std::endl;
    std::cin >> filename;
    
    std::ifstream file(filename);
    
    while(1) {
        if(!file.is_open()) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Please enter a valid filename" << std::endl;
            std::cin >> filename;
            file.open(filename);
        }
        else break;
    }
    
    int pid, arr_t, burst_t;
    
    while(file >> pid >> arr_t >> burst_t) {
        Process temp = {pid, arr_t, burst_t, burst_t, 0, State::NotArrived};
        pq.push_back(temp);
    }
    
    return pq;
}

std::vector<Process> input3() {
    std::vector<Process> pq;
    
    std::cout << "How many processes do you want to simulate? (Please enter a positive integer)" << std::endl;
    int num_pr; std::cin >> num_pr;
    
    while(1) {
        if(!std::cin || num_pr <= 0) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Please enter a valid number" << std::endl;
            std::cin >> num_pr;
        }
        else break;
    }
    
    srand(time(0));
    
    for(int i = 1; i <= num_pr; i++) {
        int arr_t = rand() % 50;
        int burst_t = (rand() % 20) + 1;
        
        Process temp = {i, arr_t, burst_t, burst_t, 0, State::NotArrived};
        pq.push_back(temp);
    }
    
    return pq;
}

void print_table(const std::vector<Cprocess>& data) {
    std::cout << "PID\tCompletion\tTurnaround\tWaiting\tResponse" << std::endl;
    for(const auto& pr : data) {
        std::cout << pr.pid << "\t" 
                  << pr.cmp_t << "\t\t" 
                  << pr.trnard_t << "\t\t" 
                  << pr.wt_t << "\t" 
                  << pr.response_t << std::endl;
    }
}

void print_rr_table(const std::vector<std::vector<Cprocess>>& rr_data) {
    std::cout << "Enter 0 to print all quantums, or 1-16 for a specific quantum:" << std::endl;
    int q; std::cin >> q;
    
    while(1) {
        if(!std::cin || q < 0 || q > 16) {
            std::cin.clear(); 
            std::cin.ignore();
            std::cout << "Please enter a valid number" << std::endl;
            std::cin >> q;
        }
        else break;
    }
    
    if(q == 0) {
        for(int i = 0; i < 16; i++) {
            std::cout << "RR Quantum " << i + 1 << ":" << std::endl;
            print_table(rr_data[i]);
            std::cout << std::endl;
        }
    } else {
        std::cout << "RR Quantum " << q << ":" << std::endl;
        print_table(rr_data[q-1]);
    }
}

void print_mlfq_table(const std::vector<std::vector<Cprocess>>& mlfq_data) {
    std::cout << "Enter 0 to print all quantums, or 1-16 for a specific quantum:" << std::endl;
    int q; std::cin >> q;
    
    while(1) {
        if(!std::cin || q < 0 || q > 16) {
            std::cin.clear(); 
            std::cin.ignore();
            std::cout << "Please enter a valid number" << std::endl;
            std::cin >> q;
        }
        else break;
    }
    
    if(q == 0) {
        for(int i = 0; i < 16; i++) {
            std::cout << "MLFQ Highest Priority Quantum " << i + 1 << ":" << std::endl;
            print_table(mlfq_data[i]);
            std::cout << std::endl;
        }
    } else {
        std::cout << "MLFQ Highest Priority Quantum " << q << ":" << std::endl;
        print_table(mlfq_data[q-1]);
    }
}

int analyze_best_quantum(const std::vector<std::vector<Cprocess>>& data) {
    int best_q = 1;
    double min_metric = -1;
    
    for(int i = 0; i < 16; i++) {
        double total_tr = 0;
        double total_resp = 0;
        double n = data[i].size();
        
        if(n == 0) continue;
        
        for(const auto& pr : data[i]) {
            total_tr += pr.trnard_t;
            total_resp += pr.response_t;
        }
        
        double metric = ((total_tr / n) + (total_resp / n)) / 2.0;
        
        if(min_metric == -1 || metric < min_metric) {
            min_metric = metric;
            best_q = i + 1;
        }
    }
    
    return best_q;
}

void compare_algorithms(const std::vector<Cprocess>& fcfs, const std::vector<Cprocess>& sjf, const std::vector<std::vector<Cprocess>>& rr, const std::vector<std::vector<Cprocess>>& mlfq) {
    int best_rr = analyze_best_quantum(rr);
    int best_mlfq = analyze_best_quantum(mlfq);
    
    std::cout << "\n--- Cross Algorithm Comparison ---" << std::endl;
    
    std::cout << "\nFCFS:" << std::endl;
    print_table(fcfs);
    
    std::cout << "\nSJF:" << std::endl;
    print_table(sjf);
    
    std::cout << "\nBest RR (Quantum " << best_rr << "):" << std::endl;
    print_table(rr[best_rr-1]);
    
    std::cout << "\nBest MLFQ (Quantum " << best_mlfq << "):" << std::endl;
    print_table(mlfq[best_mlfq-1]);
}

int main() {
    std::vector<Process> process_queue;
    std::cout << "Welcome to Kronos. Please input a number for the method of inputting processes you want to use for this simulation." << std::endl;
    std::cout << "1. Input process structs manually" << std::endl;
    std::cout << "2. Input a File with the process structs in it in the predefined format found in README.md" << std::endl;
    std::cout << "3. Input a number and that many processes with random initial vlaues (within an appropriate range) will be generated" << std::endl;
    int input_method; std::cin >> input_method;
    while(1) {
        if(!std::cin || input_method < 1 || input_method > 3) {
            std::cin.clear(); std::cin.ignore();
            std::cout << "Please enter a valid number" << std::endl;
            std::cin >> input_method;
        }
        else break;
    }
    if(input_method == 1) process_queue = input1();
    else if(input_method == 2) process_queue = input2();
    else if(input_method == 3) process_queue = input3();
    
    std::cout << "Simulating FCFS....." << std::endl;

    FCFS fcfs_sched;
    std::vector<Cprocess> fcfs_data = simulate(process_queue, &fcfs_sched);

    std::cout << "Simulating SJF....." << std::endl;

    SJF sjf_sched;
    std::vector<Cprocess> sjf_data = simulate(process_queue, &sjf_sched);

    std::cout << "Simulating RR and Benchmarking Quantum Value....." << std::endl;

    std::vector<std::vector<Cprocess>> rr_data;
    for(int i=1; i<=16; i++) {
        RR rr_sched(i);
        std::vector<Cprocess> rr_quan_data = simulate(process_queue, &rr_sched);
        rr_data.push_back(rr_quan_data);
    }

    std::cout << "Simulating MLFQ and Benchmarking Highest Priority Queue Quantum Value....." << std::endl;

    std::vector<std::vector<Cprocess>> mlfq_data;
    for(int i=1; i<=16; i++) {
        MLFQ mlfq_sched(i);
        std::vector<Cprocess> mlfq_quan_data = simulate(process_queue, &mlfq_sched);
        mlfq_data.push_back(mlfq_quan_data);
    }

    int choice = -1;
    while(1) {
        std::cout << "\nWhat metrics would you like to see?" << std::endl;
        std::cout << "1. FCFS Tabular Data" << std::endl;
        std::cout << "2. SJF Tabular Data" << std::endl;
        std::cout << "3. RR Tabular Data" << std::endl;
        std::cout << "4. MLFQ Tabular Data" << std::endl;
        std::cout << "5. Best Time Quantum Analysis for RR" << std::endl;
        std::cout << "6. Best Time Quantum Analysis for MLFQ" << std::endl;
        std::cout << "7. Cross-Algorithm Comparison" << std::endl;
        std::cout << "0. Exit" << std::endl;
        
        std::cin >> choice;
        
        while(1) {
            if(!std::cin || choice < 0 || choice > 7) {
                std::cin.clear(); 
                std::cin.ignore();
                std::cout << "Please enter a valid number" << std::endl;
                std::cin >> choice;
            }
            else break;
        }
    
        if(choice == 0) break;
        else if(choice == 1) print_table(fcfs_data);
        else if(choice == 2) print_table(sjf_data);
        else if(choice == 3) print_rr_table(rr_data);
        else if(choice == 4) print_mlfq_table(mlfq_data);
        else if(choice == 5) {
            int best = analyze_best_quantum(rr_data);
            std::cout << "Best Time Quantum for RR is: " << best << std::endl;
        }
        else if(choice == 6) {
            int best = analyze_best_quantum(mlfq_data);
            std::cout << "Best Highest Priority Time Quantum for MLFQ is: " << best << std::endl;
        }
        else if(choice == 7) compare_algorithms(fcfs_data, sjf_data, rr_data, mlfq_data);
    }
    return 0;
}
