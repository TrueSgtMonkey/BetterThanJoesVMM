#ifndef ASS4_SCHEDULERS_H
#define ASS4_SCHEDULERS_H

#include "list.h"
#include <stdio.h>
#include "vector.h"

struct Stats
{
    int throughput;
    int turnAroundTime;
    int waitTime;
};

void setStats(struct Stats* stats, int throughput, int turnAroundTime, int waitTime);
void setStatstruct(struct Stats* stats, struct Stats stats1);
void fcfs(struct node** input, char* filename);
void hpf(struct node** input, char* filename);
void rr(struct node** input, int quantum, int overhead, char* filename);

#endif //ASS4_SCHEDULERS_H
