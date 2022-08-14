#include"cert.h"

void initCert(){
    int i;
    for(i = 1; i <= n - 1; i++)
        cert[i] = expire(sorted[i], sorted[i + 1]);    
}

double expire(int a, int b){
    if(speed[a] >= speed[b])
        return INFINITE;
    
    return (x0[a] - x0[b])/(speed[b] - speed[a]);
}

void update(int i){
    if(i < 1 || i > n - 1)
        return;
    cert[i] = expire(sorted[i], sorted[i + 1]);

    updatePQ(i, cert[i]);
}

void event(){
    int i;
    while(cert[i = minPQ()] == getTime()){
        swapSorted(i, i + 1);
        update(i);
        update(i - 1);
        update(i + 1);
    }
}