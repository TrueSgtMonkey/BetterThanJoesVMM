#include <stdio.h>
#include "vector.h"
#include "list.h"

void buildVecFromString();
void buildVecFromScratch();
void buildVecIntFromScratch();
void linkedlistops();

int main()
{
    buildVecFromString();
    buildVecFromScratch();
    buildVecIntFromScratch();

    linkedlistops();

    return 0;
}

void linkedlistops()
{
    struct node* list = NULL;
    for(int i = 0; i < 25; i++)
    {
        add(&list, i * 10);
    }
    printlist(list);
    del(&list);
    printlist(list);
    printf("%d\n", getHead(list));
    printf("%d\n", getElement(list, 5));
    delAll(&list);
    printlist(list);
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
