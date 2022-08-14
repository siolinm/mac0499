#include"splay_tree.h"
#include"debug.h"

#define module(x) (x > 0 ? x : -x)
#define max(a, b) (a > b ? a : b)

void insertS(void * root, Point * a, int type, int dir){
    void * new;
    new = createNodeS(a, type, dir);
    insertSR(detach(root, type, dir), new, type, dir);
    splay(new, type, dir);
    attach(root, new, type, dir);
}

void deleteS(void * root, Point * a, int type, int dir){
    void * parent = NULL;

    if(type == HITS_UP_TREE && getKeyS(root, HITS_UP_TREE)->name == 'a' && dir == HORIZONTAL)
        printf("Deleting something from Hits_up(a)\n");


    deleteSR(detach(root, type, dir), a, &parent, type, dir);
    if(parent != NULL){
        splay(parent, type, dir);
        attach(root, parent, type, dir);
    }

    if(type == CANDS_TREE)
        a->cands[dir] = NULL;
    else if(type == HITS_LOW_TREE)
        a->hitsLow[dir] = NULL;
    else{
        a->hitsUp[dir] = NULL;
    }
}

void splay(void * x, int type, int dir){
    void * parent, *grandp;

    while(x && getParentS(x, type)){
        /*
            l or r case
        */
        parent = getParentS(x, type);
        grandp = getParentS(parent, type);
        if(!grandp){
            if(getLeftS(parent, type) == x)
                rotateRightS(parent, type, dir);
            else
                rotateLeftS(parent, type, dir);
        }
        else{
            if(getLeftS(parent, type) == x){
                /* rr case*/
                if(getLeftS(grandp, type) == parent){
                    rotateRightS(grandp, type, dir);
                    rotateRightS(parent, type, dir);
                }
                else{
                    /* rl case */
                    rotateRightS(parent, type, dir);
                    rotateLeftS(parent, type, dir);
                }
            }
            else{
                /* lr case */
                if(getLeftS(grandp, type) == parent){
                    rotateLeftS(parent, type, dir);
                    rotateRightS(parent, type, dir);
                }
                else{
                    /* ll case */
                    rotateLeftS(grandp, type, dir);
                    rotateLeftS(parent, type, dir);
                }
            }
        }
    }
}

void * splitL(void *root, int type, int dir){
    void * left;
    splay(root, type, dir);

    left = getLeftS(root, type);

    if(left){
        setLeftS(root, NULL, type);
        setParentS(left, NULL, type);
    }

    return left;
}

void * splitR(void * root, int type, int dir){
    void * right;
    splay(root, type, dir);

    right = getRightS(root, type);

    if(right){
        setRightS(root, NULL, type);
        setParentS(right, NULL, type);
    }

    return right;
}

void * joinS(void * rootS, void * rootT, int type, int dir){
    void * aux = rootS;

    if(aux == NULL)
        return rootT;

    while(getRightS(aux, type) != NULL){
        aux = getRightS(aux, type);
    }

    splay(aux, type, dir);

    setRightS(aux, rootT, type);
    if(rootT)
        setParentS(rootT, aux, type);

    if(type == CANDS_TREE)
        updateLeftmost(aux, dir);

    return aux;
}

void * successorS(void * root, Item * p, int type, int dir, int order){
    void *suc, *y, *x;
    int mirror = 0;
    int orientation;
    suc = y = NULL;
    x = getParentS(root, type);

    orientation = dir;

    if(type == CANDS_TREE && order == UP){
        mirror = 1;
    }
    if(dir == HORIZONTAL){
        if(order == UP)
            orientation = DOWN;
        else if(order == DOWN)
            orientation = UP;
    }
    else if(dir == UP){
        if(order == UP)
            orientation = HORIZONTAL;
        else if(order == DOWN)
            orientation = -DOWN;
    }
    else{ /* dir = DOWN */
        if(order == UP)
            orientation = -7;
        else if(order == DOWN)
            orientation = HORIZONTAL;
    }
    while(x != NULL){
        y = x;
        /* rounding errors */
        /* x(q) <= x(p) */
        if(leftTest(getKeyS(x, type), p, orientation)){
            if(!mirror)
                x = getRightS(x, type);
            else
                x = getLeftS(x, type);
        }
        else{
            suc = x;
            if(!mirror)
                x = getLeftS(x, type);
            else
                x = getRightS(x, type);
        }
    }

    if(y != NULL){
        detach(root, type, dir);
        splay(y, type, dir);
        attach(root, y, type, dir);
    }

    return suc;
}

