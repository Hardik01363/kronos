#ifndef RR_H
#define RR_H

#include "../process.h"
#include "../scheduler.h"
#include <vector>

class RR : public Scheduler {
    int quantum;
public:
    RR(int quantum) : quantum(quantum) {}
    std::pair<Process*, int> schedule(std::vector<Process>& ready_queue, int current_t) override;
};

#endif
