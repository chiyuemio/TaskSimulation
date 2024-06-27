#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

typedef struct Scheduler {
    void (*init)(struct Scheduler* self, Task* tasks);
    void (*schedule)(struct Scheduler* self, Task* tasks, int time);
    int exTask;
} Scheduler;

void rms_init(Scheduler* self, Task* tasks);
void rms_schedule(Scheduler* self, Task* tasks, int time);

void fifo_init(Scheduler* self, Task* tasks);
void fifo_schedule(Scheduler* self, Task* tasks, int time);

void edf_init(Scheduler* self, Task* tasks); // dynamic
void edf_schedule(Scheduler* self, Task* tasks, int time);

void rr_init(Scheduler* self, Task* tasks);
void rr_schedule(Scheduler* self, Task* tasks, int time);

#endif