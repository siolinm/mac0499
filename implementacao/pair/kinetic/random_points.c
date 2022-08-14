#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI acos(-1)

double random_number(double min, double max){
    double x = (double)rand()/RAND_MAX;
    return (max - min)*x + min;
}

int main(int argc, char * argv[]){
    double maxx, maxy, theta, x, y, vx, vy;
    int seed, n, i;
    char c = 'a';

    if(argc < 5){
        printf("Enter coordinates limits, the seed and the number of points\n");
        exit(0);
    }

    maxx = atof(argv[1]);
    maxy = atof(argv[2]);
    seed = atoi(argv[3]);
    n = atoi(argv[4]);
    srand(seed);

    printf("%d\n", n);
    for (i = 0; i < n; i++, c++){
        theta = random_number(0, 2*PI);
        x = random_number(-maxx, maxx);
        y = random_number(-maxy, maxy);
        vx = cos(theta);
        vy = sin(theta);
        printf("%.3lf %.3lf %.3lf %.3lf %c\n", x, y, vx, vy, c);
    }

    return 0;
}