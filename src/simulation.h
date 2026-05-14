#ifndef SIMULATION_H
#define SIMULATION_H

#include "process.h"
#include "metrics.h"
#include "scheduler.h"
#include <vector>

std::vector<Cprocess> simulate(std::vector<Process>& process_queue, Scheduler* scheduler);

#endif
