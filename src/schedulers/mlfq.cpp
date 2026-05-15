#include "../process.h"
#include "../scheduler.h"
#include "mlfq.h"
#include <vector>
#include <cmath>
#include <algorithm>

std::pair<Process*, int> MLFQ::schedule(std::vector<Process>& ready_queue, int current_t) {
    int fifth_quan = static_cast<int>(std::round(pow(1.25,4)*quantum));
    int reset_t = 4*fifth_quan;
    if(current_t/reset_t > cycle_no){
        cycle_no = current_t/reset_t;
        for(Process& pr : ready_queue) pr.priority = 0;
    }

    if(ready_queue.empty()) {
        auto proc = std::make_pair(nullptr, 1);
        return proc;
    }

    int comparator = 5;
    Process* ptr_sched_pr = nullptr;
    int runtime = 1;
    for(Process& pr : ready_queue) {
        if(pr.priority < comparator) {
            comparator = pr.priority;
            ptr_sched_pr = &pr;
            runtime = std::min(static_cast<int>(std::round(pow(1.25, pr.priority)*quantum)), pr.burst_t);
        }
    }
    if(ptr_sched_pr->priority < 4) ptr_sched_pr->priority += 1;
    auto sched_pr = std::make_pair(ptr_sched_pr, runtime);
    return sched_pr;
}
