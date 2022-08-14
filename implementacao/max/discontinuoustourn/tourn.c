#include"tourn.h"

int compare(int i, int j){
    return (value(i) > value(j) || (value(i) == value(j) && tourn[i]->speed > tourn[j]->speed));
}

void initTourn(){
    int i = 2*n - 1;
    
    while(i > 1){
        if(compare(i, i - 1)){
            tourn[i/2] = tourn[i];
            tourn[i - 1]->lastMatch = i - 1;
        }
        else{
            tourn[i/2] = tourn[i - 1];
            tourn[i]->lastMatch = i;
        }

        i = i - 2;
    }

    tourn[1]->lastMatch = 1;
}

void insertTourn(Object * obj){
    int i, k;

    if(2*n + 1 == maxSize)
        resize();
    n++;

    i = 2*n - 1;

    tourn[i] = obj;
    tourn[i - 1] = tourn[i/2];
    
    k = i - 1;

    while(i > 1 && compare(i, k)){
        tourn[i/2] = tourn[i];
        tourn[k]->lastMatch = k;
        update(tourn[k]);
        
        i = i/2;
        k = 2*(i/2) + !(i % 2);
    }

    tourn[i]->lastMatch = i;    
}

void deleteTourn(Object * obj){
    int k, j, i = obj->lastMatch;

    /*
        Looks for the "first match" that obj played
    */
    j = i;
    k = 2*(j/2) + !(j % 2);

    if(2*j < 2*n - 1){
        while(j < 2*n - 1){
            if(j > 1 && tourn[j] != tourn[j/2])
                j = k;
            
            j = 2*j;
            k = 2*(j/2) + !(j % 2);
        }

        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }

    /*
        Looks for a object to substitute the removed one.
        The object that will substitute the removed object is 
        the one who lost the match between the two last positions.
        If the object that is being removed is already at one of the two last positions
        remove the two last positions and make his brother go up
    */
    if(j == 2*n - 1 || j == 2*n - 2){
        tourn[j/2] = tourn[k];
        tourn[j] = tourn[k] = NULL;
        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }
    else{
        if(tourn[2*n - 1] == tourn[n - 1])
            tourn[j] = tourn[2*n - 2];
        else
            tourn[j] = tourn[2*n - 1];        

        tourn[2*n - 1] = tourn[2*n - 2] = NULL;
    }

    /*
        Now our number of elements has oficially decreased
    */
    n--;

    /*
        Goes up fixing matches, j is the winner and k is the loser of the match
    */
    while(j > 1){
        if(!compare(j, k)){
            i = k;
            k = j;
            j = i;
        }

        tourn[j/2] = tourn[j];
        tourn[k]->lastMatch = k;
        update(tourn[k]);
        
        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }

    tourn[j]->lastMatch = j;
    update(tourn[j]);
}