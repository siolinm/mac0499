#include"cert.h"
#include<stdio.h>

void initCert(){
    int i;
    Object * a;
    for(i = 2*n - 1; i >= n; i--){
        a = tourn[i];
        
        if(a->lastMatch != 1)
            newCert(a);
        else
            a->certificate = INFINITE;
    }
}

double expire(Object * a, Object * b){
    if(a == NULL || a->speed >= b->speed)
        return INFINITE;

    return (a->x0 - b->x0)/(b->speed - a->speed);
}

void newCert(Object * obj){
    obj->certificate = expire(tourn[obj->lastMatch/2], obj);
}

void update(Object * a){
    if(a == NULL)
        return;    
    updatePQ(a, expire(tourn[a->lastMatch/2], a));
}

/* 
    The first certificate in the PQ has expired
*/
void event(){
    int j, k;
    Object * a;
    while((a = minPQ())->certificate == getTime()){
        j = a->lastMatch;
        k = 2*(j/2) + !(j % 2);
        
        while(j > 1 && (value(j) > value(k) || (value(j) == value(k) && tourn[j]->speed > tourn[k]->speed))){
            tourn[j/2] = tourn[j];            
            tourn[k]->lastMatch = k;
            update(tourn[k]);
            
            j = j/2;
            k = 2*(j/2) + !(j % 2);
        }
        
        tourn[j]->lastMatch = j;
        update(tourn[j]);
    }
}