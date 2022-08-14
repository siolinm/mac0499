#include"heapsort.h"
#include"util.h"

double value(int i){
    return getXCoordinate(points[i]);
}

void sieve(int i, int m){
    Point * aux = points[i];
    int c = 2*i, p = i;
    double x = value(i);
    while(c <= m){
        if(c < m && value(c) < value(c + 1)) 
            c += 1;

        if(x >= value(c))
            break;
        points[p] = points[c];        
        p = c;
        c = 2*p;
    }
    points[p] = aux;
}

void heapsort(){
    int i;

    for(i = n/2; i >= 1; i--)
        sieve(i, n);
    
    for(i = n; i > 1; i--){
        swapPoints(1, i);
        sieve(1, i-1);
    }
}