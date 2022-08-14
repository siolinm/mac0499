#include"util.h"
#include"event.h"
#ifndef _TOURN_H
#define _TOURN_H

/* the maximum size of the tourn */
int tournMaxSize;

/* the number of elements in the tourn */
int tournElem;

/*! Initializes the tourn with the given capacity
 * @param cap the given capacity
 */
void initTourn(int cap);

/*! Inserts the sent point in the end of the tourn before the "matches" have
   been played
 * @param p the sent point
 * @param dir the given direction (HORIZONTAL, UP or DOWN)
 */
void sendTourn(Point * p, int dir);

/*! Updates the pair p -- lcand(p) in the tourn
 * @param p the point whose pair will be updated
 * @param dir the given direction (HORIZONTAL, UP or DOWN)
 */
void updateTourn(Point * p, int dir);

/* Prints the tourn (for debug)
 *
 */
void printTourn();

/*! Auxiliary function that recursively prints the tourn (for debug)
 * @param prefix the blank spaces to be printed
 * @param size the size of the prefix
 * @param j the position j
 * @param b 1 if j is to the left of j/2, 0 otherwise
 */
void printT(char * prefix, int size, int j, int b);

/* Builds the tourn
 *
 */
void buildTourn();

/*! Inserts obj in tourn and updates all needed certificates
 * @param p the point to be inserted
 * @param dir the given direction (HORIZONTAL, UP or DOWN)
 */
void insertTourn(Point *p, int dir);

/*! Deletes obj in tourn and updates all needed certificates
 * @param p the point to be deleted
 * @param dir the given direction (HORIZONTAL, UP or DOWN)
 */
void deleteTourn(Point *p, int dir);

/*! Compares tourn positions i and j
 * @param i tourn position i
 * @param j tourn position j
 * @return 1 if tourn[i] wins the match with tourn[j], 0 otherwise
 */
int compareTourn(int i, int j);

/* Duplicates the maximum size of the tourn
 *
 */
void resizeTourn();

/* Initializes all tourn certificates
 *
 */
void initCertTourn();

/*! Calculates when the certificate between tourn objects a and b will expire
 * @param a one of the tourn objects
 * @param b the other tourn object
 * @return returns the time when the certificate will expire
 */
double expireTourn(TournObject * a, TournObject * b);

/*! Creates a new certificate for the given tourn object
 * @param obj the given tourn object
 */
void newCertTourn(TournObject * obj);

/*! Updates the certificate of the given tourn object
 * @param a the given tourn object
 */
void updateTournCert(TournObject * a);

#endif