#ifndef UTILS_H
#define UTILS_H

#include "task.h"

#define SIMULATION_TIME 100

int compare_by_period(const void* a, const void* b);
int compare_by_deadline(const void* a, const void* b);
int nondet_int_range(int min, int max);

#endif