#include "../process.h"
#include "../scheduler.h"
#include "rr.h"
#include <vector>
#include <algorithm>

std::pair<Process*, int> RR::schedule(std::vector<Process>& ready_queue, int current_t) {
    (void)current_t;
    if(ready_queue.empty()) {
        auto proc = std::make_pair(nullptr, 1);
        return proc;
    }
    Process spr = ready_queue.front(); //scheduled process
    ready_queue.erase(ready_queue.begin());
    ready_queue.push_back(spr);
    Process* ptr = &ready_queue.back();
    int runtime = std::min(quantum, ready_queue.back().burst_t);
    auto sched_pr = std::make_pair(ptr, runtime);
    return sched_pr;
}
