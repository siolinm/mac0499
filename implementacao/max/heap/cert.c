#include"cert.h"
#include"pq.h"
#include<stdio.h>

void initCert(){
    int i;
    for(i = 2; i <= n; i++)
        cert[i] = expire(heap[i/2], heap[i]);
}


double expire(int a, int b){
    /*
        Assuming a already has a greater value than b
    */
    if(speed[a] >= speed[b])
        return INFINITE;

    return (x0[a] - x0[b])/(speed[b] - speed[a]);
}


void update(int i){
    if(i <= 1 || i > n)
        return;
    cert[i] = expire(heap[i/2], heap[i]);

    updatePQ(i, cert[i]);
}

void event(){
    int i;
    while(cert[i = minPQ()] == getTime()){
        swapHeap(i, i/2);
        update(i);
        update(i/2);
        update(2*(i/2) + !(i % 2));
        update(2*i);
        update(2*i + 1);
    }
}