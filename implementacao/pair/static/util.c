#include"util.h"


void init(int m){
    points = NULL;
    points = malloc((m+1)*sizeof(*points));
}

void destroy(){
    int i;
    for(i = 1; i <= n; i++)
        free(points[i]);
    free(points);
}

double getXCoordinate(Point * a){
    return (a->x)*cos(angle) + (a->y)*sin(angle);
}

double getYCoordinate(Point * a){
    return -(a->x)*sin(angle) + (a->y)*cos(angle);
}

void swapPoints(int i, int j){
    Point * aux;
    aux = points[i];
    points[i] = points[j];
    points[j] = aux;    
}

int checkLine(Point * a, Point * c, double theta){    
    double x;

    x = (cos(theta))*(getYCoordinate(c) - getYCoordinate(a));
    x -= (sin(theta))*(getXCoordinate(c) - getXCoordinate(a));

    if(x > EPS)
        x = 1;
    else if(x < -EPS)
        x = -1;
    else
        x = 0;

    return (int)x;
}

double distance(Point * a, Point * b){
    return sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
}