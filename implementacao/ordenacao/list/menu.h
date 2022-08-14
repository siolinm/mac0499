#include"util.h"
#ifndef _MENU_H
#define _MENU_H

/* 
    advance in time
*/
void advance(double t);

/*
loads the elements from a file in the following format:
    number of elements
    angular coefficient (whitespace) linear coefficient (of the first element)
    angular coefficient (whitespace) linear coefficient (of the second element)
    .....
    angular coefficient (whitespace) linear coefficient (of the n-th element)
 */
void loadFile();

/*
    options menu
 */
int menu();

/* 
    queries for the i-th element in the list
*/
void query();

/*
    changes the speed of the i-th element
*/
void change(int j, double v);

/*
    returns the next event time
*/
double nextEvent();

/*
    sorts naive vector heapsort 
*/
void queryNaive();

#endif