#include "kds.h"

void sendPoint(Point * p){
    int i;
    initial[lastID++] = p;

    p->id = lastID - 1;
    for(i = 0; i < 7; i++)
        p->cert[i] = NULL;
    for(i = 0; i < 3; i++){
        p->cands[i] = NULL;
        p->hitsLow[i] = NULL;
        p->hitsUp[i] = NULL;
        p->lcand[i] = NULL;

        initS(p, CANDS_TREE, i);
        initS(p, HITS_LOW_TREE, i);
        initS(p, HITS_UP_TREE, i);

        p->lastMatch[i] = -1;
        /* */
        p->listPosition[i] = NULL;
        p->next[i] = NULL;
        p->prev[i] = NULL;
        listInsert(p, i);
    }
}

void initKDS(){
    initial = malloc((n + 1)*sizeof(*initial));
    lastID = 0;
    now = 0;
    listInit();
    initPQ();
    /* initTourn(n); */
    initTourn(3*n);
}

void buildKDS(){
    int i;
    initial[n] = initial[0];
    initial[0] = NULL;

    initMaxima(HORIZONTAL);
    initCandsHits(HORIZONTAL);
    for(i = 1; i <= n; i++)
        sendTourn(initial[i], HORIZONTAL);

    initMaxima(UP);
    initCandsHits(UP);
    for(i = 1; i <= n; i++)
        sendTourn(initial[i], UP);

    initMaxima(DOWN);
    initCandsHits(DOWN);
    for(i = 1; i <= n; i++)
        sendTourn(initial[i], DOWN);

    buildTourn();
    /* free(initial); */
}

double nextEvent(){
    return minPQ()->p->cert[minPQ()->certType]->value;
}

void advance(double t){
    if(t < now + EPS)
        printf("Time earlier than current time\n");

    while(t >= nextEvent() - EPS){
        now = nextEvent();
        event();
    }
    now = t;
}

void change(int j, Vector v){

}

void insert(Coordinate xt, Vector v){

}

void delete(int i){

}

void query(){
    TournObject * a = tourn[1];
    char name = (a->lcandp ? a->lcandp->name : '-');
    printf("Closest pair: %c -- %c: %g\n", a->p->name, name, distance(a->p, a->lcandp, a->direction));
}

void showInfo(){
    /* int i, j; */
    /* for (i = 0; i < 3; i++)
        printList(i); */
    printTourn();
    /* for(j = 0; j < 3; j++){
        for(i = 1; i <= n; i++){
            printPoint(initial[i], j);
            printf("\n");
        }
        printf("\n\n");
    } */
}

void test(){
    int i, j, x, y;
    double dmin = distance(initial[1], initial[2], HORIZONTAL);
    x = 1;
    y = 2;
    for(i = 1; i <= n; i++)
        for(j = i + 1; j <= n; j++){
            if(distance(initial[i], initial[j], HORIZONTAL) < dmin - EPS){
                x = i;
                y = j;
                dmin = distance(initial[i], initial[j], HORIZONTAL);
            }
        }

    printf("%c -- %c, distance: %.3lf\n", initial[x]->name, initial[y]->name, dmin);
}

void freeKDS(){
    free(initial);
}