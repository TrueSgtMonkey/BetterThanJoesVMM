#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <stdio.h>
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
int inputIntoVec(FILE* file, struct vectorchar* vec);
int getNumFromVectorchar(struct vectorchar* vec);
char* getFileNameFromVecchar(char* filename, char* extension);
char* combineStrings(char* s1, char* s2);

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


#endif //VECTOR_HEADER

