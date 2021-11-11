#include "schedulers.h"

void fcfs(struct node** input, char* filename)
{
    FILE* file = fopen(filename, "a");
    struct Stats stats;
    int processes = 0;
    setStats(&stats, 0, 0, 0);
    struct node* temp = *input;
    printf("fcfs: ");
    printlist(&temp);

    fprintf(file, "Process list in FCFS order as entered:\n");
    printlistToFile(input, file);
    fprintf(file, "End of List\n\n");
    struct vectorint vec;
    newvecint(&vec);

    while(temp != NULL)
    {
        fprintf(file, "fcfs wait of p%d = %d\n", temp->data.id, stats.waitTime);
        pushint(&vec, stats.waitTime);
        stats.waitTime += temp->data.time;
        stats.turnAroundTime += temp->data.time;
        temp->data.turnAroundTime = stats.turnAroundTime;
        temp = temp->next;
        processes++;
    }
    int totWait = 0;
    for(int i = 0; i < vec.size; i++)
    {
        totWait += vec.arr[i];
    }

    double avg = (double)totWait / (double)processes;
    fprintf(file, "average wait for %d procs = %lf\n", processes, avg);

    temp = *input;
    int sum = 0;
    while(temp != NULL)
    {
        fprintf(file, "fcfs turn-around time for p%d = %d\n", temp->data.id, temp->data.turnAroundTime);
        sum += temp->data.turnAroundTime;
        temp = temp->next;
    }

    avg = (double)sum / (double)processes;
    fprintf(file, "average turn-around for %d procs = %lf\n", processes, avg);

    double throughput = (double)processes / (double)stats.turnAroundTime;
    fprintf(file, "fcfs throughput for %d procs = %lf proc/ms\n", processes, throughput);

    fprintf(file, " <><> end FCFS <><>\n\n");

    eraseint(&vec);
    fclose(file);
}

void hpf(struct node** input, char* filename)
{
    int processes = 0;
    FILE* file = fopen(filename, "a");
    struct Stats stats;
    setStats(&stats, 0, 0, 0);
    struct node* list = copyAll(input);
    //sorting by priority and making new list to not overwrite the old list that was passed in
    list = sortListByPriority(&list);
    printf("hpf: ");
    printlist(&list);
    struct node* temp = list;

    fprintf(file, "Process list in HPF order:\n");
    printlistToFile(&temp, file);
    fprintf(file, "End of list.\n\n");

    struct vectorint vec;
    newvecint(&vec);
    while(temp != NULL)
    {
        fprintf(file, "hpf wait of p%d = %d\n", temp->data.id, stats.waitTime);
        pushint(&vec, stats.waitTime);
        stats.waitTime += temp->data.time;
        stats.turnAroundTime += temp->data.time;
        temp->data.turnAroundTime = stats.turnAroundTime;
        temp = temp->next;
        processes++;
    }

    int totWait = 0;
    for(int i = 0; i < vec.size; i++)
    {
        totWait += vec.arr[i];
    }

    double avg = (double)totWait / (double)processes;
    fprintf(file, "average wait for %d procs = %lf\n", processes, avg);

    temp = list;
    int sum = 0;
    while(temp != NULL)
    {
        fprintf(file, "hpf turn-around time for p%d = %d\n", temp->data.id, temp->data.turnAroundTime);
        sum += temp->data.turnAroundTime;
        temp = temp->next;
    }

    avg = (double)sum / (double)processes;
    fprintf(file, "average turn-around for %d procs = %lf\n", processes, avg);
    /*
            "hpf throughput for 2 procs = 0.666667 proc/ms\n"
            " <><> end HPF schedule <><>"
    */
    double throughput = (double)processes / (double)stats.turnAroundTime;
    fprintf(file, "hpf throughput for %d procs = %lf proc/ms\n", processes, throughput);

    fprintf(file, " <><> end HPF schedule <><>\n\n");

    eraseint(&vec);
    delAll(&list);
    fclose(file);
}

