#include "../process.h"
#include "../scheduler.h"
#include "sjf.h"
#include <vector>
#include <limits.h>

std::pair<Process*, int> SJF::schedule(std::vector<Process>& ready_queue, int current_time) {
    (void)current_time;
    int min_burst_t = INT_MAX;
    Process* ptr_min_burst_t = nullptr;
    int obt = 1;
    for(auto& pr : ready_queue) {
        if(pr.burst_t < min_burst_t) {
            min_burst_t = pr.burst_t;
            obt = pr.oburst_t;
            ptr_min_burst_t = &pr;
        }
    }
    auto sched_pr = std::make_pair(ptr_min_burst_t, obt);
    return sched_pr;
}
