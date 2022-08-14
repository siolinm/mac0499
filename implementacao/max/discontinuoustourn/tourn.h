#include"util.h"
#include"cert.h"
#ifndef _TOURN_H
#define _TOURN_H

/*
    Initializes the tourn
*/
void initTourn();

/*
    inserts obj in tourn and updates all needed certificates
*/
void insertTourn(Object * obj);

/*
    deletes obj of tourn
*/
void deleteTourn(Object * obj);
#endif