#include "list.h"

int isDuplicate(struct node* list, struct Process data)
{
    while(list != NULL)
    {
        if(list->data.id == data.id)
            return 1;
        list = list->next;
    }
    return 0;
}

struct Process getHead(struct node* list)
{
    return list->data;
}

struct Process getElement(struct node* list, int spot)
{
    struct Process err;
    err.id = -1;
    err.priority = -1;
    err.time = -1;
    int i = 0;
    for(; i < spot && list != NULL; i++)
    {
        list = list->next;
    }
    return (list != NULL) ? list->data : err;
}

void del(struct node** list)
{
    struct node* temp = *list;
    temp = temp->next;
    free(*list);
    *list = temp;
}

struct Process delRet(struct node** list)
{
    struct Process data = (*list)->data;
    //printlist(*list);
    del(list);
    //printlist(*list);
    return data;
}

struct node* copyAll(struct node** list)
{
    struct node* temp = *list;
    struct node* newList = NULL;
    while(temp != NULL)
    {
        addAny(&newList, temp->data);
        temp = temp->next;
    }
    return newList;
}

void delAll(struct node** list)
{
    while(*list != NULL)
    {
        del(list);
    }
}

struct node* sortListByTime(struct node** list)
{
    struct node* newList = NULL;
    while(*list != NULL)
    {
        addSortByTime(&newList, delRet(list));
    }
    return newList;
}

struct node* sortListByPriority(struct node** list)
{
    struct node* newList = NULL;
    while(*list != NULL)
    {
        addSortByPriority(&newList, delRet(list));
    }
    return newList;
}

struct node* sortListByPriorityWithDupes(struct node** list)
{
    struct node* newList = NULL;
    while(*list != NULL)
    {
        addAnySortByPriority(&newList, delRet(list));
    }
    return newList;
}

struct node* sortListByTimeWithDupes(struct node** list)
{
    struct node* newList = NULL;
    while(*list != NULL)
    {
        addAnySortByTime(&newList, delRet(list));
    }
    return newList;
}


void add(struct node** list, struct Process data)
{
    if(*list == NULL)
    {
        *list = malloc(sizeof(struct node));
        (*list)->next = NULL;
        (*list)->data = data;
        return;
    }

    if(isDuplicate(*list, data) == 0) //no dupes
    {
        struct node* temp = *list;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        struct node* temp2 = temp;
        temp = temp->next;
        temp = malloc(sizeof(struct node));
        temp->next = NULL;
        temp->data = data;
        temp2->next = temp;
    }
}

void addAny(struct node** list, struct Process data)
{
    if(*list == NULL)
    {
        *list = malloc(sizeof(struct node));
        (*list)->next = NULL;
        (*list)->data = data;
        return;
    }

    struct node* temp = *list;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    struct node* temp2 = temp;
    temp = temp->next;
    temp = malloc(sizeof(struct node));
    temp->next = NULL;
    temp->data = data;
    temp2->next = temp;
}

void addSortByTime(struct node** list, struct Process data)
{
    if(*list == NULL)
    {
        *list = malloc(sizeof(struct node));
        (*list)->next = NULL;
        (*list)->data = data;
        return;
    }
    if(isDuplicate(*list, data) == 0) //no dupes allowed
    {
        struct node* temp = *list;
        if(temp->next == NULL) //1 element in list
        {
            struct node* nnode = malloc(sizeof(struct node));
            nnode->data = data;
            if(temp->data.time < data.time)
            {
                temp->next = nnode;
            }
            else
            {
                nnode->next = temp;
                *list = nnode; //setting new head
            }
        }
        else
        {
            if(temp->data.time > data.time)
            {
                struct node* nnode = malloc(sizeof(struct node));
                nnode->data = data;
                nnode->next = *list;
                *list = nnode;
                return;
            }
            while(temp->next != NULL)
            {
                if(temp->next->data.time > data.time)
                    break;
                temp = temp->next;
            }
            if(temp->next == NULL)  //made it to the last element, add normally
            {
                struct node* nnode = malloc(sizeof(struct node));
                nnode->data = data;
                nnode->next = NULL;
                temp->next = nnode;
            }
            else
            {
                struct node* nnode = malloc(sizeof(struct node));
                struct node* greater = temp;
                greater = greater->next;
                nnode->data = data;
                temp->next = nnode;
                nnode->next = greater;
            }
        }
    }
}

