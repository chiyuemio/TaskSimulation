import drs
import random
from collections import namedtuple

# Define the Task structure
Task = namedtuple('Task', ['id', 'wcet', 'period', 'deadline', 'schedulable', 'remaining', 'nextStart', 'activation', 'abDeadline', 'count', 'flag'])

def generate_tasks(num_tasks, utilization_sum, Tmin, Tmax):
    # Generate utilization vector using DRS
    utilizations = drs.drs(num_tasks, utilization_sum)
    
    tasks = []
    for i, utilization in enumerate(utilizations):
        id = i + 1
        #period = period_range[i % len(period_range)]  # Choose a period from the provided range
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

# Parameters
num_tasks = 5
utilization_sum = 0.80
Tmin = 5
Tmax = 20

# Generate tasks
tasks = generate_tasks(num_tasks, utilization_sum, Tmin, Tmax)

# Print the generated tasks
for i, task in enumerate(tasks):
    print(f"{task.id},{task.wcet},{task.period},{task.deadline}")

filename = "taskset.txt"

with open(filename, "w") as file:
    file.write("{\n")
    for task in tasks:
        file.write("{"+",".join(map(str, task))+"},\n")
    file.write("};\n")

