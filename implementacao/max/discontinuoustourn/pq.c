#include"pq.h"
int m = 0;
int maxsize = INITIAL_SIZE;

void initPQ(){
    int i;
    m = n;

    for(i = m/2; i >= 1; i--){
        sieve(i, m);
    }
}

void insertPQ(Object * obj){
    int i;

    if(m + 1 == maxsize){
        Object ** W = malloc(2*maxsize*sizeof(*W));

        for(i = 1; i <= m; i++)
            W[i] = Q[i];

        free(Q);
        Q = W;
        maxsize = 2*maxsize;
    }

    Q[++m] = obj;
    obj->pqpos = m;
    updatePQ(obj, obj->certificate);
}

void deletePQ(Object * obj){
    int i = obj->pqpos;
    Q[i] = Q[m--];
    sieve(i, m);
}

Object * minPQ(){
    return Q[1];
}

double valuePQ(int i){
    return Q[i]->certificate;
}

void updatePQ(Object * obj, double t){
    int p, j;
    double x;

    j = obj->pqpos;
    obj->certificate = t;

    p = j;
    x = valuePQ(j);
    while(p/2 >= 1 && x < valuePQ(p/2)){
        Q[p] = Q[p/2];
        Q[p/2]->pqpos = p;
        p = p/2;
    }
    Q[p] = obj;
    obj->pqpos = p;
    sieve(p, n);
}

void sieve(int i, int m){
    int s = 2*i, p = i;
    Object * x = Q[i];
    while(s <= m){
        if(s < m && valuePQ(s) > valuePQ(s + 1))
            s += 1;
        if(x->certificate < valuePQ(s))
            break;

        Q[p] = Q[s];
        Q[p]->pqpos = p;
        p = s; s = 2*p;
    }
    Q[p] = x;
    x->pqpos = p;
}