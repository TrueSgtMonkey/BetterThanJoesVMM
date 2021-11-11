#ifndef LIST_HEADER
#define LIST_HEADER

struct node
{
    int data;
    struct node* next;
};

int isDuplicate(struct node* list, int data);
void del(struct node** list);
int delRet(struct node** list);
void delAll(struct node** list);
struct node* sortList(struct node** list);
struct node* sortListWithDupes(struct node** list);
void add(struct node** list, int data);
void addSort(struct node** list, int data);
void addAny(struct node** list, int data);
void addAnySort(struct node** list, int data);
void printlist(struct node** list);
int getHead(struct node* list);
int getElement(struct node* list, int spot);

int isDuplicate(struct node* list, int data)
{
    while(list != NULL)
    {
        if(list->data == data)
            return 1;
        list = list->next;
    }
    return 0;
}

int getHead(struct node* list)
{
    return list->data;
}

int getElement(struct node* list, int spot)
{
    int i = 0;
    for(; i < spot && list != NULL; i++)
    {
        list = list->next;
    }
    return (list != NULL) ? list->data : 0;
}

void del(struct node** list)
{
    struct node* temp = *list;
    temp = temp->next;
    free(*list);
    *list = temp;
}

int delRet(struct node** list)
{
    int data = (*list)->data;
    //printlist(*list);
    del(list);
    //printlist(*list);
    return data;
}

void delAll(struct node** list)
{
    while(*list != NULL)
    {
        del(list);
    }
}

struct node* sortList(struct node** list)
{
    struct node* newList = NULL;
    while(*list != NULL)
    {
        addSort(&newList, delRet(list));
    }
    return newList;
}

struct node* sortListWithDupes(struct node** list)
{
    struct node* newList = NULL;
    while(*list != NULL)
    {
        addAnySort(&newList, delRet(list));
    }
    return newList;
}

void add(struct node** list, int data)
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

void addAny(struct node** list, int data)
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

void addSort(struct node** list, int data)
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
            if(temp->data < data)
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
            if(temp->data > data)
            {
                struct node* nnode = malloc(sizeof(struct node));
                nnode->data = data;
                nnode->next = *list;
                *list = nnode;
                return;
            }
            while(temp->next != NULL)
            {
                if(temp->next->data > data)
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

void addAnySort(struct node** list, int data)
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
        if(temp->data < data)
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
        if(temp->data > data)
        {
            struct node* nnode = malloc(sizeof(struct node));
            nnode->data = data;
            nnode->next = *list;
            *list = nnode;
            return;
        }
        while(temp->next != NULL)
        {
            if(temp->next->data > data)
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
        printf("%d", temp->data);
        if(temp->next != NULL)
        {
            printf(", ");
        }
        temp = temp->next;
    }
    printf(")\n");
}

#endif //LIST_HEADER