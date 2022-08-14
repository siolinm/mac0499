#include<stdio.h>

#ifndef _MENU_H
#define _MENU_H

/*! Loads the elements from a file in the following format:
 *   number of elements
 *   x0 y0 (whitespace) vx vy (of the first element)
 *   x0 y0 (whitespace) vx vy (of the second element)
 *   .....
 *   x0 y0 (whitespace) vx vy (of the n-th element)
 */
void loadFile();


#endif