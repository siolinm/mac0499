#include"util.h"
#ifndef _QUERIES_H
#define _QUERIES_H

/*
    BST ordered by ids
*/

/*
    returns the object with id id
*/
Object * queryQ(Node * r, int id);

/*
    recusiverly deletes from the tree the node with key key, returning the new root
*/
Node *deleteNodeQ(Node *r, Object *key);

/*
    recursively inserts node r with key key, returning the new root
*/
Node *insertNodeQ(Node *r, Object *key);

/*
    returns a new node with key key;
*/
Node *newNodeQ(Object *key);

/*
    prints the tree horizontally (for debug)
*/
void printQ(char * prefix, int size, Node * r, int b);

/*
    deallocates all memory used
*/
void removeAllQ(Node * r);

#endif