#include"tourn.h"

int compare(int i, int j){
    return (value(i) > value(j) || (value(i) == value(j) && speed[tourn[i]] > speed[tourn[j]]));
}

void initTourn(){
    int i = 2*n - 1;
    while(i > 1){
        if(compare(i, i - 1)){
            tourn[i/2] = tourn[i];
            indT[tourn[i - 1]] = i - 1;
        }
        else{
            tourn[i/2] = tourn[i - 1];
            indT[tourn[i]] = i;
        }

        i = i - 2;
    }
}