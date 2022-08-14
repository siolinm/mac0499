#include"util.h"

#ifndef _HEAPSORT_H
#define _HEAPSORT_H

/*! Calculates the value of X(v[i]) in the direction dir.
 * @param v the array of points.
 * @param i the index of the point.
 * @param dir the direction to be considered.
 * @return Returns the value of X(v[i]) int the direction dir.
 */
double valueHeapsort(Point **v, int i, int dir);

/*! Compares the value of v[i] and v[j].
 * @param v the array of points.
 * @param i the index of the point.
 * @param dir the direction to be considered.
 * @return Returns 1 if value(v[i]) > value(v[j]) and 0 otherwise.
 */
int compareH(Point **v, int i, int j, int dir);

/*! Swaps v[i] and v[j]
 * @param i position of the array to be swaped
 * @param j position of the array to be swaped
 * @param v array of points
 */
void swapHeapsort(int i, int j, Point ** v);

/*! Updates the heap assuming that only v[i] is possibly in the wrong position.
 * @param v array of points.
 * @param i the position where the sink starts.
 * @param m index of the end of the heap.
 * @param dir the direction to be considered.
 */
void sinkHeap(Point **v, int i, int m, int dir);

/*! Ordenates the array of points from the rightmost point to the leftmost in
 * the direction dir
 * @param v array of points.
 * @param dir the direction to be considered.
 */
void heapsort(Point ** v, int dir);

#endif