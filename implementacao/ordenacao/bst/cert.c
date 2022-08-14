#include"cert.h"
#include<stdio.h>

void initCert(Node * r){
    if(!r)
        return; 
    initCert(r->left);
    initCert(r->right);
    newCert(r->key);
}

void newCert(Object * obj){
    obj->certificate = expire(obj, obj->prev);
}

double expire(Object * a, Object * b){
    if(b == NULL || a->speed >= b->speed)
        return INFINITE;

    return (a->initv - b->initv)/(b->speed - a->speed);
}

void update(Object * obj){
    if(obj == NULL)
        return;
    updatePQ(obj, expire(obj, obj->prev));
}

void event(){
    Object * obj = minPQ();
    while(obj->certificate == getTime()){
        swapObjects(obj, obj->prev);
        printL();
        obj = obj->next;
        update(obj);
        update(obj->prev);
        update(obj->next);
        obj = minPQ();
    }
}