#include "util.h"
#include"splay_tree.h"

double getX(Point * p, int direction){
    double ret = 1;

    if(direction < 0){
        direction = -direction;
        ret = -ret;
    }

    return ret*(getX0(p, direction) + now*getVx(p, direction));
}

double getY(Point * p, int direction){
    double ret = 1;

    if(direction < 0){
        direction = -direction;
        ret = -ret;
    }

    return ret*(getY0(p, direction) + now*getVy(p, direction));
}

double getX0(Point * p, int direction){
    double angle = PI_3;

    if(direction == HORIZONTAL){
        angle = 0;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return (p->x0.x)*cos(angle) + (p->x0.y)*sin(angle);
}

double getY0(Point * p, int direction){
    double angle = PI_3;

    if(direction == HORIZONTAL){
        angle = 0;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return -(p->x0.x)*sin(angle) + (p->x0.y)*cos(angle);
}

double getVx(Point * p, int direction){
    double angle = PI_3;
    double ret = 1;

    if(direction < 0){
        direction = -direction;
        ret = -1;
    }

    if(direction == HORIZONTAL){
        angle = 0;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return ret*((p->speed.x)*cos(angle) + (p->speed.y)*sin(angle));
}

double getVy(Point * p, int direction){
    double angle = PI_3;
    double ret = 1;

    if(direction < 0){
        direction = -direction;
        ret = -1;
    }

    if(direction == HORIZONTAL){
        angle = 0;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return ret*(-(p->speed.x)*sin(angle) + (p->speed.y)*cos(angle));
}

double distance(Point * a, Point * b, int direction){
    double dx, dy;
    if(a == NULL || b == NULL)
        return INFINITE;
    dx = (getX(a, direction) - getX(b, direction));
    dy = (getY(a, direction) - getY(b, direction));
    return sqrt(dx*dx + dy*dy);
}

int certType(int direction){
    if(direction == UP)
        return UP_CERT;
    if(direction == DOWN)
        return DOWN_CERT;

    return HORIZONTAL_CERT;
}

void printPoint(Point * p, int dir){
    Point * hlow, *hup, *cand;
    printf("Direction: ");
    if(dir == HORIZONTAL)
        printf("HORIZONTAL");
    else if(dir == UP)
        printf("UP");
    else
        printf("DOWN");

    printf("\n");
    printf("Point: %c\n", p->name);
    printf("x0: (%g, %g), speed: (%g, %g)\n", p->x0.x, p->x0.y, p->speed.x, p->speed.y);
    printf("Current position: (%g, %g)\n", getX(p, dir), getY(p, dir));

    cand = ownerS(p->cands[dir], CANDS_TREE, dir);
    if(cand)
        printf("%c is in Cands(%c)\n", p->name, cand->name);
    hup = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);
    if(hup)
        printf("%c is in Hits_up(%c)\n", p->name, hup->name);
    hlow = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);
    if(hlow)
        printf("%c is in Hits_low(%c)\n", p->name, hlow->name);

    printf("Cands(%c) = \n", p->name);
    printS(p->candsRoot[dir], CANDS_TREE);
    printf("Hits_up(%c) = \n", p->name);
    printS(p->hitsUpRoot[dir], HITS_UP_TREE);
    printf("Hits_low(%c) = \n", p->name);
    printS(p->hitsLowRoot[dir], HITS_LOW_TREE);
    if(p->next[dir])
        printf("Next: %c\n", p->next[dir]->name);
    if(p->prev[dir])
        printf("Prev: %c\n", p->prev[dir]->name);
}

int updateLcand(Point * p, int dir){
    Point * lcand = NULL;
    int retval = 0;

    if(p->candsRoot[dir]->parent)
        /* leftmost can't be NULL */
        lcand = getKeyS(p->candsRoot[dir]->parent->leftmost, CANDS_TREE);

    if(p->lcand[dir] != lcand)
        retval = 1;

    p->lcand[dir] = lcand;

    return retval;
}

int getDirection(int certType){
    int retval;
    if(certType == HORIZONTAL_CERT)
        retval = HORIZONTAL;
    else if(certType == UP_CERT)
        retval = UP;
    else if(certType == DOWN_CERT)
        retval = DOWN;
    else if(certType == ALL_CERT)
        retval = 3;
    else
        retval = certType - TOURN_CERT;

    return retval;
}

int left(Point *p, Point *q, int dir){
    double vxp, vxq, vyp, vyq, aux;
    if(getX(p, dir) < getX(q, dir) - EPS){
        return 1;
    }
    else if(getX(q, dir) < getX(p, dir) - EPS){
        return 0;
    }
    else{
        if(getY(p, dir) > getY(q, dir) + EPS)
            return 1;
        else if(getY(p, dir) < getY(q, dir) - EPS)
            return 0;
        else{
            vxp = getVx(p, dir);
            vxq = getVx(q, dir);

            aux = max(mod(vxp), mod(vxq));

            vxp -= aux;
            vxq -= aux;

            if(vxp < vxq - EPS) /* p is to the left after t+epsilon (was to the right) */
                return 1;
            else if(vxq < vxp - EPS)/* q is to the left after t+epsilon (was to the right) */
                return 0;
            else{
                vyp = getVy(p, dir);
                vyq = getVy(q, dir);

                aux = max(mod(vyp), mod(vyq));

                vyp -= aux;
                vyq -= aux;
                if(vyp < vyq - EPS) /* p is below q after t+epsilon (was above, therefore to the left) */
                    return 0;
                else
                    return 1;
            }
        }
    }
}

int wasLeft(Point *p, Point *q, int dir){
    double vxp, vxq, vyp, vyq, aux;
    if(getX(p, dir) < getX(q, dir) - EPS){
        return 1;
    }
    else if(getX(q, dir) < getX(p, dir) - EPS){
        return 0;
    }
    else{
        if(getY(p, dir) > getY(q, dir) + EPS)
            return 1;
        else if(getY(p, dir) < getY(q, dir) - EPS)
            return 0;
        else{
            vxp = getVx(p, dir);
            vxq = getVx(q, dir);

            aux = max(mod(vxp), mod(vxq));

            vxp -= aux;
            vxq -= aux;

            if(vxp < vxq - EPS) /* p is to the left after t+epsilon (was to the right) */
                return 0;
            else if(vxq < vxp - EPS)/* q is to the left after t+epsilon (was to the right) */
                return 1;
            else{
                vyp = getVy(p, dir);
                vyq = getVy(q, dir);

                aux = max(mod(vyp), mod(vyq));

                vyp -= aux;
                vyq -= aux;
                if(vyp < vyq - EPS) /* p is below q after t+epsilon (was above, therefore to the left) */
                    return 1;
                else
                    return 0;
            }
        }
    }
}

double auxAtan(double x){
    double ret = atan(x);
    if(ret < -EPS)
        ret += M_PI;
    if(mod(ret) < EPS)
        ret = M_PI;
    return ret;
}

double getAngle(Vector a, Vector b){
    double anorm, bnorm;
    double x = a.x*b.x + a.y*b.y;
    anorm = sqrt(a.x*a.x + a.y*a.y);
    bnorm = sqrt(b.x*b.x + b.y*b.y);
    if(anorm < EPS || bnorm < EPS)
    /* problema */
        return 0;
    x /= anorm;
    x /= bnorm;

    return x;
}

double getCertPriority(Point * p, Point * q, int dir){
    double a, b, cosalp, sinalp, c, d;
    double alpha = 0, theta = 0, x;
    Point * auxp;
    Vector aux;
    double norm_vp, norm_vq;
    if(wasLeft(q, p, dir)){
        auxp = q;
        q = p;
        p = auxp;
    }
    norm_vp = sqrt(p->speed.x*p->speed.x + p->speed.y*p->speed.y);
    norm_vq = sqrt(q->speed.x*q->speed.x + q->speed.y*q->speed.y);
    if(mod(p->speed.x) < EPS && mod(p->speed.y) < EPS){
        return auxAtan(getVx(q, dir)/getVy(q, dir));
    }
    if(mod(q->speed.x) < EPS && mod(q->speed.y) < EPS){
        return auxAtan(getVx(p, dir)/getVy(p, dir));
    }
    aux.x = -1;
    aux.y = 0;
    if(dir == UP)
        alpha = PI_3;
    else if(dir == DOWN)
        alpha = -PI_3;
    cosalp = cos(alpha);
    if(mod(cosalp) < EPS)
        cosalp = 0;
    sinalp = sin(alpha);
    if(mod(sinalp) < EPS)
        sinalp = 0;
    c = getAngle(p->speed, aux);
    if(mod(c) < EPS)
        c = 0;
    d = getAngle(q->speed, aux);
    if(mod(d) < EPS)
        d = 0;
    a = (norm_vp/norm_vq)*c - d;
    c = sqrt(1 - c*c);

    if(-p->speed.y < -EPS)
        c = -c;

    d = sqrt(1 - d*d);
    if(-q->speed.y < -EPS)
        d = -d;
    if(mod(c) < EPS)
        c = 0;
    if(mod(d) < EPS)
        d = 0;
    b = (norm_vp/norm_vq)*c - d;
    if(mod(a) < EPS)
        a = 0;
    if(mod(b) < EPS)
        b = 0;
    x = a*cosalp + b*sinalp;
    x = x/(b*cosalp - a*sinalp);
    theta = auxAtan(x);

    return theta;
}

int auxDir(int dir){
    if(dir < 0){
        if(dir == -7)
            return UP;
        else
            return -dir;
    }
    return dir;
}

int leftTest(Point * p, Point * q, int dir){
    int auxdir;
    double prio;
    Point * cert_point;
    PQObject * pq;
    Cert * c;
    if(getX(p, dir) < getX(q, dir) - EPS){
        return 1;
    }
    else if(getX(q, dir) < getX(p, dir) - EPS){
        return 0;
    }
    else{
        if(getY(p, dir) > getY(q, dir) + EPS)
            return 1;
        else if(getY(p, dir) < getY(q, dir) - EPS)
            return 0;
        else{
            auxdir = auxDir(dir);
            prio = getCertPriority(p, q, auxdir);
            pq = Q[1];
            if(pq == NULL)
                return left(p, q, dir);
            cert_point = pq->p;
            c = cert_point->cert[pq->certType];
            /* pego o evento no topo da fila atualmente */
            /* checo se a troca entre p e q deveria ser processada
            antes ou depois desse evento */
            printf("compare: %.2lf with: %.2lf\n", prio, c->priority);
            if(mod(prio - c->priority) < EPS){
                printf("PASSEI POR AQUI\n");
                return left(p, q, dir);
            }
            else if(prio < c->priority - EPS){
                return left(p, q, dir);
            }
            else if(prio > c->priority + EPS){
                return wasLeft(p, q, dir);
            }
            else{
                printf("%lf, %lf\n", prio, c->priority);
                exit(1);
                return 0;
            }
        }
    }
}

void printDir(int dir){
    if(dir == HORIZONTAL)
        printf("HORIZONTAL");
    else if(dir == UP)
        printf("UP");
    else if(dir == DOWN)
        printf("DOWN");
}

void destroy(){

}