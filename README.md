# **A task scheduling simulator**

We implement a simple scheduler based on weakly hard scheduling method to simulate the scheduling process of multiple tasks on a single processor. The weakly hard scheduling model serves as a method for characterizing systems that can withstand certain deadline misses, which introduces (m,k) constraint to describe a task.

**(m,k) constraint**: no more than 𝑚 deadline misses must occur for any k consecutive activations of the task.

And we implemented the scheduler using the job-continue policy, which means the job will continue executing until its completion even if its deadline is missed.

## Project Overview

The project consists of several components that work together to generate, preprocess, and validate task sets. The main parts of the project include task generation, preprocessing, initialization, and verification.

```
TaskSimulation/
|--task
|   |--generator.py
|   |--taskset_5_0.95
|   |--taskset_5_0.90
|   |--taskset_5_0.85
|   |--taskset_5-0.80
|--pre
|   |--pre.py
|   |--preProcess.c
|   |--preProcess
|--init
|   |--init.py
|--init.c
|--simulate.c
|--main.c
|--simulate.h
|--task.h
|--start.py
|--README.md
```

### task

**generator.py**

+ This script generates an initial task set using the DRS  algorithm. The generated task information is saved into taskset.txt.

+ Input Parameters:

    + `num_tasks`: number of tasks to generate.
    + `utilization_sum`: the total CPU utilization of all tasks.
    + `Tmin`: minimum task period.
    + `Tmax`: maximum task period.

**taskset**

+ These files contain predefined task sets with different utilization sums and task configurations.

### pre/pre.py

+ This script preprocesses the initial tasks from taskset.txt to preliminarily check if the tasks are schedulable. It updates the schedulable field of each task based on the analysis results.

### init/init.py

+ A script that reads task information from `taskset.txt` and writes it into the initialization section of task.h. It also allows setting various parameters such as `SIMULATION_TIME`, `TASKS_NUM`, `M`, `K`, and `NUMBER` for configuring the verification process.

### simulate.c, main.c, simulate.h, task.h

+ These files define the simulation and verification logic, including task scheduling and constraint checking.

### start.py

+ This script initiates the verification process to check whether the tasks satisfy the given constraints

## How to use it

### Generate initial task sets

+ Modify `num_task`, `sutilization_sum`, `Tmin`, `Tmax` in `generator.py` with the desired parameters and run it to create `taskset.txt`.

```bash
python task/generator.py #modify it according to the actual path.
```

### Preprocess

+ Run `pre.py` to determine whether the tasks in `taskset.txt` are scheduleble and update the `schedulable` field of the tasks.

```bash
python pre/pre.py
```

### Initialize tasks

+ Modify `SIMULATION_TIME`, `TASKS_NUM`, `M`, `K`, `NUMBER` in `init.py` with the desired parameters, and run it to read task information from `taskset.txt` and write it into `task.h`.

```bash
python init/init.py
```

### Start running

+ Run `start.py` to start verification process.

```bash
python start.py
```
