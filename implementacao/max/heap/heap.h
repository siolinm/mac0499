#include"util.h"
#include"currentTime.h"
#include"cert.h"
#include<stdio.h>
#ifndef _HEAP_H
#define _HEAP_H

/*
    assegurates the heap property by "sieving" elements
*/
void sieveHeap(int i, int m);

/*
    Initializes the heap
*/
void initHeap();


#endif