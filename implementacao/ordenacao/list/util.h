#include<stdlib.h>
#include<stdio.h>
#include"currentTime.h"
#ifndef _UTIL_H
#define _UTIL_H
#define max(a, b) ((a > b) ? a : b)

/*
    cert[i] keeps the certificate between i/2 and i (the time that the certificate expires)
*/
double * cert;

/*
    speed[i] is the i-th element speed
*/
double * speed;

/*
    x0[i] is the i-th element initial value
*/
double * x0;

/*
    sorted[i] is the i-th element 
*/
int * sorted;

/*
    naive 
*/
int * naive;

/*
    priority queue that keeps the certificates 
    the certificate with the earlier expiration time is in the first position
*/
int * Q;

/*
    indQ[i] is the position of the i-th certificate in the priority queue Q;
*/
int * indQ;

/*
    indS[i] is the position of the i-th element in sorted
*/
int * indS;

/*
    total number of elements
*/
int n;

/*
    allocates the necessary memory for n elements
*/
void init(int m);

/* 
    deallocates the memory used 
*/
void destroy();

/*
    returns the value of the element in the i-th position in sorted
*/
double value(int i);

/*
    swaps the i-th element in sorted with the j-th element
*/
void swapSorted(int i, int j);

typedef int Bool;

void printS();

void printC();

void printPQ();

void printIQ();

void printIS();

#endif