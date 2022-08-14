#include"util.h"
#include<stdio.h>
#ifndef _SPLAY_H
#define _SPLAY_H

/* The trees have an unusual structure: there is a node x that stores who is the
point that "owns" the entire tree. The parent of this node x is the real root of
the tree and the parent of the root is this node x */

/*! Inserts the point a in the splay tree with the given root
 * @param root the root of the tree
 * @param a the point to be inserted
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 */
void insertS(void * root, Point * a, int type, int dir);

/*! Deletes the point a in the splay tree with the given root
 * @param root the root of the tree
 * @param a the point to be deleted
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 */
void deleteS(void * root, Point * a, int type, int dir);

/*! "Splays" the given node (bring him to the root of the tree)
 * @param x the node to be "splayed"
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 */
void splay(void * x, int type, int dir);

/*! Splits the left subtree of the given root
 * @param root the root to be given
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @return the new tree created after the split
 */
void * splitL(void *root, int type, int dir);

/*! Splits the right subtree of the given root
 * @param root the root to be given
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @return the new tree created after the split
 */
void * splitR(void * root, int type, int dir);

/*! Joins the rootS and rootL into one tree assuming all elements in rootS tree
 * are less valuable than rootL elements
 * @param rootS one of the roots to be given
 * @param rootL the other root to be given
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @return the new tree created after the join
 */
void * joinS(void * rootS, void * rootL, int type, int dir);

/*! Returns the successor of point p in the given tree, direction and order
 * @param root the root of the tree that will be searched
 * @param p the point whose successor is being searched
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @param order the order based on the edges of Dom(p) (UP or DOWN)
 * @return the node that contains the successor of the point (NULL if none)
 */
void * successorS(void * root, Item * p, int type, int dir, int order);

/*! Returns the predecessor of point p in the given tree, direction and order
 * @param root the root of the tree that will be searched
 * @param p the point whose predecessor is being searched
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @param order the order based on the edges of Dom(p) (UP or DOWN)
 * @return the node that contains the predecessor of the point (NULL if none)
 */
void * predecessorS(void * root, Item * p, int type, int dir, int order);

/*! Returns the point who is the owner of the entire tree
 * @param root the node where to start going up
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @return the point who is the owner of the tree
 */
Point * ownerS(void * root, int type, int dir);

/*! Extracts a subtree of the tree with given based on low and up
 * @param root the given root
 * @param low the element with the minimum value that is not in the subtree
 * extracted
 * @param up the element with the maximum value that is not in the subtree
 * extracted
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @return returns the root of the subtree extracted
 */
void * extractS(void * root, void * low, void * up, int type, int dir);

/* ---------------------------------------------- */

/*! Rotates the subtree with root x to the left
 * @param x the root of the subtree
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 */
void rotateLeftS(void * x, int type, int dir);

/*! Rotates the subtree with root x to the right
 * @param x the root of the subtree
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 */
void rotateRightS(void * x, int type, int dir);

/*! Creates the "x" node for point p
 * @param p the point who will be initialized
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 */
void initS(Point * p, int type, int dir);

/*! Creates a new node containing the given key
 * @param key the key that will be stored in the new node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 */
void * createNodeS(Point * key, int type, int dir);

/*! Auxiliar function that inserts recursively a node in the splay tree
 * @param root the root of the subtree
 * @param node the node to be inserted
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @return returns the new root of the three
 */
void * insertSR(void * root, void * node, int type, int dir);

/*! Auxiliar function that delete recursively a node from the splay tree
 * @param root the root of the subtree
 * @param a the point to be deleted
 * @param parent stores the parent of the last node visited (for splay)
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @return returns the new root of the three
 */
void * deleteSR(void * root, Point * a, void **parent, int type, int dir);

/*! Compares two points based on the three type and returns 1 if the point a
 must be to the right, 0 otherwise
 * @param a one of the points to be compared
 * @param b the other point to be compared
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @return 1 if a must be in the right subtree of b, 0 otherwise
 */
int compareS(Point * a, Point * b, int type, int dir);

/*! Swaps the keys of roota and rootb
 * @param roota one of the node that will have his key swaped
 * @param rootb the other node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 */
void swapS(void * roota, void * rootb, int type, int dir);

/*! Deallocates all memory from the tree
 * @param root the root of the subtree to be freed
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 */
void freeAllS(void * root, int type, int dir);

/* ---------------------------------------------- */

/*! Connects the "x" root of the tree roota and the real root rootb
 * @param roota the "x" root of the tree
 * @param rootb the real root
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 */
void attach(void * roota, void * rootb, int type, int dir);

/*! Disconnects the "x" root of the tree roota and the real root
 * @param root the "x" root of the tree
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param dir the direction considered
 * @return the real root of the tree
 */
void * detach(void * root, int type, int dir);

/*! Sets x->left = y based on the type of the tree
 * @param x the root node
 * @param y the left subtree node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 */
void setLeftS(void * x, void * y, int type);

/*! Sets x->right = y based on the type of the tree
 * @param x the root node
 * @param y the right subtree node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 */
void setRightS(void * x, void * y, int type);

/*! Sets x->parent = y based on the type of the tree
 * @param x the root node
 * @param y the parent node of the node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 */
void setParentS(void * x, void * y, int type);

/*! Sets x->leftmost = y for the CANDS_TREE node
 * @param x the root node
 * @param y the leftmost (node that contains the leftmost point) node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 */
void setLeftmostS(void * x, void * y, int type);

/*! Sets x->key = a based on the type of the tree
 * @param x the root node
 * @param a the point that is the key
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 */
void setKeyS(void * x, Point * a, int type);

/*! Returns x->left based on the type of the tree
 * @param x the root node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @return x->left
 */
void * getLeftS(void * x, int type);

/*! Returns x->right based on the type of the tree
 * @param x the root node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @return x->right
 */
void * getRightS(void * x, int type);

/*! Returns x->parent based on the type of the tree
 * @param x the root node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @return x->parent
 */
void * getParentS(void * x, int type);

/*! Returns x->leftmost based on the type of the tree
 * @param x the root node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @return x->leftmost
 */
void * getLeftmostS(void * x, int type);

/*! Returns x->key based on the type of the tree
 * @param x the root node
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @return x->key
 */
Point * getKeyS(void * x, int type);

/*! Updates the leftmost for the given CANDS_TREE node
 * @param x the root node
 * @param dir the direction considered
 */
void updateLeftmost(void * x, int dir);

/*! Prints all elements in the tree with "x" root given (for debug)
 * @param x the given "x" root
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 */
void printS(void * root, int type);

/*! Auxiliar function that prints recursively the tree with the given root (for debug)
 * @param root the given root
 * @param prefix the blank spaces before printing
 * @param type the type of the tree (CANDS_TREE, HITS_LOW_TREE or HITS_UP_TREE)
 * @param size the size of the prefix
 * @param b whether root is the left or the right subtree
 */
void printSR(void * root, char * prefix, int type, int size, int b);

#endif