void addSortByPriority(struct node** list, struct Process data)
{
    if(*list == NULL)
    {
        *list = malloc(sizeof(struct node));
        (*list)->next = NULL;
        (*list)->data = data;
        return;
    }
    if(isDuplicate(*list, data) == 0) //no dupes allowed
    {
        struct node* temp = *list;
        if(temp->next == NULL) //1 element in list
        {
            struct node* nnode = malloc(sizeof(struct node));
            nnode->data = data;
            if(temp->data.priority < data.priority)
            {
                temp->next = nnode;
            }
            else
            {
                nnode->next = temp;
                *list = nnode; //setting new head
            }
        }
        else
        {
            if(temp->data.priority > data.priority)
            {
                struct node* nnode = malloc(sizeof(struct node));
                nnode->data = data;
                nnode->next = *list;
                *list = nnode;
                return;
            }
            while(temp->next != NULL)
            {
                if(temp->next->data.priority > data.priority)
                    break;
                temp = temp->next;
            }
            if(temp->next == NULL)  //made it to the last element, add normally
            {
                struct node* nnode = malloc(sizeof(struct node));
                nnode->data = data;
                nnode->next = NULL;
                temp->next = nnode;
            }
            else
            {
                struct node* nnode = malloc(sizeof(struct node));
                struct node* greater = temp;
                greater = greater->next;
                nnode->data = data;
                temp->next = nnode;
                nnode->next = greater;
            }
        }
    }
}

void addAnySortByTime(struct node** list, struct Process data)
{
    if(*list == NULL)
    {
        *list = malloc(sizeof(struct node));
        (*list)->next = NULL;
        (*list)->data = data;
        return;
    }

    struct node* temp = *list;
    if(temp->next == NULL) //1 element in list
    {
        struct node* nnode = malloc(sizeof(struct node));
        nnode->data = data;
        if(temp->data.time < data.time)
        {
            temp->next = nnode;
        }
        else
        {
            nnode->next = temp;
            *list = nnode; //setting new head
        }
    }
    else
    {
        if(temp->data.time > data.time)
        {
            struct node* nnode = malloc(sizeof(struct node));
            nnode->data = data;
            nnode->next = *list;
            *list = nnode;
            return;
        }
        while(temp->next != NULL)
        {
            if(temp->next->data.time > data.time)
                break;
            temp = temp->next;
        }
        if(temp->next == NULL)  //made it to the last element, add normally
        {
            struct node* nnode = malloc(sizeof(struct node));
            nnode->data = data;
            nnode->next = NULL;
            temp->next = nnode;
        }
        else
        {
            struct node* nnode = malloc(sizeof(struct node));
            struct node* greater = temp;
            greater = greater->next;
            nnode->data = data;
            temp->next = nnode;
            nnode->next = greater;
        }
    }
}

void addAnySortByPriority(struct node** list, struct Process data)
{
    if(*list == NULL)
    {
        *list = malloc(sizeof(struct node));
        (*list)->next = NULL;
        (*list)->data = data;
        return;
    }

    struct node* temp = *list;
    if(temp->next == NULL) //1 element in list
    {
        struct node* nnode = malloc(sizeof(struct node));
        nnode->data = data;
        if(temp->data.priority < data.priority)
        {
            temp->next = nnode;
        }
        else
        {
            nnode->next = temp;
            *list = nnode; //setting new head
        }
    }
    else
    {
        if(temp->data.priority > data.priority)
        {
            struct node* nnode = malloc(sizeof(struct node));
            nnode->data = data;
            nnode->next = *list;
            *list = nnode;
            return;
        }
        while(temp->next != NULL)
        {
            if(temp->next->data.priority > data.priority)
                break;
            temp = temp->next;
        }
        if(temp->next == NULL)  //made it to the last element, add normally
        {
            struct node* nnode = malloc(sizeof(struct node));
            nnode->data = data;
            nnode->next = NULL;
            temp->next = nnode;
        }
        else
        {
            struct node* nnode = malloc(sizeof(struct node));
            struct node* greater = temp;
            greater = greater->next;
            nnode->data = data;
            temp->next = nnode;
            nnode->next = greater;
        }
    }
}

void printlist(struct node** list)
{
    struct node* temp = *list;
    printf("(");
    while(temp != NULL)
    {
        printf("<%d, %d, %d>", temp->data.id, temp->data.time, temp->data.priority);
        if(temp->next != NULL)
        {
            printf(", ");
        }
        temp = temp->next;
    }
    printf(")\n");
}

void printlistToFile(struct node** list, FILE* file)
{
    struct node* temp = *list;
    while(temp != NULL)
    {
        fprintf(file, "%d %d %d\n", temp->data.id, temp->data.time, temp->data.priority);
        temp = temp->next;
    }
}
