#include"util.h"

void init(int m){
    lastID = 1;
    root = r = NULL;
    n = m;
    Q = malloc((INITIAL_SIZE + 1)*sizeof(*Q));
}

void destroy(){
    free(Q);
}

void destroyObject(Object * a){
    free(a);
}

double value(Object * e){
    return e->initv + e->speed*getTime();
}

/*
    assuming b->next = a
*/
void swapObjects(Object * a, Object * b){    
    Node * noa = a->node;
    Node * nob = b->node;
    
    noa->key = b;
    b->node = noa;
    
    nob->key = a;        
    a->node = nob;

    b->next = a->next;
    a->prev = b->prev;    
    b->prev = a;
    a->next = b;
    if(a->prev)
        a->prev->next = a;
    if(b->next)
        b->next->prev = b;
}