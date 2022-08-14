#include"currentTime.h"

static double now = 0;

double getTime(){
    return now;
}

void setTime(double t){
    now = t;
}