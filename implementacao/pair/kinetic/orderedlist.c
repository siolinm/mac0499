#include "orderedlist.h"
/*
    https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
    https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
    https://www.youtube.com/watch?v=YkF76cOgtMQ&list=PLxI8Can9yAHf8k8LrUePyj0y3lLpigGcl&index=21
    https://www.youtube.com/watch?v=FzS0n_Z8lrk
*/

#define max(a, b) (a > b ? a : b)

void listInit(){
    int i;

    for(i = 0; i < 3; i++)
        listRoot[i] = NULL;
}

void listInsert(Point * a, int dir){

    listRoot[dir] = insertAVLNode(listRoot[dir], a, dir);

    newCertList(a, dir);
    updateListCert(a->next[dir], dir);
}

void listDelete(Point * a, int dir){
    Point * next;
    int i;

    i = certType(dir);
    next = a->next[dir];

    listRoot[dir] = deleteAVLNode(listRoot[dir], a, dir);

    deletePQ(a, i);
    updateListCert(next, dir);
}

void listSwap(Point * p, Point * q, int dir){
    /* swap list nodes */
    AVLNode * aux;
    aux = p->listPosition[dir];
    p->listPosition[dir] = q->listPosition[dir];
    p->listPosition[dir]->key = p;
    q->listPosition[dir] = aux;
    q->listPosition[dir]->key = q;

    /* swap linked list positions */
    p->prev[dir] = q->prev[dir];
    if(p->prev[dir])
        p->prev[dir]->next[dir] = p;

    q->next[dir] = p->next[dir];
    if(q->next[dir])
        q->next[dir]->prev[dir] = q;

    p->next[dir] = q;
    q->prev[dir] = p;
}

double expireList(Point *a, Point * b, int dir){
    double aspeed, bspeed;
    if(b == NULL)
        return INFINITE;

    aspeed = getVx(a, dir);
    bspeed = getVx(b, dir);

    if(mod(aspeed - bspeed) < EPS && mod(getX0(a, dir) - getX0(b, dir)) < EPS){
        aspeed = getVy(a, dir);
        bspeed = getVy(b, dir);
        if(aspeed < bspeed - EPS)
            return INFINITE;
        return (getY0(b, dir) - getY0(a, dir))/(aspeed - bspeed);
    }

    if(aspeed - bspeed > -EPS)
        return INFINITE;

    return (getX0(a, dir) - getX0(b, dir))/(bspeed - aspeed);
}

void newCertList(Point *p, int dir){
    Cert *cert;
    int type;

    if(p == NULL) return;

    cert = malloc(sizeof(*cert));
    cert->priority = 0.0;
    type = certType(dir);

    p->cert[type] = cert;
    p->cert[type]->value = expireList(p, p->prev[dir], dir);

    insertPQ(p, type);
    updateListCert(p, dir);
}

void updateListCert(Point * p, int dir){
    int type;
    Point * q;
    double time, dx, dy;
    double prio = 0.0;
    if(p == NULL) return;

    q = p->prev[dir];
    time = expireList(p, q, dir);
    if(q != NULL){
        dx = getX0(p, dir) + time*getVx(p, dir) - (getX0(q, dir) + time*getVx(q, dir));
        dy = getY0(p, dir) + time*getVy(p, dir) - (getY0(q, dir) + time*getVy(q, dir));
        if(sqrt(dx*dx + dy*dy) < EPS){
            /* colisao */
            prio = getCertPriority(p, q, dir);
        }
    }
    type = certType(dir);
    p->cert[type]->priority = prio;
    updatePQ(p, type, time);
}

int height(AVLNode *a)
{
    return (a ? a->height : -1);
}

void setHeight(AVLNode *a)
{
    a->height = max(height(a->left), height(a->right)) + 1;
}

AVLNode *newAVLNode(Object *key, int dir)
{
    AVLNode *new = (AVLNode *)malloc(sizeof(AVLNode));

    new->left = NULL;
    new->right = NULL;
    new->key = key;
    new->height = 1;
    new->children = 0;
    key->listPosition[dir] = new;

    return new;
}

AVLNode *rotateRight(AVLNode *no)
{
    AVLNode *leftChild, *aux;

    leftChild = no->left;
    if (!leftChild)
        return no;
    aux = leftChild->right;

    leftChild->right = no;
    no->left = aux;

    leftChild->children += no->children + 1;

    setHeight(no);
    setHeight(leftChild);

    return leftChild;
}

AVLNode *rotateLeft(AVLNode *no)
{
    AVLNode *rightChild, *aux;

    rightChild = no->right;
    if (!rightChild)
        return no;
    aux = rightChild->left;

    rightChild->left = no;
    no->right = aux;

    no->children -= rightChild->children + 1;

    setHeight(no);
    setHeight(rightChild);

    return rightChild;
}

int getBalance(AVLNode *no){
    return (no ? (height(no->left) - height(no->right)) : 0);
}

int AVLCompare(Object * a, Object * b, int dir){
    /* x(t) */
    // double x, y, vxa, vxb, aux;
    // x = getX(a, dir);
    // y = getX(b, dir);
    // if(mod(x - y) < EPS){/* x = y */
    //     vxa = getVx(a, dir);
    //     vxb = getVx(b, dir);
    //     aux = max(mod(vxa), mod(vxb));
    //     vxa -= aux;
    //     vxb -= aux;
    //     printf("%.8lf\n", mod(vxa - vxb));
    //     if(mod(vxa - vxb) < EPS){
    //         // if they've the same x-speed use y-coordinate
    //         return getY(a, dir) > getY(b, dir) + EPS;
    //     }
    //     return vxa < vxb - EPS;
    // }
    // return x - y < -EPS;
    return left(a, b, dir);
}

