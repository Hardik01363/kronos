//include statements

std::vector<Cprocess> simulate(std::vector<Process>& process_queue, Scheduler* scheduler) {
    int current_t = 0;
    int completed_p = 0;
    std::vector<Process> ready_queue;
    while(completed_p < process_queue.size()) {
        for(pr:std::vector<Process.& process_queue) {
            if(pr.arr_t < current_t && pr.state == NotArrived) {
                ready_queue.push_back(pr);
                pr.state = Ready;
            }
        }
        pair<pr*, run_t> sched_pr = scheduler.schedule(ready_queue, current_t);

        
    }

}

//simulation loop starts

//checking current conditions and calling schedule()

//setting values through newfound info

//getting out of the loop, storing all the values in respective data sttructures, resetting the input struct's values for use by the next algorithm
