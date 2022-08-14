#include "util.h"
#include "cert.h"
#ifndef _AVL_H
#define _AVL_H

/*
    BST ordered by ids
*/

/*
    returns the height of node a, -1 if NULL;
*/
int height(Node *a);

/*
    recalculates the node a height and sets its new value;
*/
void setHeight(Node *a);

/*
    returns a new node with key key;
*/
Node *newNode(Object *key);

/*
    rotates the node to the right
*/
Node *rotateRight(Node *no);

/*
    rotates the node to the left
*/
Node *rotateLeft(Node *no);

/*
    returns the node's balance, which is height(node->left) - height(node->right)
    0 if NULL
*/
int getBalance(Node *no);

/*
    recursively inserts node r with key key, returning the new root
*/
Node *insertObject(Node *r, Object *key);

/*
    returns the leftmost in element in the subtree with root r
*/
Node *leftmost(Node *r);

/*
    recusiverly deletes from the avl tree the node with key key, returning the new root
*/
Node *deleteObject(Node *r, Object *key);

/*
    returns the object with id id
*/
Object * getObject(Node * r, int id);

/*
    Prints the avl tree horizontally (for debug)
*/
void print(char * prefix, int size, Node * r, int b);

/*
   deallocates all memory used
*/
void removeAll(Node * r);

#endif