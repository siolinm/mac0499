#include<stdio.h>
#include<stdlib.h>
#include"util.h"
#include"debug.h"
#ifndef _PQ_H
#define _PQ_H

/* the priority queue size (number of elements) */
int pqSize;

/* the priority queue maximum size */
int pqMaxSize;

/*! Initializes the priority queue
 *
 */
void initPQ();

/*! Returns the certificate with minimum value
 * @return the PQObject that contains the certificate with minimum value
 */
PQObject * minPQ();

/*! Compares priority queue objects x and y
 * @param x one of the objects to be compared
 * @param y the other object
 * @return 1 if x has higher priority than y, 0 otherwise.
 */
int comparePQ(PQObject * x, PQObject * y);

/*! Returns the value of the certificate in the i-th priority queue position
 * @param i the position of the PQ
 * @return the value of the certificate in that position
 */
double valuePQ(int i);

/*! Returns the value of the certificate in the i-th priority queue position
 * @param obj the PQObject that contains a certificate
 * @return the value of the given PQObject
 */
double valuePQObject(PQObject * obj);

/*! Updates the point p certificate to value t and adjusts Q
 * @param p the point that will have his certificate updated
 * @param certType the type of certificate
 * @param t the new value t
 */
void updatePQ(Point * p, int certType, double t);

/*! Assegurates the heap property by "sieving" elements
 * @param i the starting position
 * @param m the limit of the array
 */
void sink(int i, int m);

/*! Assegurates the heap property by bringing elements up
 * @param i the starting point
 */
void swim(int i);

/*! Inserts point p with cert certType in the PQ
 * @param p the point whose certificate will be inserted
 * @param certType the certificate type
 */
void insertPQ(Point * p, int certType);

/*! Deletes point p certificate from the PQ
 * @param p the point whose certificate will be deleted
 * @param certType the certificate type
 */
void deletePQ(Point * p, int certType);

/*! Prints all elements in the PQ (for debug)
 *
 */
void printPQ();

#endif