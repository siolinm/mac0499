#include"util.h"
#include"heapsort.h"
#include"splay_tree.h"

#ifndef _MAXIMA_H
#define _MAXIMA_H

/* Root of the maxima set tree*/
CandsNode * maximaRoot;

/*! Initializes the maxima tree in the direction considered
 * @param dir the direction considered
 */
void initMaxima(int dir);

/*! Initializes the Cands and Hits tree for all the points in the direction
 * considered
 * @param dir the direction considered
 */
void initCandsHits(int dir);

#endif