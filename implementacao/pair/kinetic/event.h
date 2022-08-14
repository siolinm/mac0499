#include"pq.h"
#include"debug.h"
#include"util.h"
#ifndef _CERT_H
#define _CERT_H

/*! Updates the tourn after an event
 *
 */
void tournEvent();

/*! Updates the list after an event and calls the functions horizontalEvent,
 * upEvent and downEvent
 *
 */
void listEvent();

/*! Updates all the data structures for a horizontal event
 * @param p one of the points involved in the event
 * @param q the other point involved
 * @param dir the direction of the event (UP, DOWN or HORIZONTAL)
 */
void horizontalEvent(Point * p, Point * q, int dir);

/*! Updates all the data structures for an up event
 * @param p one of the points involved in the event
 * @param q the other point involved
 * @param dir the direction of the event (UP, DOWN or HORIZONTAL)
 */
void upEvent(Point * p, Point * q, int dir);

/*! Updates all the data structures for a down event
 * @param p one of the points involved in the event
 * @param q the other point involved
 * @param dir the direction of the event (UP, DOWN or HORIZONTAL)
 */
void downEvent(Point * p, Point * q, int dir);

/*! Calls a list event or a tourn event when they occur
 *
 */
void event();

#endif