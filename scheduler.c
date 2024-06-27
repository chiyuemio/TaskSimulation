#include "scheduler.h"
#include "utils.h"
#include <stdlib.h>

void rms_init(Scheduler* self, Task* tasks) {
    // no need for initialization
}

void rms_schedule(Scheduler* self, Task* tasks, int time) {
    int execution = 0;
    qsort(tasks, TASKS_NUM, sizeof(Task), compare_by_period);
    for (int i = 0; i < TASKS_NUM; i++) {
        if (tasks[i].nextStart <= time && tasks[i].remaining > 0) {
            self->exTask = i;
            execution = 1;
            break;
        }
    }
    if (!execution) self->exTask = TASKS_NUM;
}

void fifo_init(Scheduler* self, Task* tasks) {
    // no need for initialization
}

void fifo_schedule(Scheduler* self, Task* tasks, int time) {
    int execution = 0;
    for (int i = 0; i < TASKS_NUM; i++) {
        if (tasks[i].nextStart <= time && tasks[i].remaining > 0) {
            self->exTask = i;
            execution = 1;
            break;
        }
    }
    if (!execution) self->exTask = TASKS_NUM;
}

void edf_init(Scheduler* self, Task* tasks) {
    // no need for initialization
}

void edf_schedule(Scheduler* self, Task* tasks, int time) {
    int execution = 0;
    qsort(tasks, TASKS_NUM, sizeof(Task), compare_by_deadline);
    for (int i = 0; i < TASKS_NUM; i++) {
        if (tasks[i].nextStart <= time && tasks[i].remaining > 0) {
            self->exTask = i;
            execution = 1;
            break;
        }
    }
    if (!execution) self->exTask = TASKS_NUM;
}

void rr_init(Scheduler* self, Task* tasks) {
    self->exTask = 0;
}

void rr_schedule(Scheduler* self, Task* tasks, int time) {
    self->exTask = (self->exTask + 1) % TASKS_NUM;
    int execution = 0;
    for (int i = 0; i < TASKS_NUM; i++) {
        int idx = (self->exTask + i) % TASKS_NUM;
        if (tasks[idx].nextStart <= time && tasks[idx].remaining > 0) {
            self->exTask = idx;
            execution = 1;
            break;
        }
    }
    if (!execution) self->exTask = TASKS_NUM;
}
