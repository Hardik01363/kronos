#include "../process.h"
#include "../scheduler.h"
#include "fcfs.h"
#include <vector>
#include <limits.h>

std::pair<Process*, int> FCFS::schedule(std::vector<Process>& ready_queue, int current_time) {
    int min_arr_t = INT_MAX;
    Process* ptr_min_arr_t = nullptr;
    for(auto& pr : ready_queue) {
        if(pr.arr_t < min_arr_t) {
            min_arr_t = pr.arr_t;
            ptr_min_arr_t = &pr;
        }
    }
    auto sched_pr = std::make_pair(ptr_min_arr_t, oburst_t);
    return sched_pr
}