void * predecessorS(void * root, Item * p, int type, int dir, int order){
    void *pred, *y, *x;
    int orientation;
    int mirror = 0;
    pred = y = NULL;
    x = getParentS(root, type);

    orientation = dir;

    if(type == CANDS_TREE && order == UP){
        mirror = 1;
    }
    if(dir == HORIZONTAL){
        if(order == UP)
            orientation = DOWN;
        else if(order == DOWN)
            orientation = UP;
    }
    else if(dir == UP){
        if(order == UP)
            orientation = HORIZONTAL;
        else if(order == DOWN)
            orientation = -DOWN;
    }
    else{ /* dir = DOWN */
        if(order == UP)
            orientation = -7;
        else if(order == DOWN)
            orientation = HORIZONTAL;
    }

    while(x != NULL){
        y = x;
        /* rounding errors */
        /* x(q) >= x(p) */
        if(leftTest(p, getKeyS(x, type), orientation)){
            if(!mirror)
                x = getLeftS(x, type);
            else
                x = getRightS(x, type);
        }
        else{
            pred = x;
            if(!mirror)
                x = getRightS(x, type);
            else
                x = getLeftS(x, type);
        }
    }

    if(y != NULL){
        detach(root, type, dir);
        splay(y, type, dir);
        attach(root, y, type, dir);
    }

    return pred;
}

Point * ownerS(void * root, int type, int dir){
    void * aux = root;

    if(aux && type == CANDS_TREE)
        updateLeftmost(aux, dir);

    while(aux && aux != getParentS(getParentS(aux, type), type)){
        if(type == CANDS_TREE)
            updateLeftmost(aux, dir);
        aux = getParentS(aux, type);
    }

    if(aux){
        aux = getParentS(aux, type);
        detach(aux, type, dir);
        splay(root, type, dir);
        attach(aux, root, type, dir);

        return getKeyS(aux, type);
    }

    return NULL;
}

/* ---------------------------------------------- */

void updateLeftmost(void * x, int dir){
    void * a, * b, *c, * left, * right;
    double vxa, vxb, aux;
    a = b = c = NULL;
    left = getLeftS(x, CANDS_TREE);
    right = getRightS(x, CANDS_TREE);
    if(left)
        a = getLeftmostS(left, CANDS_TREE);
    if(right)
        b = getLeftmostS(right, CANDS_TREE);

    if(a && b){
        if(getX(getKeyS(a, CANDS_TREE), dir) <
        getX(getKeyS(b, CANDS_TREE), dir))
            c = a;
        else if(getX(getKeyS(a, CANDS_TREE), dir) ==
        getX(getKeyS(b, CANDS_TREE), dir)){
            vxa = getVx(getKeyS(a, CANDS_TREE), dir);
            vxb = getVx(getKeyS(b, CANDS_TREE), dir);

            aux = max(module(vxa), module(vxb));

            vxa -= aux;
            vxb -= aux;

            if(vxa < vxb)
                c = a;
            else
                c = b;
        }
        else
            c = b;

    }
    else if(a){
        c = a;
    }
    else if(b){
        c = b;
    }

    setLeftmostS(x, x, CANDS_TREE);
    if(c && getX(getKeyS(c, CANDS_TREE), dir) <
        getX(getKeyS(x, CANDS_TREE), dir)){
        setLeftmostS(x, c, CANDS_TREE);
    }
    else if(c && getX(getKeyS(c, CANDS_TREE), dir) ==
    getX(getKeyS(x, CANDS_TREE), dir)){
        vxa = getVx(getKeyS(c, CANDS_TREE), dir);
        vxb = getVx(getKeyS(x, CANDS_TREE), dir);

        aux = max(module(vxa), module(vxb));

        vxa -= aux;
        vxb -= aux;

        if(vxa < vxb) setLeftmostS(x, c, CANDS_TREE);
    }
}

