#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <stdlib.h>

struct vectorchar
{
    char* arr;
    int total_size; //used for resizing array to speed things up
    int size; //used for finding the current length of the cstring
};

struct vectorint
{
    int* arr;
    int total_size; //max size
    int size;   //curr size
};

//VECTORCHAR
//make a blank char vec
void newvecchar(struct vectorchar* vec);
//make a new vectorchar with a string of chars
void newvecstring(struct vectorchar* vec, char* s);
//push an entire string onto the vectorchar
void pushcharvec(struct vectorchar* vec1, struct vectorchar* vec2);
void pushstring(struct vectorchar* vec, char* s);
//push a char onto the vectorchar
void pushchar(struct vectorchar* vec, char c);
/* resize the vectorchar to whatever you want
 * Must be initialized first */
void resizechararr(struct vectorchar* vec, int newsize);
char popchar(struct vectorchar* vec);
void erasechar(struct vectorchar* vec);
void printstring(struct vectorchar vec);

//VECTORINT
void newvecint(struct vectorint* vec);
//make a new vectorchar with a string of chars
void newvecintarr(struct vectorint* vec, int* s, int sz);
//push an entire string onto the vectorchar
void pushintvec(struct vectorint* vec1, struct vectorint* vec2);
void pushintarr(struct vectorint* vec, int* s, int sz);
//push a char onto the vectorchar
void pushint(struct vectorint* vec, int c);
/* resize the vectorchar to whatever you want
 * Must be initialized first */
void resizeintarr(struct vectorint* vec, int newsize);
int popint(struct vectorint* vec);
void eraseint(struct vectorint* vec);
void printarr(struct vectorint vec);

//------------VECTOR-CHAR------------------------------------
void newvecstring(struct vectorchar* vec, char* s)
{
    int i = 0;
    
    //getting total_size of the string
    while(s[i] != '\0')
    {
        i++;
    }
    i++;
    
    //making vectorchar with twice as many elements with that string
    vec->total_size = i * 2;
    vec->arr = malloc(sizeof(char) * vec->total_size);
    for(int j = 0; j < i; j++)
    {
        vec->arr[j] = s[j];
    }
    
    //set size to '\0'
    vec->size = i;
}

void newvecchar(struct vectorchar* vec)
{
    vec->arr = malloc(sizeof(char));
    vec->total_size = 2;
    vec->size = 1;
    vec->arr[vec->size] = '\0';
}

void erasechar(struct vectorchar* vec)
{
  free(vec->arr);
  vec->size = 0;
  vec->total_size = 0;
}

void pushcharvec(struct vectorchar* vec1, struct vectorchar* vec2)
{
    for(int i = 0; i < vec2->size; i++)
    {
        pushchar(vec1, vec2->arr[i]);
    }
}

void pushstring(struct vectorchar* vec, char* s)
{
    int i = 0;
    while(s[i] != '\0')
    {
        pushchar(vec, s[i]);
        i++;
    }
}

void pushchar(struct vectorchar* vec, char c)
{
    vec->size += 1;
    if(vec->size >= vec->total_size)
    {
        resizechararr(vec, vec->total_size * 2);
    }
    vec->arr[vec->size-2] = c;
    vec->arr[vec->size-1] = '\0';
}

void resizechararr(struct vectorchar* vec, int newsize)
{
    vec->total_size = newsize;
    char* c = malloc(sizeof(char) * newsize);

    for(int i = 0; i < vec->size; i++)
    {
        c[i] = vec->arr[i];
    }

    free(vec->arr);
    vec->arr = c;
}

char popchar(struct vectorchar* vec)
{
    if(vec->size > 1)
    {
        char c = vec->arr[vec->size-2];
        vec->size--;
        vec->arr[vec->size-1] = '\0';
        return c;
    }
    return '\0';
}

void printstring(struct vectorchar vec)
{
    printf("%s\n", vec.arr);
}

//-------------VECTOR-INT--------------------------------
void newvecintarr(struct vectorint* vec, int* s, int sz)
{
    vec->total_size = sz * 2;
    vec->arr = malloc(sizeof(int) * vec->total_size);
    for(int j = 0; j < sz; j++)
    {
        vec->arr[j] = s[j];
    }

    vec->size = sz;
}

void newvecint(struct vectorint* vec)
{
    vec->arr = malloc(sizeof(int));
    vec->total_size = 2;
    vec->size = 1;
    vec->arr[vec->size] = 0;
}

void eraseint(struct vectorint* vec)
{
    free(vec->arr);
    vec->size = 0;
    vec->total_size = 0;
}

void pushintvec(struct vectorint* vec1, struct vectorint* vec2)
{
    for(int i = 0; i < vec2->size; i++)
    {
        pushint(vec1, vec2->arr[i]);
    }
}

void pushintarr(struct vectorint* vec, int* s, int sz)
{
    for(int i = 0; i < sz; i++)
    {
        pushint(vec, s[i]);
    }
}

void pushint(struct vectorint* vec, int c)
{
    vec->size += 1;
    if(vec->size >= vec->total_size)
    {
        resizeintarr(vec, vec->total_size * 2);
    }
    vec->arr[vec->size-1] = c;
}

void resizeintarr(struct vectorint* vec, int newsize)
{
    vec->total_size = newsize;
    int* c = malloc(sizeof(int) * newsize);

    for(int i = 0; i < vec->size; i++)
    {
        c[i] = vec->arr[i];
    }

    free(vec->arr);
    vec->arr = c;
}

int popint(struct vectorint* vec)
{
    if(vec->size > 1)
    {
        int c = vec->arr[vec->size-1];
        vec->size--;
        vec->arr[vec->size-1] = 0;
        return c;
    }
    return '\0';
}

void printarr(struct vectorint vec)
{
    printf("[");
    for(int i = 0; i < vec.size; i++)
    {
        printf("%d", vec.arr[i]);
        (i < vec.size-1) ? printf(", ") : printf("]\n");
    }
}

#endif //VECTOR_HEADER

