#include"event.h"
#include"orderedlist.h"
#include"tourn.h"

#include"splay_tree.h"
#include"draw.h"
#include<stdio.h>

#define module(x) (x > 0 ? x : -x)
#define max(a, b) (a > b ? a : b)

void tournEvent(){
    PQObject * aux = minPQ();
    int dir, j, k;
    dir = aux->certType - TOURN_CERT;

    j = aux->p->lastMatch[dir];
    k = 2*(j/2) + !(j % 2);

    tourn[j/2] = tourn[j];
    dir = tourn[k]->direction;
    tourn[k]->p->lastMatch[dir] = k;
    updateTournCert(tourn[k]);

    j = j/2;
    k = 2*(j/2) + !(j % 2);

    while(j > 1 && compareTourn(j, k)){
        tourn[j/2] = tourn[j];
        dir = tourn[k]->direction;
        tourn[k]->p->lastMatch[dir] = k;
        updateTournCert(tourn[k]);

        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }

    dir = tourn[j]->direction;
    tourn[j]->p->lastMatch[dir] = j;
    updateTournCert(tourn[j]);
}

void listEvent(Point * p, int eventType){
    int dir, skip = 1;
    double prio;
    Point * auxp, *q;
    char text[100];

    q = p->prev[getDirection(eventType)];
    auxp = p;
    prio = p->cert[eventType]->priority;
    theta = prio;

    dir = HORIZONTAL;
    sprintf(text, "Event between %c and %c", p->name, q->name);
    drawEvent(p, q, NULL, NULL, 0, dir, text, -1, &skip);

    if(eventType == HORIZONTAL_CERT){
        /* q must be above p */
        if(getY(p, HORIZONTAL) > EPS + getY(q, HORIZONTAL)){ /* Y(p) > Y(q) */
            p = q;
            q = auxp;
        }
        else if(mod(getY(p, HORIZONTAL) - getY(q, HORIZONTAL)) < EPS){
            p = q;
            q = auxp;
        }

        horizontalEvent(p, q, HORIZONTAL);
        downEvent(p, q, UP);
        upEvent(q, p, DOWN);
    }
    else if(eventType == UP_CERT){
        /* p must be to the left of q */

        if(leftTest(q, p, HORIZONTAL)){
            p = q;
            q = auxp;
        }

        upEvent(p, q, HORIZONTAL);
        horizontalEvent(q, p, UP);
        downEvent(p, q, DOWN);
    }
    else if(eventType == DOWN_CERT){
        if(leftTest(q, p, HORIZONTAL)){
            p = q;
            q = auxp;
        }

        downEvent(p, q, HORIZONTAL);
        upEvent(p, q, UP);
        horizontalEvent(p, q, DOWN);
    }

    dir = getDirection(eventType);
    p = auxp;
    q = p->prev[dir];
    listSwap(p, q, dir);

    p = p->next[dir];
    updateListCert(p, dir);
    updateListCert(p->prev[dir], dir);
    updateListCert(p->next[dir], dir);
}

/* horizontal-order event */
void horizontalEvent(Point * p, Point * q, int dir){
    Point * t, *w, *v;
    CandsNode * up, *newCands, *low;
    double vxp, vxq, aux;
    int change;
    if(q == ownerS(p->hitsUp[dir], HITS_UP_TREE, dir)){ /* p is in HitsUp(q) */
        t = NULL;
        up = (CandsNode *)predecessorS(q->candsRoot[dir], p, CANDS_TREE, dir, UP);
        if(up != NULL)
            t = up->key;
        else
            t = ownerS(q->hitsUp[dir], HITS_UP_TREE, dir);

        newCands = extractS(q->candsRoot[dir], NULL, up, CANDS_TREE, dir);

        change = updateLcand(q, dir);
        if(change) updateTourn(q, dir);

        newCands = joinS(detach(p->candsRoot[dir], CANDS_TREE, dir), newCands, CANDS_TREE, dir);

        attach(p->candsRoot[dir], newCands, CANDS_TREE, dir);
        /* check if some lcand changed */

        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);

        /* delete p from HitsUp(q) */
        deleteS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

        /* insert p in HitsUp(t) (if t != NULL)*/
        if(t != NULL){

            insertS(t->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

        }

        w = ownerS(q->hitsLow[dir], HITS_LOW_TREE, dir);

        if(w != NULL){

            deleteS(w->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);
        }

        insertS(p->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);
    }
    else if(p == ownerS(q->hitsLow[dir], HITS_LOW_TREE, dir)){ /* q is in HitsLow(p) */
        /* searching for low(q) in Cands(p) */
        low = (CandsNode *)predecessorS(p->candsRoot[dir], q, CANDS_TREE, dir, DOWN);
        if(low != NULL)
            t = low->key;
        else
            t = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);


        newCands = extractS(p->candsRoot[dir], low, NULL, CANDS_TREE, dir);

        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);

        newCands = joinS(detach(q->candsRoot[dir], CANDS_TREE, dir), newCands, CANDS_TREE, dir);

        attach(q->candsRoot[dir], newCands, CANDS_TREE, dir);
        /* check if some lcand changed */
        change = updateLcand(q, dir);
        if(change) updateTourn(q, dir);

        deleteS(p->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);

        if(t != NULL){

            insertS(t->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);
        }

        w = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);

        if(w != NULL){

            deleteS(w->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

        }

        insertS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
    }

    vxp = getVx(p, dir);
    vxq = getVx(q, dir);

    aux = max(module(vxp), module(vxq));

    vxp -= aux;
    vxq -= aux;

    if(vxp < vxq - EPS) /* p is to the left */
        v = ownerS(p->cands[dir], CANDS_TREE, dir);
    else /* q is to the left */
        v = ownerS(q->cands[dir], CANDS_TREE, dir);

    if(v != NULL){
        if(change) updateTourn(v, dir);
    }
}

