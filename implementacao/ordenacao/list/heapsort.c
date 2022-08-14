#include"heapsort.h"

int compare(int i, int j){
    return (value(i) > value(j) || (value(i) == value(j) && speed[sorted[i]] > speed[sorted[j]]));
}

void sieveHeap(int i, int m){
    int s = 2*i, p = i;
    double x = value(i);
    double sp = speed[sorted[i]];
    i = sorted[i];
    while(s <= m){
        if(s < m && compare(s, s + 1)) 
            s += 1;
        if(x < value(s) || (x == value(s) && sp < speed[sorted[s]]))
            break;
        sorted[p] = sorted[s];
        indS[sorted[s]] = p;
        p = s;
        s = 2*p;
    }
    sorted[p] = i;
    indS[i] = p;
}

void heapsort(){
    int i;

    for(i = n/2; i >= 1; i--){
        sieveHeap(i, n);
    }
    for(i = n; i > 1; i--){
        
        swapSorted(1, i);
        sieveHeap(1, i-1);
    }
}