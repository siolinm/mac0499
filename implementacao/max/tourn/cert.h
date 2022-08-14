#include"pq.h"
#include"currentTime.h"
#include"debug.h"
#include"util.h"
#ifndef _CERT_H
#define _CERT_H

/*
    Initializes all certificates
*/
void initCert();

/*
    Calculates the expiration time between elements a and b
*/
double expire(int a, int b);

/*
    updates the i-th certificate
*/
void update(int i);

/*
    An event
*/
void event();

#endif