/* +60-order event */
void upEvent(Point * p, Point * q, int dir){
    HitsNode * auxh, *newHits;
    Point * v, *t;
    int change;
    if(q == ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir)){ /* p is in HitsLow(q) */
        v = ownerS(q->cands[dir], CANDS_TREE, dir); /* search for q in Cands(v) */
        if(v != NULL){

            deleteS(v->candsRoot[dir], q, CANDS_TREE, dir);

            /* check if some lcand changed */
            change = updateLcand(v, dir);
            if(change) updateTourn(v, dir);
        }

        /* check if some lcand changed */

        insertS(p->candsRoot[dir], q, CANDS_TREE, dir);

        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);

        auxh = (HitsNode *)successorS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir, HORIZONTAL);
        if(auxh != NULL)
            t = auxh->key;
        else
            t = ownerS(q->hitsLow[dir], HITS_LOW_TREE, dir);

        newHits = extractS(q->hitsUpRoot[dir], NULL, auxh, HITS_UP_TREE, dir);

        newHits = joinS(detach(p->hitsUpRoot[dir], HITS_UP_TREE, dir), newHits, HITS_UP_TREE, dir);
        attach(p->hitsUpRoot[dir], newHits, HITS_UP_TREE, dir);

        /* remove p from Hits_low(q) */
        deleteS(q->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);

        if(t != NULL){
            insertS(t->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);
        }

    }
    else if(p == ownerS(q->cands[dir], CANDS_TREE, dir)){ /* q is in Cands(p) */

        t = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);

        if(t != NULL){
            deleteS(t->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);
        }

        insertS(q->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);

        auxh = (HitsNode *)predecessorS(p->hitsUpRoot[dir], q, HITS_UP_TREE, dir, UP);

        if(auxh != NULL)
            v = auxh->key;
        else
            v = ownerS(p->cands[dir], CANDS_TREE, dir);

        newHits = extractS(p->hitsUpRoot[dir], auxh, NULL, HITS_UP_TREE, dir);
        newHits = joinS(newHits, detach(q->hitsUpRoot[dir], HITS_UP_TREE, dir), HITS_UP_TREE, dir);
        attach(q->hitsUpRoot[dir], newHits, HITS_UP_TREE, dir);

        deleteS(p->candsRoot[dir], q, CANDS_TREE, dir);

        /* check if some lcand changed */
        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);
        if(v != NULL){
            insertS(v->candsRoot[dir], q, CANDS_TREE, dir);
            /* check if some lcand changed */
            change = updateLcand(v, dir);
            if(change) updateTourn(v, dir);
        }
    }
}

/* -60-order event */
void downEvent(Point * p, Point * q, int dir){
    HitsNode * auxh, *newHits;
    Point * v, *t;
    int change;

    if(q == ownerS(p->hitsUp[dir], HITS_UP_TREE, dir)){ /* p is in HitsUp(q) */
        v = ownerS(q->cands[dir], CANDS_TREE, dir); /* search for q in Cands(v) */
        if(v != NULL){

            deleteS(v->candsRoot[dir], q, CANDS_TREE, dir);

            /* check if some lcand changed */
            change = updateLcand(v, dir);
            if(change) updateTourn(v, dir);
        }

        insertS(p->candsRoot[dir], q, CANDS_TREE, dir);
        /* check if some lcand changed */
        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);

        auxh = (HitsNode *)successorS(q->hitsLowRoot[dir], p, HITS_LOW_TREE, dir, HORIZONTAL);

        if(auxh != NULL)
            t = auxh->key;
        else
            t = ownerS(q->hitsUp[dir], HITS_UP_TREE, dir);

        newHits = extractS(q->hitsLowRoot[dir], NULL, auxh, HITS_LOW_TREE, dir);
        newHits = joinS(detach(p->hitsLowRoot[dir], HITS_LOW_TREE, dir), newHits, HITS_LOW_TREE, dir);
        attach(p->hitsLowRoot[dir], newHits, HITS_LOW_TREE, dir);

        /* remove p from Hits_low(q) */
        deleteS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);


        if(t != NULL){
            insertS(t->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
        }
    }
    else if(p == ownerS(q->cands[dir], CANDS_TREE, dir)){ /* q is in Cands(p) */
        t = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);

        if(t != NULL){
            deleteS(t->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
        }
        insertS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

        auxh = (HitsNode *)predecessorS(p->hitsLowRoot[dir], q, HITS_LOW_TREE, dir, DOWN);

        if(auxh != NULL)
            v = auxh->key;
        else
            v = ownerS(p->cands[dir], CANDS_TREE, dir);

        newHits = extractS(p->hitsLowRoot[dir], auxh, NULL, HITS_LOW_TREE, dir);
        newHits = joinS(newHits, detach(q->hitsLowRoot[dir], HITS_LOW_TREE, dir), HITS_LOW_TREE, dir);
        attach(q->hitsLowRoot[dir], newHits, HITS_LOW_TREE, dir);

        deleteS(p->candsRoot[dir], q, CANDS_TREE, dir);


        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);
        if(v != NULL){

            insertS(v->candsRoot[dir], q, CANDS_TREE, dir);

            change = updateLcand(v, dir);
            if(change) updateTourn(v, dir);
        }
    }

}

/*
    The first certificate in the PQ has expired
*/
void event(){
    PQObject *aux;
    while(mod(valuePQ(1) - now) <= EPS){
        aux = minPQ();
        if(aux->certType >= TOURN_CERT){
            tournEvent();
        }
        else{
            listEvent(aux->p, aux->certType);
        }
    }
}