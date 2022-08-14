#include<stdlib.h>
#include<stdio.h>

int main(int argc, char * argv[]){
    int semente, number, i;
    double min, max, x;
    min = atof(argv[2]);
    max = atof(argv[3]);
    x = max - min;
    semente = atoi(argv[1]);
    number = atoi(argv[4]);
    srand(semente);
    printf("%d\n", number);
    for(i = 0; i < number; i++){
        printf("%g %g\n", ((float)rand()/RAND_MAX)*x + min, (float)((float)rand()/RAND_MAX)*x + min);
    }

    return 0;
}