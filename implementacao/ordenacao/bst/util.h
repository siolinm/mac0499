#include<stdlib.h>
#include<stdio.h>
#include"currentTime.h"
#include"debug.h"
#ifndef _UTIL_H
#define _UTIL_H
#define max(a, b) ((a > b) ? a : b)
/*priority queue initial size*/
#define INITIAL_SIZE 100

/*
    An element/object
*/
typedef struct Object
{
    int id;
    double speed;
    double initv;
    struct Object * next;
    struct Object * prev;
    double certificate;
    int pqpos;
    struct Node * node;
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
    int children;
} Node;

/*
    total number of elements
*/
int n;

/*
    priority queue
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
    avl tree root
*/
Node * r;

/*
    allocate all memory needed for m elements
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
    swaps element i with element j in the avl tree and the linked list
*/
void swapObjects(Object * i, Object * j);

/*
    value of object e
*/
double value(Object * e);

/*
    prints the linked list (for debug)
*/
void printL();

typedef int Bool;

#endif