void rotateLeftS(void * x, int type, int dir){
    void * aux, *parent;

    parent = getParentS(x, type);
    aux = getRightS(x, type);

    if(!aux) return;

    setRightS(x, getLeftS(aux, type), type);
    if(getLeftS(aux, type))
        setParentS(getLeftS(aux, type), x, type);

    setLeftS(aux, x, type);
    setParentS(x, aux, type);
    setParentS(aux, parent, type);

    if(parent){
        if(getLeftS(parent, type) == x)
            setLeftS(parent, aux, type);
        else
            setRightS(parent, aux, type);
    }

    if(type == CANDS_TREE){
        updateLeftmost(x, dir);
        updateLeftmost(aux, dir);
    }
}

void rotateRightS(void * x, int type, int dir){
    void * aux, *parent;

    parent = getParentS(x, type);
    aux = getLeftS(x, type);

    if(!aux) return;

    setLeftS(x, getRightS(aux, type), type);
    if(getRightS(aux, type))
        setParentS(getRightS(aux, type), x, type);

    setRightS(aux, x, type);
    setParentS(x, aux, type);
    setParentS(aux, parent, type);

    if(parent){
        if(getLeftS(parent, type) == x)
            setLeftS(parent, aux, type);
        else
            setRightS(parent, aux, type);
    }

    if(type == CANDS_TREE){
        updateLeftmost(x, dir);
        updateLeftmost(aux, dir);
    }
}

void initS(Point * p, int type, int dir){
    void * new;
    if(type == CANDS_TREE){
        new = (void *)malloc(sizeof(CandsNode));
        setLeftmostS(new, new, type);
    }
    else{
        new = (void *)malloc(sizeof(HitsNode));
    }

    setLeftS(new, NULL, type);
    setRightS(new, NULL, type);
    setParentS(new, NULL, type);
    setKeyS(new, p, type);

    if(type == CANDS_TREE){
        p->candsRoot[dir] = new;
    }
    else if(type == HITS_UP_TREE){
        p->hitsUpRoot[dir] = new;
    }
    else if(type == HITS_LOW_TREE){
        p->hitsLowRoot[dir] = new;
    }

}

void * createNodeS(Point * key, int type, int dir){
    void * new;
    if(type == CANDS_TREE){
        new = (void *)malloc(sizeof(CandsNode));
        setLeftmostS(new, new, type);
    }
    else{
        new = (void *)malloc(sizeof(HitsNode));
    }
    setLeftS(new, NULL, type);
    setRightS(new, NULL, type);
    setParentS(new, NULL, type);
    setKeyS(new, key, type);

    if(type == CANDS_TREE){
        key->cands[dir] = (CandsNode *)new;
    }
    else if(type == HITS_UP_TREE){
        key->hitsUp[dir] = (HitsNode *)new;
    }
    else if(type == HITS_LOW_TREE){
        key->hitsLow[dir] = (HitsNode *)new;
    }

    return new;
}

void * insertSR(void * root, void * node, int type, int dir){
    void * sub;
    if(!root)
        return node;

    if(compareS(getKeyS(root, type), getKeyS(node, type), type, dir)){
        sub = insertSR(getLeftS(root, type), node, type, dir);
        setLeftS(root, sub, type);
        setParentS(sub, root, type);
    }
    else{
        sub = insertSR(getRightS(root, type), node, type, dir);
        setRightS(root, sub, type);
        setParentS(sub, root, type);
    }

    if(type == CANDS_TREE)
        updateLeftmost(root, dir);

    // printf("Returning root\n");
    return root;
}

void * extractS(void * root, void * low, void * up, int type, int dir){
    void * r = NULL;
    r = detach(root, type, dir);
    if(low != NULL){
        splay(low, type, dir);

        r = splitR(low, type, dir);

        if(type == CANDS_TREE)
            updateLeftmost(low, dir);
        if(!up)
            attach(root, low, type, dir);
    }

    if(up != NULL){
        splay(up, type, dir);

        r = splitL(up, type, dir);

        if(type == CANDS_TREE)
            updateLeftmost(up, dir);
        attach(root, up, type, dir);
    }

    if(up != NULL && low != NULL){
        detach(root, type, dir);
        attach(root, joinS(low, up, type, dir), type, dir);

        if(type == CANDS_TREE)
            updateLeftmost(low, dir);

    }



    return r;
}

