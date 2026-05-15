#include "metrics.h"
#include "process.h"
#include "scheduler.h"
#include "simulation.h"
#include <vector>
#include <algorithm>

std::vector<Cprocess> simulate(std::vector<Process>& process_queue, Scheduler* scheduler) {
    int current_t = 0;
    int completed_p = 0;
    std::vector<Process> ready_queue;
    std::vector<Cprocess> output;
    while(completed_p < (int)process_queue.size()) {
        for(Process& pr : process_queue) {
            if(pr.arr_t < current_t && pr.state == State::NotArrived) {
                ready_queue.push_back(pr);
                pr.state = State::Ready;
            }
        }
        
        Cprocess temp_pr = {0,0,0,0,0,0};
        auto sched_pr = scheduler->schedule(ready_queue, current_t);

        if(sched_pr.first == nullptr) {
            current_t += sched_pr.second;
            continue;
        }

        sched_pr.first->state = State::Running;
        temp_pr.pid = sched_pr.first->pid;

        if(sched_pr.first->burst_t == sched_pr.first->oburst_t) temp_pr.f_cpu_t = current_t;
        
        sched_pr.first->burst_t -= sched_pr.second;
        current_t += sched_pr.second;

        if(sched_pr.first->burst_t == 0) {
            sched_pr.first->state = State::Completed;
            //Removing the now completed process from ready queue
            ready_queue.erase(
              std::remove_if(ready_queue.begin(), ready_queue.end(), 
              [&](const Process& pr) {
             return pr.pid == sched_pr.first->pid;
                 }),
               ready_queue.end()
            );
            temp_pr.cmp_t = current_t;
            temp_pr.trnard_t = temp_pr.cmp_t - sched_pr.first->arr_t;
            temp_pr.wt_t = temp_pr.trnard_t - sched_pr.first->oburst_t;
            temp_pr.response_t = temp_pr.f_cpu_t - sched_pr.first->arr_t;
            completed_p += 1;
        }
        else sched_pr.first->state = State::Ready;
        
        int match = 0;
        for(Cprocess& pr : output) {
            if(pr.pid == temp_pr.pid) {
                pr.f_cpu_t = temp_pr.f_cpu_t;
                pr.cmp_t = temp_pr.cmp_t;
                pr.trnard_t = temp_pr.trnard_t;
                pr.wt_t = temp_pr.wt_t;
                pr.response_t = temp_pr.response_t;
                match += 1;
            }
        }
        if(match == 0) output.push_back(temp_pr); 
    }

    for(Process& pr : process_queue) {
        pr.burst_t = pr.oburst_t;
        pr.state = NotArrived;
        pr.priority = 0;
    }

    return output;
}
