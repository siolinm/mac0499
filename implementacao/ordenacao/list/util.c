#include"util.h"

void init(int m){
    n = m;
    cert = malloc(n*sizeof(*cert));
    sorted = malloc((n + 1)*sizeof(*sorted));
    naive = malloc((n + 1)*sizeof(*naive));
    x0 = malloc((n + 1)*sizeof(*x0));
    speed = malloc((n + 1)*sizeof(*speed));
    Q = malloc((n + 1)*sizeof(*Q));
    indQ = malloc((n + 1)*sizeof(*indQ));
    indS = malloc((n + 1)*sizeof(*indS));
}

void destroy(){
    free(cert);
    free(sorted);
    free(naive);
    free(x0);
    free(speed);
    free(Q);
    free(indQ);
    free(indS);
}

double value(int i){
    i = sorted[i];
    return x0[i] + speed[i]*getTime();
}

void printS(){
    int i;
    for(i = 1; i <= n; i++)
            printf("sorted[%d] = %d\n", i, sorted[i]);

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

void printIS(){
    int i;
    for(i = 1; i <= n; i++)
        printf("indS[%d] = %d\n", i, indS[i]);

    printf("\n");
}

void printC(){
    int i;
    for(i = 1; i <= n-1; i++)
        printf("cert[%d] = %g\n", i, cert[i]);

    printf("\n");
}

void swapSorted(int i, int j){
    int aux = sorted[i];
    sorted[i] = sorted[j];
    sorted[j] = aux;
    indS[sorted[i]] = j;
    indS[sorted[j]] = i; 
}