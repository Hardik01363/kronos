#ifndef METRICS_H
#define METRICS_H

struct Cprocess { //Cprocess abbrevating for completed process
int pid;
int f_cpu_t; //time stamp of first cpu usage
int cmp_t; //Completion time
int trnard_t; //=cmp_t-arr_t
int wt_t; //=trnard_t-oburst_t
int response_t; //=f_cpu_t-arr_t
};

#endif
