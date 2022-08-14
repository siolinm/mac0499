#include"cert.h"
#include<stdio.h>

void initCert(){
    int i;
    for(i = 1; i <= n; i++){
        if(indT[i] != 1)
            cert[i] = expire(tourn[indT[i]/2], tourn[indT[i]]);
        else
            cert[i] = INFINITE;
    }
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
    int j = tourn[i];
    /*j = indT[i]; */ /* position when the i-th element was in the moment it lost a match */
    if(i == 1){
        cert[j] = INFINITE;
        updatePQ(j, cert[j]);
        return;
    }
    if(j < 1 || j > n)
        return;
    cert[j] = expire(tourn[i/2], tourn[i]);
    
    updatePQ(j, cert[j]);
}



/* 
    The first certificate in the PQ has expired
*/
void event(){
    int i, j, k;    
    while(cert[i = minPQ()] == getTime()){
        j = indT[i];
        k = 2*(j/2) + !(j % 2);
        
        while(j > 1 && (value(j) > value(k) || (value(j) == value(k) && speed[tourn[j]] > speed[tourn[k]]))){
            tourn[j/2] = tourn[j];
            k = 2*(j/2) + !(j % 2);
            indT[tourn[k]] = k;
            update(k);
            
            j = j/2;
            k = 2*(j/2) + !(j % 2);
        }
        
        indT[tourn[j]] = j;
        update(j);
    }
}