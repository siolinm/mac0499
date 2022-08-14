#include"heap.h"
#include"util.h"

int compare(int i, int j){
    return (value(i) < value(j) || (value(i) == value(j) && speed[heap[i]] < speed[heap[j]]));
}

void sieveHeap(int i, int m){
    int s = 2*i, p = i;
    double x = value(i);
    double sp = speed[heap[i]];
    i = heap[i];

    while(s <= m){
        if(s < m && compare(s, s + 1))
            s += 1;
        if(x > value(s) || (x == value(s) && sp > speed[heap[s]]))
            break;

        heap[p] = heap[s];
        indH[heap[s]] = p;
        p = s;
        s = 2*p;
    }
    heap[p] = i;
    indH[i] = p;
}

void initHeap(){
    int i;

    for(i = n/2; i >= 1; i--)
        sieveHeap(i, n);
}