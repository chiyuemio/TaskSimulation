#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <assert.h>

#define SIMULATION_TIME 200
#define UTILIZATION 1
#define TASKS_NUM 5

#define M 1
#define K 3

int hasZeroOffset = 0;

typedef struct {
    int id;
    int wcet;
    int period;
    int deadline;
    int remaining;
    int nextStart;
    int activation;
    int abDeadline;//实际deadline
    int deadlineMiss[K];//记录连续K次激活窗口，deadline miss情况
    int count;//计数任务激活的次数
    int flag;//记录该任务是否满足(m,k)限制：满足为0（初始为0），不满足为1
} Task;

int nondet_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

int compare_tasks(const void* a, const void* b) {
    Task* taskA = (Task*)a;
    Task* taskB = (Task*)b;
    return taskA->period - taskB->period;
}

void initTasks(Task* tasks){
    tasks[0].id=3;
    tasks[0].wcet=3;
    tasks[0].period=11;
    tasks[0].deadline=11;
    tasks[0].nextStart=0;
    tasks[0].activation=0;
    tasks[0].remaining=3;
    tasks[0].abDeadline=tasks[0].activation+tasks[0].deadline;
    for(int j=0; j<K; j++){
        tasks[0].deadlineMiss[j] = 0;
    }
    tasks[0].count=0;
    tasks[0].flag=0;

    tasks[1].id=4;
    tasks[1].wcet=3;
    tasks[1].period=15;
    tasks[1].deadline=7;
    tasks[1].nextStart=145;
    tasks[1].activation=145;
    tasks[1].remaining=3;
    tasks[1].abDeadline=tasks[1].activation+tasks[1].deadline;
    for(int j=0; j<K; j++){
        tasks[1].deadlineMiss[j] = 0;
    }
    tasks[1].count=0;
    tasks[1].flag=0;

    tasks[2].id=1;
    tasks[2].wcet=3;
    tasks[2].period=19;
    tasks[2].deadline=14;
    tasks[2].nextStart=154;
    tasks[2].activation=154;
    tasks[2].remaining=3;
    tasks[2].abDeadline=tasks[2].activation+tasks[2].deadline;
    for(int j=0; j<K; j++){
        tasks[2].deadlineMiss[j] = 0;
    }
    tasks[2].count=0;
    tasks[2].flag=0;

    tasks[3].id=2;
    tasks[3].wcet=2;
    tasks[3].period=19;
    tasks[3].deadline=4;
    tasks[3].nextStart=166;
    tasks[3].activation=166;
    tasks[3].remaining=2;
    tasks[3].abDeadline=tasks[3].activation+tasks[3].deadline;
    for(int j=0; j<K; j++){
        tasks[3].deadlineMiss[j] = 0;
    }
    tasks[3].count=0;
    tasks[3].flag=0;

    tasks[4].id=5;
    tasks[4].wcet=1;
    tasks[4].period=20;
    tasks[4].deadline=1;
    tasks[4].nextStart=5;
    tasks[4].activation=5;
    tasks[4].remaining=1;
    tasks[4].abDeadline=tasks[4].activation+tasks[4].deadline;
    for(int j=0; j<K; j++){
        tasks[4].deadlineMiss[j] = 0;
    }
    tasks[4].count=0;
    tasks[4].flag=0;

}


void simulate(Task* tasks) {
    
    //job-continue策略
    int time = 0;
    int exTask = TASKS_NUM; //当前占用CPU的任务索引
    int execution;//execution=1 cpu执行任务； execution=0 cpu空闲
    
    while (time < SIMULATION_TIME) {

        execution = 0;
        for (int i = 0; i < TASKS_NUM; i++) {
            if (tasks[i].nextStart <= time && tasks[i].remaining > 0 && i <= exTask) {
                exTask = i;
                execution = 1;
            }
        }
        
        if (execution == 1) {
            printf("t%d\ttask%d\n", time, tasks[exTask].id);

            if (tasks[exTask].remaining > 0) {
                tasks[exTask].remaining--;
            
                if (tasks[exTask].remaining == 0) {
                    int deadlineMissCount = 0;//计数K次连续激活窗口中deadlinemiss数
                    if(time > tasks[exTask].abDeadline){
                        tasks[exTask].deadlineMiss[tasks[exTask].count%K]=1;
                        printf("task%d deadline miss\n", tasks[exTask].id);
                        //printf(":[%d,%d,%d]\n",tasks[exTask].deadlineMiss[0],tasks[exTask].deadlineMiss[1],tasks[exTask].deadlineMiss[2]);
                    }
                    tasks[exTask].count++;
                    for(int i=0; i<K; i++){
                        deadlineMissCount += tasks[exTask].deadlineMiss[i];
                    }
                    if(deadlineMissCount > M){
                        tasks[exTask].flag = 1;//不满足
                    }
                    tasks[exTask].nextStart += tasks[exTask].period;
                    printf("task%d nextStart: %d\n", tasks[exTask].id, tasks[exTask].nextStart);
                    tasks[exTask].abDeadline += tasks[exTask].period;
                    printf("task%d abDeadline: %d\n", tasks[exTask].id, tasks[exTask].abDeadline);
                    tasks[exTask].remaining = tasks[exTask].wcet;
                    exTask = TASKS_NUM;
                }
            }
        }else {
            //printf("t%d\t idle\n", time);
            exTask = TASKS_NUM;
        }
        time++;
    }
}


int main() {

    int count = 0;
    srand(time(NULL));
    Task* tasks = malloc(TASKS_NUM * sizeof(Task));

    initTasks(tasks);

    simulate(tasks);

    for(int i = 0; i < TASKS_NUM; i++){
        printf("task%d:flag=%d\n",tasks[i].id,tasks[i].flag);
        if(tasks[i].flag == 1){
            printf("task%d 不满足(%d,%d)限制\n", tasks[i].id, M, K);
            count++;
        }
    }
    printf("job-continue(%d,%d) count:%d cnf:%f\n", M, K, count, (float)(TASKS_NUM-count)/TASKS_NUM);
/**
    assert(tasks[0].flag==0);
    assert(tasks[1].flag==0);
    assert(tasks[2].flag==0);
    assert(tasks[3].flag==0);
    assert(tasks[4].flag==0);
*/
    free(tasks);

    return 0;
}
