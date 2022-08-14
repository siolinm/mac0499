#include<stdlib.h>
#include<stdio.h>
#ifndef _UTIL_H
#define _UTIL_H
#define max(a, b) ((a > b) ? a : b)
#define INITIAL_SIZE 100

/*
    An element/object
*/
typedef struct Object
{
    int id;
    double speed;
    double x0;    
    double certificate;
    int pqpos;
    int lastMatch;
} Object;

/*
    An avl node
*/
typedef struct Node
{
    struct Node * left;
    struct Node * right;
    struct Object * key;
    int height;
} Node;

/*
    tourn[1] is the maximum element
*/
Object ** tourn;

/*
    priority queue that keeps the certificates 
    the certificate with the earlier expiration time is in the first position
*/
Object ** Q;

/*
   last not used id
*/
int lastID;

/*
    queries tree root
*/
Node * root;

/*
    total number of elements
*/
int n;

/*
    maximum size supported by the vectors 
*/
int maxSize;

/*
    resizes the maximum size of tourn
*/
void resize();

/*
    allocates the necessary memory for n elements
*/
void init(int m);

/* 
    deallocates the memory used 
*/
void destroy();

/*
    deallocates memory used by obj
*/
void destroyObject(Object * obj);

/*
    returns the value of the element in the i-th position in tourn
*/
double value(int i);

/*
    swaps the i-th element in tourn with the j-th element
*/
void swapTourn(int i, int j);

/*
    prints tourn (for debug)
*/
void printT(char * prefix, int size, int j, int b);

typedef int Bool;

#endif