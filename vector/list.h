#ifndef LIST_HEADER
#define LIST_HEADER

struct node
{
    int data;
    struct node* next;
};

int isDuplicate(struct node* list, int data);
void del(struct node** list);
void delAll(struct node** list);
void add(struct node** list, int data);
void printlist(struct node* list);
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

void delAll(struct node** list)
{
    while(*list != NULL)
    {
        del(list);
    }
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

void printlist(struct node* list)
{
    struct node* temp = list;
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