/*
 * For the preemptive RR scheduler, vary the time quantum q from 1 to 5 milliseconds (ms).
 *
 * Also, for each q selected, vary the overhead o of a context switch from 0 ms up to q itself.
 *
 * There is no need to vary the o beyond q.
 *
 * When a process scheduled by the RR system has received all time needed to completion, do not add a final o unit
 * in the computation of the total time for that process.
 *
 * Also the first time around, act as if the initial schedule overhead o is 0.
 * */
void rr(struct node** input, int quantum, int overhead, char* filename)
{
    struct Stats stats;
    struct node* list = NULL;
    setStats(&stats, 0, 0, 0);
    struct node* inputList = copyAll(input);
    struct node* temp = inputList;
    FILE* file = fopen(filename, "a");

    int totalTime = 0;
    int sz = 0;
    int idFirst;
    while(temp != NULL)
    {
        temp->data.overhead = 0;
        totalTime += temp->data.time;

        temp->data.timeSlices = ((temp->data.time - 1) / quantum) + 1;
        temp = temp->next;
        sz++;
    }
    int firstInput = 1;
    int totalWaitTime = 0;
    while(totalTime > 0)
    {
        temp = inputList;
        while(temp != NULL)
        {
            //checking if process is done
            if(temp->data.time > 0)
            {
                if(quantum <= temp->data.time)
                    totalWaitTime += quantum;
                else
                    totalWaitTime += temp->data.time;

                temp->data.time -= quantum;
                totalTime -= quantum;

                if(temp->data.time <= 0)
                {
                    //getting original time and then giving it to the new list
                    int time = temp->data.time + (quantum * temp->data.timeSlices);
                    totalTime -= temp->data.time;
                    temp->data.time = time;
                    temp->data.overhead = totalWaitTime;
                    addAny(&list, temp->data);

                    temp->data.time = 0;
                }
                if(firstInput == 0)
                {
                    totalWaitTime += overhead;
                }
                firstInput = 0;
            }
            temp = temp->next;
        }
    }

    temp = list;
    while(temp != NULL)
    {
        if(temp->data.id != idFirst)
            temp->data.overhead += overhead * temp->data.timeSlices;
        temp = temp->next;
    }

    printf("rr checking build list");
    printlist(&list);
    temp = list;
    printf("q=%d,o=%d\n", quantum, overhead);


    fprintf(file, "preemptive RR schedule, quantum = %d overhead = %d\n",
            quantum, overhead);
    /*
            "RR Throughput, 2 p, with q: 1, o: 0, is: 0.666667 p/ms, or 666.667 p/us\n"
            "Average RR TA, 2 p, with q: 1, o: 0, is: 2.5");
    */
    while(temp != NULL)
    {
        temp->data.overhead -= overhead * (temp->data.timeSlices - 1);
        fprintf(file, "RR TA time for finished p%d = %d, needed: %d ms, and: "
                      "%d time slices.\n", temp->data.id, temp->data.overhead,
                      temp->data.time, temp->data.timeSlices);
        temp = temp->next;
    }
    temp = list;
    int totalTA = 0;
    while(temp != NULL)
    {
        totalTA += temp->data.overhead;
        temp = temp->next;
    }

    double throughput = (double)sz / (double)(totalWaitTime);
    fprintf(file, "RR Throughput, %d p, with q: %d, o: %d, is: %g p/ms, or "
                  "%g p/us\n", sz, quantum, overhead, throughput,
                  throughput * 1000.0);

    double avgTA = (double)totalTA / (double)sz;
    fprintf(file, "Average RR TA, %d p, with q: %d, o: %d, is: %g\n\n", sz,
                   quantum, overhead, avgTA);

    delAll(&inputList);
    delAll(&list);
    fclose(file);
}

void setStats(struct Stats* stats, int throughput, int turnAroundTime, int waitTime)
{
    stats->throughput = throughput;
    stats->turnAroundTime = turnAroundTime;
    stats->waitTime = waitTime;
}

void setStatstruct(struct Stats* stats, struct Stats stats1)
{
    stats->throughput = stats1.throughput;
    stats->turnAroundTime = stats1.turnAroundTime;
    stats->waitTime = stats1.waitTime;
}