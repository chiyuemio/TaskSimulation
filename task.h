// task.h
#ifndef TASK_H
#define TASK_H

#include <stdbool.h>

#define SIMULATION_TIME 57
#define TASKS_NUM 5
#define M 2
#define K 5
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
    {1,1,8,3,true,1,0,0,0,0,true},
    {2,3,13,3,false,3,0,0,0,0,true},
    {3,1,18,8,true,1,0,0,0,0,true},
    {4,2,18,15,true,2,0,0,0,0,true},
    {5,4,19,7,false,4,0,0,0,0,true},
    };

void init();

#endif

