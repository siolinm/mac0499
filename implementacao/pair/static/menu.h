#include"util.h"
#include"splay.h"
#include"heapsort.h"
#ifndef _MENU_H
#define _MENU_H

/*
    load points in mode 'mode', 'i' for interactive
*/
void loadPoints(char mode);

/*
    find the closest distance between points in points vector
*/
double closestDistance();

/*
    options menu
*/
void menu();

#endif