#include"util.h"
#include"currentTime.h"

void init(int m){
    n = m;
    cert = malloc(n*sizeof(*cert));
    heap = malloc((n + 1)*sizeof(*heap));
    x0 = malloc((n + 1)*sizeof(*x0));
    speed = malloc((n + 1)*sizeof(*speed));
    Q = malloc((n + 1)*sizeof(*Q));
    indQ = malloc((n + 1)*sizeof(*indQ));
    indH = malloc((n + 1)*sizeof(*indH));
}

void destroy(){
    free(cert);
    free(heap);
    free(x0);
    free(speed);
    free(Q);
    free(indQ);
    free(indH);
}

double value(int i){
    i = heap[i];
    return x0[i] + speed[i]*getTime();
}

void printH(){
    int i;
    for(i = 1; i <= n; i++)
            printf("heap[%d] = %d\n", i, heap[i]);

    printf("\n");
}

void printPQ(){
    int i;
    for(i = 1; i <= n-1; i++)
        printf("Q[%d] = %d\n", i, Q[i]);

    printf("\n");
}

void printIQ(){
    int i;
    for(i = 1; i <= n-1; i++)
        printf("indQ[%d] = %d\n", i, indQ[i]);

    printf("\n");
}

void printIH(){
    int i;
    for(i = 1; i <= n; i++)
        printf("indH[%d] = %d\n", i, indH[i]);

    printf("\n");
}

void printC(){
    int i;
    for(i = 2; i <= n; i++)
        printf("cert[%d] = %g\n", i, cert[i]);

    printf("\n");
}

void swapHeap(int i, int j){
    int aux = heap[i];
    heap[i] = heap[j];
    heap[j] = aux;
    indH[heap[i]] = j;
    indH[heap[j]] = i;
}