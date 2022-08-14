#include"util.h"
#include"currentTime.h"
#include"cert.h"
#ifndef _HEAPSORT_H
#define _HEAPSORT_H

/*
    Assegurates the heap property by "sieving" elements
*/
void sieveHeap(int i, int m);

/*
    Builds heap and sorts "sorted"
*/
void heapsort();


#endif