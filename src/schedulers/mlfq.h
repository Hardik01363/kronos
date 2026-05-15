#ifndef MLFQ_H
#define MLFQ_H

#include "../process.h"
#include "../scheduler.h"
#include <vector>

class MLFQ : public Scheduler {
    int quantum;
    int cycle_no;
public:
    MLFQ(int quantum) : quantum(quantum), cycle_no(0) {}
    std::pair<Process*, int> schedule(std::vector<Process>& ready_queue, int current_t) override;
};

#endif
