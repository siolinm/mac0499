#include"math.h"
#include<stdlib.h>
#include<stdio.h>
#ifndef _UTIL_H
#define _UTIL_H
#define INFINITE 1e8
#define EPS 1e-6
#define PI_3 acos(0.5)

typedef struct Point
{
    double x;
    double y;
} Point;

typedef Point Item;

/*
    Coordinate system rotation
*/
double angle;

/*
    Vector of points
*/
Point ** points;

/*
    Number of points
*/
int n;

/*
    Allocates memory for m points
*/
void init(int m);

void destroy();

/*
    Get x coordinate from point a in the coordinate system rotated by angle
*/
double getXCoordinate(Point * a);

/*
    Get y coordinate from point a in the coordinate system rotated by angle
*/
double getYCoordinate(Point * a);

/*
    Swaps values in index i and j from points
*/
void swapPoints(int i, int j);

/*
    Returns 1 if point c is to the left of the 
    parallel line to the x-axis that passes through point c rotated by theta (counterclockwise)
    0 if point c is in that line and -1 if point c is to the right of that line
*/
int checkLine(Point * a, Point * c, double theta);

/*
    Calculates the distance between items (points) a and b
*/
double distance(Item * a, Item * b);


#endif