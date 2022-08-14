#include"util.h"
#ifndef _SPLAY_H
#define _SPLAY_H

typedef struct Node
{
    struct Node * left;
    struct Node * right;
    struct Node * parent;
    Item * key;
} Node;

/*
    Root of the splay tree
*/
Node * root;

/*
    Inserts key in the splay tree
*/
void insert(Item * key);

/*
    Splays node x
*/
void splay(Node * x);

/*
    Rotates node x to the left, if x was the root the root is updated
*/
void rotateLeft(Node * x);

/*
    Rotates node x to the right, if x was the root the root is updated
*/
void rotateRight(Node * x);

/*
    Creates a new node with key key
*/
Node * createNode(Item * key);

/*
    Query for low in dominance of p, using start as the root
*/
Node * queryLow(Item * p, Node * start);

/*
    Query for up in dominance of p, using start as the root
*/
Node * queryUp(Item * p, Node * start);

/*
    Extracts Cands(p) from the splay tree
*/
Node * cands(Item * p);

/*
    Looks for the point with minimum x in Cands(p) with root lcandsRoot
*/
Item * lcand(Node * lcandsRoot, Item * min);

/*
    Compares items (points) a and b, if b should be on the left subtree of a returns 1, otherwise returns 0
*/
int compare(Item * a, Item * b);

/*
    Deallocate all memory used in the splay tree
*/
void freeAll(Node * r);

/*
    Prints the splay tree (for debug)
*/
void print(char * prefix, int size, Node * r, int b);

#endif