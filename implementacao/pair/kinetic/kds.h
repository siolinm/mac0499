#include"util.h"
#include"tourn.h"
#include"event.h"
#include"pq.h"
#include"orderedlist.h"
#include"maxima.h"
#ifndef _KDS_H
#define _KDS_H

/*! Advance in time
 * @param t the time to advance for
 */
void advance(double t);

/*! Queries for the current closest pair in the set
 *
 */
void query();

/*! Changes the speed of the j-th element
 * @param j the element that will have his speed changed
 * @param v the new speed
 */
void change(int j, Vector v);

/*! Inserts a new element with speed v and current value xt
 * @param xt the current position
 * @param v the speed
 */
void insert(Coordinate xt, Vector v);

/*! Deletes element with id i
 * @param i the id of the element
 */
void delete(int i);

/*! Initialize the KDS (initializes the structures and some variables initial values)
 *
 */
void initKDS();

/*! Build the kds (builds the strucutures after the points have been received)
 *
 */
void buildKDS();

/*! Deallocates all the memory
 *
 */
void freeKDS();

/*! Initializes the attributes from the point
 *
 */
void sendPoint(Point * p);

/*! Returns the next event time
 *
 */
double nextEvent();

/*! Show the data structures state (for debug)
 *
 */
void showInfo();

/*! Checks the closest pair by testing all the pairs of points (for debug)
 *
 */
void test();

#endif