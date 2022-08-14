#include"heapsort.h"

double valueHeapsort(Point **v, int i, int dir){
    return getX(v[i], dir);
}

int compareH(Point **v, int i, int j, int dir){
    return wasLeft(v[j], v[i], dir);
}

void swapHeapsort(int i, int j, Point ** v){
    Point *aux;
    aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void sinkHeap(Point **v, int i, int m, int dir){
    int s = 2*i, p = i;
    Point * aux = v[i];

    while(s <= m){
        if(s < m && compareH(v, s, s + 1, dir))
            s += 1;
        if(wasLeft(aux, v[s], dir))
            break;
        v[p] = v[s];

        p = s;
        s = 2*p;
    }

    v[p] = aux;

}

void heapsort(Point ** v, int dir){
    int i;

    for(i = n/2; i >= 1; i--){
        sinkHeap(v, i, n, dir);
    }

    for(i = n; i > 1; i--){
        swapHeapsort(1, i, v);
        sinkHeap(v, 1, i-1, dir);
    }
}