#ifndef SCHEDULER_H
#define SCHEDULER_H


#include "process.h"
#include <vector>

class Scheduler {
    public:
        virtual std::pair<Process*, int> schedule(std::vector<Process>& ready_queue, int current_t) = 0;
        virtual ~Scheduler() = default;
};

#endif
