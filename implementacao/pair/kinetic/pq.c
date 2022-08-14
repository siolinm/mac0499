#include"pq.h"

#define pqpos(obj) obj->p->cert[obj->certType]->pqpos

void initPQ(){
    /* 3n from lists + 3n from tourn */
    pqMaxSize = 6*n;
    Q = malloc(pqMaxSize*sizeof(*Q));
    pqSize = 0;
}

int comparePQ(PQObject * a, PQObject * b){
    double ta, tb;
    Point * pa = a->p;
    Point * pb = b->p;
    Cert * ca, *cb;

    ca = pa->cert[a->certType];
    cb = pb->cert[b->certType];
    ta = valuePQObject(a);
    tb = valuePQObject(b);
    if(mod(ta - tb) < EPS && ta < INFINITE){
        if(a->certType >= TOURN_CERT)
            return 0;
        else if(b->certType >= TOURN_CERT)
            return 1;
        return ca->priority < cb->priority;
    }

    return valuePQObject(a) < valuePQObject(b);
}

void resizePQ(){
    int i;
    if(pqSize + 1 == pqMaxSize){
        PQObject ** W = malloc(2*pqMaxSize*sizeof(*W));

        for(i = 1; i <= pqSize; i++)
            W[i] = Q[i];

        free(Q);
        Q = W;
        pqMaxSize = 2*pqMaxSize;
    }
}

void insertPQ(Point * p, int certType){
    PQObject * pq;
    resizePQ();

    pq = malloc(sizeof(*pq));
    pq->p = p;
    pq->certType = certType;

    Q[++pqSize] = pq;
    pqpos(pq) = pqSize;

    updatePQ(pq->p, pq->certType, valuePQ(pqSize));
}

void deletePQ(Point * p, int certType){
    PQObject * obj = Q[p->cert[certType]->pqpos];

    Q[pqpos(obj)] = Q[pqSize--];
    swim(pqpos(obj));
    sink(pqpos(obj), pqSize);

    free(p->cert[certType]);
    p->cert[certType] = NULL;
}

PQObject * minPQ(){
    return Q[1];
}

double valueMinPQ(){
    return valuePQ(1);
}

double valuePQ(int i){
    return Q[i]->p->cert[Q[i]->certType]->value;
}

double valuePQObject(PQObject * obj){
    return obj->p->cert[obj->certType]->value;
}

void updatePQ(Point * p, int certType, double t){
    PQObject * obj = Q[p->cert[certType]->pqpos];
    p->cert[certType]->value = t;

    swim(pqpos(obj));
    sink(pqpos(obj), pqSize);

}

void swim(int i){
    PQObject * obj;
    obj = Q[i];
    while(i/2 >= 1 && comparePQ(obj, Q[i/2])){
        Q[i] = Q[i/2];
        pqpos(Q[i/2]) = i;
        i = i/2;
    }
    Q[i] = obj;
    pqpos(obj) = i;
}

void sink(int i, int m){
    int s = 2*i, p = i;
    PQObject * x = Q[i];
    while(s <= m){
        if(s < m && comparePQ(Q[s + 1], Q[s]))
            s += 1;
        if(comparePQ(x, Q[s]))
            break;

        Q[p] = Q[s];
        pqpos(Q[p]) = p;
        p = s; s = 2*p;
    }
    Q[p] = x;
    pqpos(x) = p;
}

void printPQR(char * prefix, int size, int j, int b){
    int i, cert;
    char aux;
    char * newprefix;

    if(prefix == NULL){
        prefix = malloc(sizeof(*prefix));
        prefix[0] = '\0';
    }
    if(j <= pqSize)
    {
        for(i = 0; prefix[i] != '\0'; i++)
            printf("%c", prefix[i]);
        cert = Q[j]->certType;
        if(b)
            printf("├──");
        else
            printf("└──" );
        aux = ' ';
        if(Q[j]->p->prev[getDirection(cert)])
            aux = Q[j]->p->prev[getDirection(cert)]->name;
        printf("%d: %c -- %c, %g, prio: %.2lf, certType: ", j, Q[j]->p->name,
        aux, valuePQ(j), Q[j]->p->cert[cert]->priority);
        if(cert == HORIZONTAL_CERT){
            printf("HORIZONTAL_CERT\n");
        }
        else if(cert == UP_CERT){
            printf("UP_CERT\n");
        }
        else if(cert == DOWN_CERT){
            printf("DOWN_CERT\n");
        }
        else if(cert == ALL_CERT){
            printf("ALL_CERT\n");
        }
        else{
            printf("TOURN_CERT\n");
        }

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
		printPQR(newprefix, size + 4, 2*j, 1);
        printPQR(newprefix, size + 4, 2*j + 1, 0);

    }
    if(!b)
        free(prefix);
}

void printPQ(){
    printPQR(NULL, 1, 1, 0);
}

