#include"maxima.h"
#include"debug.h"

void initMaxima(int dir){
    maximaRoot = malloc(sizeof(*maximaRoot));
    maximaRoot->parent = NULL;
    maximaRoot->key = NULL;
    maximaRoot->left = maximaRoot->right = NULL;
    maximaRoot->leftmost = NULL;
}

void initCandsHits(int dir){
    int i;
    CandsNode * up, * low, *aux;
    Point * p;

    initMaxima(dir);
    heapsort(initial, dir);

    for(i = 1; i <= n; i++){
        p = initial[i];
        low = predecessorS(maximaRoot, p, CANDS_TREE, dir, DOWN);
        up = predecessorS(maximaRoot, p, CANDS_TREE, dir, UP);

        /* inserts up(p) in HitsUp(p) */
        if(up) insertS(up->key->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
        /* inserts low(p) in HitsLow(p) */
        if(low) insertS(low->key->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);
        /* stores Cands(p) */
        aux = (CandsNode *)extractS(maximaRoot, low, up, CANDS_TREE, dir);
        attach(p->candsRoot[dir], aux, CANDS_TREE, dir);
        insertS(maximaRoot, p, CANDS_TREE, dir);

        updateLcand(p, dir);

    }

    freeAllS(getParentS(maximaRoot, CANDS_TREE), CANDS_TREE, dir);
    free(maximaRoot);
}