void * deleteSR(void * root, Point * a, void **parent, int type, int dir){
    void * aux = root;

    if(root == NULL){
        printf("Point is not in this three\n");
        return NULL;
    }

    if(getKeyS(root, type) == a){
        if(getLeftS(root, type) && getRightS(root, type)){
            aux = getRightS(root, type);
            while(getLeftS(aux, type) != NULL){
                aux = getLeftS(aux, type);
            }
            swapS(root, aux, type, dir);
            setRightS(root, deleteSR(getRightS(root, type), a,
            parent, type, dir), type);
        }
        else{
            *parent = getParentS(root, type);
            aux = (getLeftS(root, type) ? getLeftS(root, type)
            : getRightS(root, type));

            if(aux) setParentS(aux, *parent, type);

            if(*parent == NULL) *parent = aux;

            if(getParentS(root, type)){
                if(getLeftS(getParentS(root, type), type) == root)
                    setLeftS(getParentS(root, type), aux, type);
                else
                    setRightS(getParentS(root, type), aux, type);
            }

            if(type == CANDS_TREE)
                a->cands[dir] = NULL;
            else if(type == HITS_UP_TREE)
                a->hitsUp[dir] = NULL;
            else if(type == HITS_LOW_TREE)
                a->hitsLow[dir] = NULL;

            free(root);

            root = aux;
        }
    }
    else if(compareS(getKeyS(root, type), a, type, dir)){
        setLeftS(root, deleteSR(getLeftS(root, type), a,
        parent, type, dir), type);
        if(getLeftS(root, type))
            setParentS(getLeftS(root, type), root, type);
    }
    else{
        setRightS(root, deleteSR(getRightS(root, type), a,
        parent, type, dir), type);
        if(getRightS(root, type))
            setParentS(getRightS(root, type), root, type);
    }

    if(root && type == CANDS_TREE){
        updateLeftmost(root, dir);
    }

    return root;
}

int compareS(Point * a, Point * b, int type, int dir){
    if(type == CANDS_TREE){
        return getY(a, dir) > getY(b, dir) + EPS;
    }

    // if(mod(getX(a, dir) - getX(b, dir)) < EPS){
    //     vxa = getVx(a, dir);
    //     vxb = getVx(b, dir);

    //     aux = max(mod(vxa), mod(vxb));

    //     vxa -= aux;
    //     vxb -= aux;

    //     if(mod(vxa - vxb) < EPS)
    //         return getY(a, dir) < getY(b, dir) - EPS;

    //     return vxa > vxb + EPS;
    // }

    // return getX(a, dir) > getX(b, dir) + EPS;
    return left(b, a, dir);
}

void swapS(void * roota, void * rootb, int type, int dir){
    Point * p, * q;
    /* void * aux; */
    p = getKeyS(roota, type);
    q = getKeyS(rootb, type);
    if(type == HITS_UP_TREE){
        p->hitsUp[dir] = (HitsNode *)rootb;
        q->hitsUp[dir] = (HitsNode *)roota;
    }
    else if(type == HITS_LOW_TREE){
        p->hitsLow[dir] = (HitsNode *)rootb;
        q->hitsLow[dir] = (HitsNode *)roota;
    }
    else{
        p->cands[dir] = (CandsNode *)rootb;
        q->cands[dir] = (CandsNode *)roota;
    }
    setKeyS(roota, q, type);
    setKeyS(rootb, p, type);
    /* aux = getLeftS(roota, type);
    setLeftS(roota, getLeftS(rootb, type), type);
    setLeftS(rootb, aux, type);

    aux = getRightS(roota, type);
    setRightS(roota, getRightS(rootb, type), type);
    setRightS(rootb, aux, type);

    aux = getParentS(roota, type);
    if(aux){
        if(roota == getLeftS(aux, type))
            setLeftS(aux, rootb, type);
        else
            setRightS(aux, rootb, type);
    }
    if(getParentS(rootb, type)){
        if(rootb == getLeftS(getParentS(rootb, type), type))
            setLeftS(getParentS(rootb, type), roota, type);
        else
            setRightS(getParentS(rootb, type), roota, type);
    }
    setParentS(roota, getParentS(rootb, type), type);
    setParentS(rootb, aux, type); */

    if(type == CANDS_TREE){
        updateLeftmost(roota, dir);
        updateLeftmost(rootb, dir);
    }
}

