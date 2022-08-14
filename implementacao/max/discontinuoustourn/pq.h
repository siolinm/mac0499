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
Object * minPQ();

/*
    returns the value of the certificate in the i-th priority queue position
*/
double valuePQ(int i);

/*
    Ajusta o valor do certificado do objeto c para t
    e ajusta a PQ de acordo
*/
void updatePQ(Object * c, double t);

/*
    assegurates the heap property by "sieving" elements
*/
void sieve(int i, int m);

/*
    inserts object obj in the PQ
*/
void insertPQ(Object * obj);

/*
    deletes object obj from the PQ
*/
void deletePQ(Object * obj);

#endif