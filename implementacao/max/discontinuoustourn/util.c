#include"util.h"
#include"currentTime.h"

void init(int m){
    n = m;
    tourn = malloc((2*n)*sizeof(*tourn));
    Q = malloc((n + 1)*sizeof(*Q));
    tourn[0] = NULL;
    root = NULL;
    lastID = 1;
}

/*
    minimum size has to be at least 2
*/
void resize(){
    int i;
    Object ** newTourn;
    newTourn = malloc((2*maxSize + 1)*sizeof(*newTourn));

    for (i = 1; i <= n; i++){
        newTourn[i] = tourn[i];
    }

    newTourn = tourn;
    maxSize = 2*maxSize;
}

void destroy(){
    free(tourn);
    free(Q);
}

void destroyObject(Object * a){
    free(a);
}

double value(int i){
    Object * a = tourn[i];
    return a->x0 + a->speed*getTime();
}

void swapTourn(int i, int j){
    Object * aux = tourn[i];
    tourn[i] = tourn[j];
    tourn[j] = aux;
    tourn[i]->lastMatch = i;
    tourn[j]->lastMatch = j;
}

/*
    printT(NULL, 1, 1, 0)
*/
void printT(char * prefix, int size, int j, int b){
	int i;
    char * newprefix;
    if(prefix == NULL){
        prefix = malloc(sizeof(*prefix));
        prefix[0] = '\0';
    }
    if(j < 2*n)
    {
        for(i = 0; prefix[i] != '\0'; i++)
            printf("%c", prefix[i]);

        if(b) 
            printf("├──"); 
        else 
            printf("└──" );
        printf("%d: %g*t + %g = %g, posicao: %d, lastMatch: %d\n", tourn[j]->id, tourn[j]->speed, tourn[j]->x0, value(j), j, tourn[j]->lastMatch);
		
        newprefix = malloc((size + 4)*sizeof(*newprefix));
        for(i = 0; i < size; i++)
            newprefix[i] = prefix[i];
        if(b)
            newprefix[size - 1] = '|';
        else
            newprefix[size - 1] = ' ';
        for(i = size; i < size + 4; i++)
            newprefix[i] = ' ';
        newprefix[size + 3] = '\0';
		printT(newprefix, size + 4, 2*j, 1);
        printT(newprefix, size + 4, 2*j + 1, 0);
        
    }
    if(!b)
        free(prefix);
}