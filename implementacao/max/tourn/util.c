#include"util.h"
#include"currentTime.h"

void init(int m){
    n = m;
    cert = malloc(n*sizeof(*cert));
    tourn = malloc((2*n)*sizeof(*tourn));
    x0 = malloc((n + 1)*sizeof(*x0));
    speed = malloc((n + 1)*sizeof(*speed));
    Q = malloc((n + 1)*sizeof(*Q));
    indQ = malloc((n + 1)*sizeof(*indQ));
    indT = malloc((n + 1)*sizeof(*indT));
}

void destroy(){
    free(cert);
    free(tourn);
    free(x0);
    free(speed);
    free(Q);
    free(indQ);
    free(indT);
}

double value(int i){
    i = tourn[i];
    return x0[i] + speed[i]*getTime();
}

void printT(){
    int i;
    for(i = 1; i <= 2*n - 1; i++)
        printf("tourn[%d] = %d\n", i, tourn[i]);

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

void printIT(){
    int i;
    for(i = 1; i <= n; i++)
        printf("indT[%d] = %d\n", i, indT[i]);

    printf("\n");
}

void printC(){
    int i;
    for(i = 2; i <= n; i++)
        printf("cert[%d] = %g\n", i, cert[i]);

    printf("\n");
}

void swapTourn(int i, int j){
    int aux = tourn[i];
    tourn[i] = tourn[j];
    tourn[j] = aux;
    indT[tourn[j]] = j;
    indT[tourn[i]] = i; 
}