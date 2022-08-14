#include "util.h"
#include "event.h"
#ifndef _ORDEREDLIST_H
#define _ORDEREDLIST_H

AVLNode * listRoot[3];

/*! Initializes the trees in every direction
 *
 */
void listInit();

/*! Inserts the point a into the list with direction dir
 * @param a the point to be inserted
 * @param dir the direction considered
 */
void listInsert(Point * a, int dir);

/*! Deletes point a from the list with direction dir
 * @param a the point to be deleted
 * @param dir the direction considered
 */
void listDelete(Point * a, int dir);

/*! Swaps the points p and q in the AVL tree and in the linked list
 * @param p one the points to be swaped
 * @param q the other point to be swaped
 * @param dir the direction considered
 */
void listSwap(Point * p, Point * q, int dir);

/*! Creates a new certificate for the point p, considering the list for
 * direction dir
 * @param p the point that will have a new certificate
 * @param dir the direction considered
 */
void newCertList(Point *p, int dir);

/*! Updates the certificate for the point p, considering the list for
 * direction dir
 * @param p the point that will have his certificate updated
 * @param dir the direction considered
 */
void updateListCert(Point * p, int dir);

/*! Calculates the expiration time of the certificate between a and b
 * considering the list in direction dir
 * @param a one of the points
 * @param b
 * @param dir the direction considered
 * @return the expiration time
 */
double expireList(Point *a, Point * b, int dir);

/*! Returns the height of node a, -1 if NULL;
 * @param a an AVL node
 * @return the height of a
 */
int height(AVLNode *a);

/*! Recalculates the node a height and updates his height;
 * @param a the node to have his height recalculated
 */
void setHeight(AVLNode *a);

/*! Returns a new node with key key;
 * @param key the key of the new node
 * @param dir the direction considered
 * @return the new node created
 */
AVLNode *newAVLNode(Object *key, int dir);

/*! Rotates the node to the right
 * @param no the node to be rotated
 * @return the root of the new subtree after the rotation
 */
AVLNode *rotateRight(AVLNode *no);

/*! Rotates the node to the left
 * @param no the node to be rotated
 * @return the root of the new subtree after the rotation
 */
AVLNode *rotateLeft(AVLNode *no);

/*! Returns the node's balance, which is height(node->left) -
 *   height(node->right) 0 if NULL
 * @param no the node whose balance will be calculated
 * @return the balance of the node
 */
int getBalance(AVLNode *no);

/*! Recursively inserts node r with key key and adjusts the linked list,
 *   returning the new root
 * @param r the root of the tree
 * @param key the key to be inserted
 * @param dir the direction considered
 * @return the root of the subtree after the insertion
 */
AVLNode *insertAVLNode(AVLNode *r, Object *key, int dir);

/*! Calculates the leftmost in element in the subtree with root r
 * @param r the root of the subtree considered
 * @return the leftmost element in the subtree
 */
AVLNode *leftmost(AVLNode *r);

/*! Recusiverly deletes from the avl tree the node with key key, adjusting the
 * linked list in the process, returning the new root
 * @param r the root of the subtree considered
 * @param key the key to be deleted
 * @param dir the direction considered
 * @return the new root of the subtree after the deletion
 */
AVLNode *deleteAVLNode(AVLNode *r, Object *key, int dir);

/*! Queries for the k-th element in the avl tree
 * @param r the root of the subtree considered
 * @param i the i-th element being searched in the subtree
 * @return the i-th element in the avl tree
 */
Object * query_kth(AVLNode *r, int i);

/*! Prints the avl tree horizontally (for debug)
 * @param prefix the blank spaces and symbols that will be printed
 * @param size the size of the prefix
 * @param r the root of the subtree being printed
 * @param b boolean parameter that indicates we're on the right or the left of
 * the subtree
 */
void print(char * prefix, int size, AVLNode * r, int b);

/*! Deallocates all memory used
 * @param r the root of the subtree being deallocated
 */
void removeAll(AVLNode * r);

/*! Prints the elements in the list order (for debug)
 * @param dir the direction considered
 */
void printList(int dir);

#endif