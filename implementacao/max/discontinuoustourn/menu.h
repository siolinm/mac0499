#include<stdio.h>
#include"util.h"
#include"tourn.h"
#include"cert.h"
#include"pq.h"
#include"avl.h"
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
    queries for the element with maximum value
*/
void query();

/*
    changes the speed of the i-th element
*/
void change(int j, double v);

/*
    inserts element with speed v and current value xt
*/
void insert(double xt, double v);

/*
    deletes element with id i
*/
void delete(int i);

/*
    returns the next event time
*/
double nextEvent();

#endif