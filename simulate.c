// simulate.c
#include <stdio.h>
#include "task.h"
#include <stdbool.h>
#include <assert.h>
#include "simulate.h"
#include "scheduler.h"

void simulate(int taskId, Scheduler* scheduler) { //taskId: the index of a task in tasks; to check the task whose deadline misses if it satisfies the (m,k) constraint.

    //job-continue strategy: continue the job execution until completion even if its dealine is missed.

    int time = 0;
    int exTask = TASKS_NUM; //the index of the task that are running
    int execution; //execution=1 cpu is occupied； execution=0 cpu idle
    int deadlineMiss[K];
    for(int i=0; i<K; i++){
        deadlineMiss[i]=0;
    }

    scheduler->init(scheduler, tasks);
    while (time < SIMULATION_TIME) {
        scheduler->schedule(scheduler, tasks, time);

        execution = 0; //When execution equals 0, cpu is idling; When execution equals 1, there is a task executing.
        /*
        for (int i = 0; i < TASKS_NUM; i++) { //choosing a task to execute.
            if (tasks[i].nextStart <= time && tasks[i].remaining > 0 && i <= exTask) {
                exTask = i;
                execution = 1;
                break;
            }
        }
        */

        if (scheduler->exTask < TASKS_NUM && tasks[scheduler->exTask].remaining > 0) {
            execution = 1;
        }

        if (execution == 1) {

            tasks[scheduler->exTask].remaining--;

            if(tasks[scheduler->exTask].remaining == 0){

                if(scheduler->exTask == taskId){

                    int deadlineMissCount = 0;

                    if(time > tasks[scheduler->exTask].abDeadline){
                        deadlineMiss[tasks[scheduler->exTask].count % K]=1;
                    }else{
                        deadlineMiss[tasks[scheduler->exTask].count % K]=0;
                    }

                    for(int i=0; i<K; i++){
                        deadlineMissCount += deadlineMiss[i];
                    }

                    if(deadlineMissCount > M){
                        tasks[scheduler->exTask].flag=false;
                        break;
                    }

                }

                tasks[scheduler->exTask].count++;
                tasks[scheduler->exTask].nextStart += tasks[scheduler->exTask].period;
                tasks[scheduler->exTask].abDeadline += tasks[scheduler->exTask].period;
                tasks[scheduler->exTask].remaining = tasks[scheduler->exTask].wcet;
                scheduler->exTask = TASKS_NUM;
            }

        }else {
            scheduler->exTask = TASKS_NUM;
        }
        time++;
    }
}

