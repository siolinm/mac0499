#include"currentTime.h"

static double currentTime = 0;

double getTime(){
    return currentTime;
}

void setTime(double t){
    currentTime = t;
}