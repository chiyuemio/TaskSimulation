// task.h
#ifndef TASK_H
#define TASK_H

#include <stdbool.h>

#define SIMULATION_TIME 72
#define TASKS_NUM 5
#define M 1
#define K 3
#define NUMBER 4

typedef struct {
    int id;
    int wcet;
    int period;
    int deadline;
    bool schedulable;
    int remaining;
    int nextStart;
    int activation;
    int abDeadline;
    int count;
    bool flag;
} Task;

extern Task tasks[TASKS_NUM];

Task tasks[TASKS_NUM] = {
    {1,1,5,3,true,1,0,0,0,0,true},
    {2,2,12,2,false,2,0,0,0,0,true},
    {3,1,14,10,true,1,0,0,0,0,true},
    {4,1,14,5,true,1,0,0,0,0,true},
    {5,2,18,16,true,2,0,0,0,0,true},
    };

void init();

#endif

