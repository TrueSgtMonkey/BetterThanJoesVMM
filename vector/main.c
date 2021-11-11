#include <stdio.h>
#include "vector.h"
#include "list.h"
#include <stdlib.h>
#include <time.h>

void buildVecFromString();
void buildVecFromScratch();
void buildVecIntFromScratch();
void linkedlistops();
void checkListDupes(int check);
void checkSortAdd();
void addCheck(struct node** list, int data);
void unsortedToSorted();
int randy();

int main()
{
    srand(time(0));
    buildVecFromString();
    buildVecFromScratch();
    buildVecIntFromScratch();

    linkedlistops();
    checkListDupes(1);

    //check what happens if we do not check for duplicates
    checkListDupes(0);
    checkSortAdd();
    //for(int i = 0; i < 100; i++)
    {
        unsortedToSorted();
    }


    return 0;
}

void unsortedToSorted()
{
    struct node* list = NULL;
    struct node* list2 = NULL;

    for(int i = 100; i >= 0; i--)
    {
        int n = (randy() % ((i > 0) ? i : 2));
        addAny(&list, n);
        addAny(&list2, n);
    }
    printf("unsorted list: ");
    printlist(&list);

    struct node* list3 = sortListWithDupes(&list);
    printf("%d\n", list);
    struct node* list4 = sortList(&list2);
    printlist(&list3);
    printlist(&list4);
    delAll(&list);
    delAll(&list2);
    delAll(&list3);
    delAll(&list4);
}

int randy()
{
    int n = (rand() << 17) | (rand() << 2) | (rand() >> 13);
    return ((n < 0) ? (-n) : n);
}

void checkSortAdd()
{
    struct node* list = NULL;
    addCheck(&list, 4);
    addCheck(&list, 2);
    addCheck(&list, 8);
    addCheck(&list, 6);
    addCheck(&list, 10);
    addCheck(&list, 5);
    addCheck(&list, 1);
    addCheck(&list, 7);
    addCheck(&list, 22);
    addCheck(&list, 8);
    delAll(&list);
}

void addCheck(struct node** list, int data)
{
    addSort(list, data);
    printlist(list);
}

//if check is anything but 0, we'll check for duplicates
void checkListDupes(int check)
{
    struct node* list = NULL;
    printf("adding 1: ");
    (check != 0) ? add(&list, 1) : addAny(&list, 1);
    printlist(&list);
    printf("adding 1: ");
    (check != 0) ? add(&list, 1) : addAny(&list, 1);
    printlist(&list);
    for(int i = 0; i < 10; i++)
    {
        int x = i/2;
        printf("adding %d: ", x);
        (check != 0) ? add(&list, x) : addAny(&list, x);
        printlist(&list);
    }
    delAll(&list);
}

void linkedlistops()
{
    struct node* list = NULL;
    for(int i = 0; i < 25; i++)
    {
        add(&list, i * 10);
    }
    printlist(&list);
    del(&list);
    printlist(&list);
    printf("%d\n", getHead(list));
    printf("%d\n", getElement(list, 5));
    delAll(&list);
    printlist(&list);
}

void buildVecFromString()
{
    struct vectorchar vec;

    newvecstring(&vec, "holy fuck");

    printf("%d\n", vec.size);
    pushstring(&vec, " poop");
    printf("%d\n", vec.size);
    printf("%s\n", vec.arr);

    erasechar(&vec);
}

void buildVecFromScratch()
{
    struct vectorchar vec;

    newvecchar(&vec);

    pushchar(&vec, 'h');
    printf("%s\n", vec.arr);
    pushchar(&vec, 'i');
    printf("%s\n", vec.arr);

    pushstring(&vec, " cutie! Love you sweetie!");

    printf("%s\n", vec.arr);
    char c = popchar(&vec);
    printf("%c", c);
    int sz = vec.size;
    for(int i = 0; i < sz-1; i++)
    {
        printf("%c", popchar(&vec));
    }
    printf("\n");
    free(vec.arr);
}

void buildVecIntFromScratch()
{
    struct vectorint vec;

    newvecint(&vec);
    vec.arr[0] = 69;
    printarr(vec);
    for(int i = 0; i < 10; i++)
    {
        pushint(&vec, i * 25);
    }

    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    struct vectorint vec2;
    newvecintarr(&vec2, arr, 10);
    pushintvec(&vec, &vec2);

    printf("vec1: ");
    printarr(vec);
    printf("vec2: ");
    printarr(vec2);

    eraseint(&vec);
    eraseint(&vec2);
}
