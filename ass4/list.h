#ifndef LIST_HEADER
#define LIST_HEADER

#include <stdlib.h>
#include <stdio.h>

struct Process
{
    int id;
    int time;
    int priority;
    int turnAroundTime;
    int timeSlices;
    int overhead;
};

struct node
{
    struct Process data;
    struct node* next;
};

int isDuplicate(struct node* list, struct Process data);
void del(struct node** list);
struct Process delRet(struct node** list);
struct node* copyAll(struct node** list);
void delAll(struct node** list);
struct node* sortListByTime(struct node** list);
struct node* sortListByPriority(struct node** list);
struct node* sortListByTimeWithDupes(struct node** list);
struct node* sortListByPriorityWithDupes(struct node** list);
void add(struct node** list, struct Process data);
void addSortByTime(struct node** list, struct Process data);
void addSortByPriority(struct node** list, struct Process data);
void addAny(struct node** list, struct Process data);
void addAnySortByTime(struct node** list, struct Process data);
void addAnySortByPriority(struct node** list, struct Process data);
void printlist(struct node** list);
void printlistToFile(struct node** list, FILE* file);
struct Process getHead(struct node* list);
struct Process getElement(struct node* list, int spot);

#endif //LIST_HEADER