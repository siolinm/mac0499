#include<stdio.h>
#include<stdlib.h>
#include"util.h"
#include"debug.h"
#ifndef _PQ_H
#define _PQ_H

/*
    initializes the priority queue
*/
void initPQ();

/*
    returns the certificate with minimum value
*/
int minPQ();

/*
    returns the value of the certificate in the i-th priority queue position
*/
double valuePQ(int i);

/*
    updates the i-th certificate's value to t and adjust the priority queue accordingly    
*/
void updatePQ(int i, double t);

/*
    assegurates the heap property by "sieving" elements
*/
void sieve(int i, int m);

#endif