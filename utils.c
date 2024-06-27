#include "utils.h"
#include <stdlib.h>

int compare_by_period(const void* a, const void* b) {
    return ((Task*)a)->period - ((Task*)b)->period;
}

int compare_by_deadline(const void* a, const void* b) {
    return ((Task*)a)->abDeadline - ((Task*)b)->abDeadline;
}

int nondet_int_range(int min, int max) {
    return rand() % (max - min + 1) + min;
}