AVLNode *insertAVLNode(AVLNode *r, Object *key, int dir)
{
    int a;
    if (!r)
        return newAVLNode(key, dir);

    if (AVLCompare(key, r->key, dir)){
        r->left = insertAVLNode(r->left, key, dir);
    }
    else{
        r->children += 1;
        r->right = insertAVLNode(r->right, key, dir);
    }

    if(key->prev[dir] == NULL && !AVLCompare(key, r->key, dir)){
        key->prev[dir] = r->key;
        key->next[dir] = r->key->next[dir];
        if(key->next[dir])
            key->next[dir]->prev[dir] = key;
        r->key->next[dir] = key;
    }
    else if(key->next[dir] == NULL && AVLCompare(key, r->key, dir)){
        key->next[dir] = r->key;
        key->prev[dir] = r->key->prev[dir];
        if(key->prev[dir])
            key->prev[dir]->next[dir] = key;
        r->key->prev[dir] = key;
    }

    setHeight(r);

    a = getBalance(r);

    if (a > 1 && key < r->left->key)
        return rotateRight(r);

    if (a > 1 && key > r->left->key)
    {
        r->left = rotateLeft(r->left);
        return rotateRight(r);
    }


    if (a < -1 && key > r->right->key)
        return rotateLeft(r);

    if (a < -1 && key < r->right->key)
    {
        r->right = rotateRight(r->right);
        return rotateLeft(r);
    }

    return r;
}

AVLNode *leftmost(AVLNode *r)
{
    while (r->left)
        r = r->left;

    return r;
}

AVLNode *deleteAVLNode(AVLNode *r, Object *key, int dir)
{
    AVLNode *aux;
    int a;

    if (r == NULL)
        return r;

    if (key == r->key)
    {
        if(key->prev[dir])
            key->prev[dir]->next[dir] = key->next[dir];
        if(key->next[dir])
            key->next[dir]->prev[dir] = key->prev[dir];
        if (r->left && r->right)
        {
            aux = leftmost(r->right);
            r->key = aux->key;
            r->key->listPosition[dir] = r;
            r->right = deleteAVLNode(r->right, r->key, dir);
            r->children -= 1;
        }
        else
        {
            aux = r;
            r = (r->left ? r->left : r->right);
            free(aux);
        }
    }
    else if (AVLCompare(key, r->key, dir))
    {
        r->left = deleteAVLNode(r->left, key, dir);
    }
    else
    {
        r->right = deleteAVLNode(r->right, key, dir);
        r->children -= 1;
    }

    if(r == NULL)
        return r;

    a = getBalance(r);

    if (a > 1 && getBalance(r->left) >= 0){
        return rotateRight(r);
    }
    else if (a > 1)
    {
        r->left = rotateLeft(r->left);
        return rotateRight(r);
    }
    else if (a < -1 && getBalance(r->right) <= 0){
        return rotateLeft(r);
    }
    else if(a < -1)
    {
        r->right = rotateRight(r->right);
        return rotateLeft(r);
    }

    return r;
}

Object * query_kth(AVLNode *r, int i){
    if(r->children == i - 1)
        return r->key;

    if(r->children < i)
        return query_kth(r->left, i - r->children - 1);

    return query_kth(r->right, i);
}

void printListR(AVLNode * r, int dir){
    if(r != NULL){
        printListR(r->left, dir);
        printf(" -- %c", r->key->name);
        // printf(" - %g - %c", r->key->cert[certType(dir)]->value, r->key->name);
        printListR(r->right, dir);
    }
}

void printList(int dir){
    printf("NULL");
    printListR(listRoot[dir], dir);
    printf(" -- NULL");
    printf("\n");
}


/*
void print(char * prefix, int size, AVLNode * r, int b){
	int i;
    char * newprefix;
    if(prefix == NULL){
        prefix = malloc(sizeof(*prefix));
        prefix[0] = '\0';
    }
    if(r != NULL)
    {
        for(i = 0; prefix[i] != '\0'; i++)
            printf("%c", prefix[i]);

        if(b)
            printf("├──");
        else
            printf("└──" );
        printf("%d: %g*t + %g = %g\n", r->key->id, r->key->speed, r->key->initv, value(r->key));

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
		print(newprefix, size + 4, r->left, 1);
        print(newprefix, size + 4, r->right, 0);

    }
    if(!b)
        free(prefix);
}
*/
/*
void printL(){
    AVLNode * aux;
    Object * obj, * lobj;
    aux = leftmost(r);
    obj = aux->key;
    while(obj != NULL){
        printf("%d: %g*t + %g = %g", obj->id, obj->speed, obj->initv, value(obj));
        printf("%d: %g", obj->id, value(obj));
        printf("%d", obj->id);
        if(obj->next)
            printf(" --> ");
        else{
            lobj = obj;
            printf("\n");
        }
        obj = obj->next;
    }
    obj = lobj;
    while(obj != NULL){
        printf("%d", obj->id);
        if(obj->prev)
            printf(" (%gs)--> ", obj->certificate);
        else{
            lobj = obj;
            printf("\n");
        }
        obj = obj->prev;
    }
}
*/

void removeAll(AVLNode * r){
    if(!r)
        return;
    removeAll(r->left);
    removeAll(r->right);
    free(r);
}