import drs
import random
from collections import namedtuple
from pre import pre

NUM_TASKS = 5
UTILIZATION_SUM = 0.8
TMIN = 5
TMAX = 20

M = 1
K = 3
NUMBER = 4

# Define the Task structure
Task = namedtuple('Task', ['id', 'wcet', 'period', 'deadline', 'schedulable', 'remaining', 'nextStart', 'activation', 'abDeadline', 'count', 'flag'])

def generate_tasks(num_tasks, utilization_sum, Tmin, Tmax):
    # Generate utilization vector using DRS
    utilizations = drs.drs(num_tasks, utilization_sum)
    
    tasks = []
    for i, utilization in enumerate(utilizations):
        id = i + 1
        period = random.randint(Tmin, Tmax) 
        wcet = max(1, int(utilization * period))  # Calculate WCET as utilization * period
        deadline = random.randint(wcet, period)  # For simplicity, set deadline equal to period
        task = Task(id=id, wcet=wcet, period=period, deadline=deadline, 
                    schedulable=False, remaining=wcet, activation=0, nextStart=0,
                    abDeadline=0, count=0, flag=True)
        tasks.append(task)
    
    tasks.sort(key=lambda x : x.period)
    for i, task in enumerate(tasks):
        tasks[i] = task._replace(id=i + 1)

    return tasks

def write_taskset(tasks, filename="taskset.txt"):
    with open(filename, "w") as file:
        file.write("{\n")
        for task in tasks:
            file.write("{"+",".join(map(str, task))+"},\n")
        file.write("};\n")

def main():

    num_tasks = NUM_TASKS
    utilization_sum =UTILIZATION_SUM
    Tmin = TMIN
    Tmax = TMAX
    tasks = generate_tasks(num_tasks, utilization_sum, Tmin, Tmax)
    for i, task in enumerate(tasks):
        print(f"{task.id},{task.wcet},{task.period},{task.deadline}")
    write_taskset(tasks)

    pre.main()

if __name__ == "__main__":

    main()