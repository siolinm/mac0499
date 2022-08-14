#include"pq.h"

void initPQ(){
    int i;
    for(i = 1; i <= n; i++){
        Q[i] = i;
        indQ[i] = i;
    }
    for(i = n/2; i >= 1; i--)
        sieve(i, n);             
    
}

int minPQ(){
    return Q[1];
}

double valuePQ(int i){
    return cert[Q[i]];
}

void updatePQ(int i, double t){
    int p, j;
    double x;
    j = indQ[i];
    cert[i] = t;
    p = j;
    x = valuePQ(j);
    while(p/2 >= 1 && x < valuePQ(p/2)){
        Q[p] = Q[p/2];
        indQ[Q[p/2]] = p;        
        p = p/2;
    }
    Q[p] = i;
    indQ[i] = p;
    sieve(indQ[i], n);
}

void sieve(int i, int m){
    int s = 2*i, p = i;
    int x = Q[i];
    while(s <= m){
        if(s < m && valuePQ(s) > valuePQ(s + 1)) 
            s += 1;
        if(cert[x] < valuePQ(s)) 
            break;

        Q[p] = Q[s];
        indQ[Q[p]] = p;        
        p = s; s = 2*p;
    }
    Q[p] = x;
    indQ[x] = p;
}