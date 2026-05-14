#ifndef FCFS_H
#define FCFS_H

#include "process.h"
#include "../scheduler.h"
#include <vector>

class FCFS : public Scheduler {
    public:
        Process* schedule(std::vector<Process>& ready_queue, int current_t) override;
};

#endif