void * detach(void * root, int type, int dir){
    void * aux;

    if(!root) return root;

    aux = getParentS(root, type);
    if(aux)
        setParentS(aux, NULL, type);
    setParentS(root, NULL, type);
    return aux;
}

void attach(void * roota, void * rootb, int type, int dir){
    setParentS(roota, rootb, type);
    if(rootb) setParentS(rootb, roota, type);
}

void freeAllS(void * root, int type, int dir){
    Point * p;
    if(root){
        freeAllS(getLeftS(root, type), type, dir);
        freeAllS(getRightS(root, type), type, dir);
        p = getKeyS(root, type);
        if(p != NULL){
            if(type == CANDS_TREE){
                p->cands[dir] = NULL;
            }
            else if(type == HITS_UP_TREE){
                p->hitsUp[dir] = NULL;
            }
            else{
                p->hitsLow[dir] = NULL;
            }
        }
        free(root);
    }
}

void setLeftS(void * x, void * y, int type){
    if(type == CANDS_TREE){
        ((CandsNode * )x)->left = (CandsNode *)y;
    }
    else{
        ((HitsNode * )x)->left = (HitsNode *)y;
    }
}

void setRightS(void * x, void * y, int type){
    if(type == CANDS_TREE){
        ((CandsNode * )x)->right = (CandsNode *)y;
    }
    else{
        ((HitsNode * )x)->right = (HitsNode *)y;
    }
}

void setParentS(void * x, void * y, int type){
    if(type == CANDS_TREE){
        ((CandsNode * )x)->parent = (CandsNode *)y;
    }
    else{
        ((HitsNode * )x)->parent = (HitsNode *)y;
    }
}

void setKeyS(void * x, Point * y, int type){
    if(type == CANDS_TREE){
        ((CandsNode * )x)->key = y;
    }
    else{
        ((HitsNode * )x)->key = y;
    }
}

void setLeftmostS(void * x, void * y, int type){
    ((CandsNode * )x)->leftmost = (CandsNode *)y;
}

void * getLeftS(void * x, int type){
    if(type == CANDS_TREE){
        return (void *)((CandsNode * )x)->left;
    }
    else{
        return (void *)((HitsNode * )x)->left;
    }
}

void * getRightS(void * x, int type){
    if(type == CANDS_TREE){
        return (void *)((CandsNode * )x)->right;
    }
    else{
        return (void *)((HitsNode * )x)->right;
    }
}

void * getParentS(void * x, int type){
    if(type == CANDS_TREE){
        return (void *)((CandsNode * )x)->parent;
    }
    else{
        return (void *)((HitsNode * )x)->parent;
    }
}

Point * getKeyS(void * x, int type){
    if(type == CANDS_TREE){
        return ((CandsNode *)x)->key;
    }

    return ((HitsNode *)x)->key;
}

void * getLeftmostS(void * x, int type){
    return (void *)((CandsNode * )x)->leftmost;
}

void printS(void * root, int type){
    printSR(getParentS(root, type), NULL, type, 1, 0);
}

void printSR(void * root, char * prefix, int type, int size, int b){
    int i;
    char * newprefix;
    Point * key;
    if(prefix == NULL){
        prefix = malloc(sizeof(*prefix));
        prefix[0] = '\0';
    }
    if(root != NULL)
    {
        for(i = 0; prefix[i] != '\0'; i++)
            printf("%c", prefix[i]);

        if(b)
            printf("├──");
        else
            printf("└──");
        key = getKeyS(root, type);
        printf("%c: (%g, %g) + t*(%g, %g)", key->name, key->x0.x, key->x0.y, key->speed.x, key->speed.y);

        if(type == CANDS_TREE){
            printf(", leftmost: %c", ((CandsNode *)getLeftmostS(root, type))->key->name);
        }
        printf("\n");

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
		printSR(getLeftS(root, type), newprefix, type, size + 4, 1);
        printSR(getRightS(root, type), newprefix, type, size + 4, 0);
    }
    else{
        printf("%s", prefix);
        if(b)
            printf("├── NULL\n");
        else
            printf("└── NULL\n");
    }
    if(!b)
        free(prefix);
}