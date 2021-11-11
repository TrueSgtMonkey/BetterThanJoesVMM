#include <stdio.h>
#include "list.h"
#include "schedulers.h"

int setVal(FILE* file, int* val);

int main(int argc, char* argv[])
{
    FILE* file;
    FILE* outFile;
    int x = 1;
    struct node* input = NULL;

    switch(argc)
    {
        case 0:case 1:
        {
            printf("must give name of input file!\n");
            return 1;
        }
        default:
        {
            file = fopen(argv[1], "r");
        }
    }

    while(x > 0)
    {
        struct Process proc;

        x = setVal(file, &proc.id);
        if(x > 0)
            x = setVal(file, &proc.time);
        else
            break;
        if(x > 0)
            x = setVal(file, &proc.priority);
        else
            break;

        proc.turnAroundTime = 0;
        add(&input, proc);
        printf("p%d added: ", proc.id);
        printlist(&input);
    }

    char* filename = getFileNameFromVecchar(argv[1], "_out.txt");
    outFile = fopen(filename, "w");
    fprintf(outFile, "Enter triples: process id, time in ms, and priority:\n"
                     "For example:\n"
                     "1 12 0\n"
                     "3  9 1\n"
                     "2 99 9\n"
                     "process 1 needs 12 ms and has priority 0, very high,\n"
                     "process 3 needs  9 ms and has priority 1.\n"
                     "and so on ...\n");
    printlistToFile(&input, outFile);
    fprintf(outFile, "\n");

    fclose(outFile);

    fcfs(&input, filename);
    hpf(&input, filename);

    struct node* temp = input;
    int max = 0;
    while(temp != NULL)
    {
        if(max < temp->data.time)
            max = temp->data.time;
        temp = temp->next;
    }
    if(max > 5)
        max = 5;
    for(int i = 1; i < max+1; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            rr(&input, i, j, filename);
        }
    }

    outFile = fopen(filename, "a");

    fprintf(outFile, " <><> end preemptive RR schedule <><>\n\n");

    fclose(outFile);

    printf("main: ");
    printlist(&input);

    delAll(&input);
    free(filename);
    fclose(file);
    return 0;
}

int setVal(FILE* file, int* val)
{
    struct vectorchar vec;
    newvecchar(&vec);
    int ret = inputIntoVec(file, &vec);
    *val = getNumFromVectorchar(&vec);
    erasechar(&vec);
    return ret;
}


