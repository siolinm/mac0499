#include<stdio.h>
#include"math.h"

typedef struct Point
{
    double x;
    double y;
} Point;

Point pontos[11234567];

double distancia(Point * a, Point * b){
    return (a->x-b->x)*(a->x-b->x) + (a->y-b->y)*(a->y-b->y);
}

int main(){
    double distance, minDistance = 1e8;
    int i, j, number;

    scanf("%d", &number);
    for(i = 0; i < number; i++){
        scanf("%lf %lf", &(pontos[i].x), &(pontos[i].y));
    }

    for(i = 0; i < number; i++){
        for(j = i + 1; j < number; j++){
            distance = distancia(pontos + i, pontos + j);
            if(distance < minDistance)
                minDistance = distance;
        }
    }

    printf("%g\n", sqrt(minDistance));
    return 0;
}