#include<stdlib.h>
#include<math.h>
#include"debug.h"
#ifndef _UTIL_H
#define _UTIL_H
#define INFINITE 100000000

#define PI_3 acos(0.5)

#define COS_PI_3 cos(PI_3)
#define SIN_PI_3 sin(PI_3)
#define SIN_NEG_PI_3 -SIN_PI_3
#define COS_NEG_PI_3 COS_PI_3

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define mod(x) ((x) > 0 ? (x) : -(x))

#define EPS 1e-8

enum directions{
    /* +60º rotation */
    UP = 0,
    /* +0º rotation */
    HORIZONTAL,
    /* -60º rotation */
    DOWN
};

/* TOURN_CERT + HORIZONTAL_CERT, TOURN_CERT + UP_CERT */
enum cert_types{
    /* +60-order event */
    UP_CERT = 0,
    /* 0-order event */
    HORIZONTAL_CERT,
    /* -60-order event */
    DOWN_CERT,
    /* UP, HORIZONTAL and DOWN CERT */
    ALL_CERT,
    /* kinetic tourn event */
    TOURN_CERT
};

enum cert_priority{
    TOURN_PRIORITY,
    LOW_PRIORITY,
    MEDIUM_PRIORITY,
    HIGH_PRIORITY
};

enum splay_types{
    CANDS_TREE = 0,
    HITS_UP_TREE,
    HITS_LOW_TREE
};

typedef struct Coordinate{
    double x;
    double y;
} Coordinate;

typedef struct Vector{
    double x;
    double y;
} Vector;

typedef struct Cert{
    /* certificate type */
    int pqpos;
    double value;
    double priority;
} Cert;

typedef struct Point{
    char name; /* point's name */
    int id;
    Coordinate x0;
    Vector speed;
    struct Point * lcand[3];
    /* root of cands tree of the point */
    struct CandsNode * candsRoot[3];
    /* node where the point is in a cands tree */
    struct CandsNode * cands[3];
    /* node where the point is in a hitsLow tree */
    struct HitsNode * hitsLow[3];
    /* node where the point is in a hitsUp tree */
    struct HitsNode * hitsUp[3];
    struct HitsNode * hitsLowRoot[3];
    struct HitsNode * hitsUpRoot[3];
    struct AVLNode * listPosition[3];
    struct Point * prev[3];
    struct Point * next[3];
    Cert * cert[7]; /* ALL_CERT created to degenerate cases */
    int lastMatch[3];
} Point;

typedef Point Object;

typedef struct AVLNode
{
    struct AVLNode * left;
    struct AVLNode * right;
    Object * key;
    int children;
    int height;
} AVLNode;

typedef struct CandsNode{
    struct CandsNode * left;
    struct CandsNode * right;
    struct CandsNode * parent;
    Point * key;
    /* points to the leftmost point in the node subtrees */
    struct CandsNode * leftmost;
} CandsNode;

typedef struct HitsNode{
    struct HitsNode * left;
    struct HitsNode * right;
    struct HitsNode * parent;
    Point * key;
} HitsNode;

typedef struct TournObject{
    Point * p;
    Point * lcandp;
    int direction;
} TournObject;

typedef struct PQObject{
    Point * p;
    int certType;
} PQObject;

typedef Point Item;

/* priority queue */
PQObject ** Q;

/* kinetic tourn */
TournObject ** tourn;

/* where points will be at first */
Point ** initial;

/* current time */
double now;

/* number of elements */
int n;

/* lastID available */
int lastID;

/*! Get p x-coordinate in the specified direction
 * @param p the given point
 * @param dir the specified direction
 * @return the x-coordinate of the point in the specified direction
 */
double getX(Point * p, int dir);

/*! Get p y-coordinate in the specified direction
 * @param p the given point
 * @param dir the specified direction
 * @return the y-coordinate of the point in the specified direction
 */
double getY(Point * p, int dir);

/*! Get p x0-coordinate in the specified direction
 * @param p the given point
 * @param dir the specified direction
 * @return the x0-coordinate of the point in the specified direction
 */
double getX0(Point * p, int dir);

/*! Get p y0-coordinate in the specified direction
 * @param p the given point
 * @param dir the specified direction
 * @return the y0-coordinate of the point in the specified direction
 */
double getY0(Point * p, int dir);

/*! Get p speed first component in the specified direction
 * @param p the given point
 * @param dir the specified direction
 * @return the speed first component of the point in the specified direction
 */
double getVx(Point * p, int dir);

/*! Get p speed second component in the specified direction
 * @param p the given point
 * @param dir the specified direction
 * @return the speed first component of the point in the specified direction
 */
double getVy(Point * p, int dir);

/*! Calculates the distance between points a and b for the given direction
 * @param a one of the points of the pair
 * @param b the other point
 * @param dir the given direction
 * @return the distance between the two points
 */
double distance(Point * a, Point * b, int dir);

/*! Returns cert type based on direction
 * @param direction the given direction
 * @return the certificate type
 */
int certType(int direction);

/*! Returns lcand(p)
 * @param p the point whose lcand will be returned
 * @return lcand(p)
 */
Point * getLcand(Point * p);

/*! Updates lcand(p) and updates the pair p -- lcand(p) in tourn
 * @param p the point whose lcand will be updated
 * @param dir the direction specified
 * @return 1 if lcand has been updated, 0 if lcand didn't change
 */
int updateLcand(Point * p, int dir);

/*! Returns the direction based on the certificate type
 * @param certType the certifica type
 * @return the correspondent direction
 */
int getDirection(int certType);

/*! Prints the point p info in the specified direction (for debug)
 * @param p the given point
 * @param dir the specified direction
 */
void printPoint(Point * p, int dir);

/*! int getCertPriority(Point * p, Point * q, int dir)
 * @param p point p to the left of q, that will reach q in t'
 * @param q point q to the right of p
 * @param dir the direction of the certificate
 * @return returns the certificate priority
 */
double getCertPriority(Point * p, Point * q, int dir);


/*! int left(Point * p, Point * q, int dir)
 * @param p point p
 * @param q point q
 * @param dir the direction considered
 * @return returns 1 if p is to the left of q or will be to the left at
 * now + epsilon, 0 otherwise
 */
int left(Point *p, Point *q, int dir);

/*! int wasLeft(Point * p, Point * q, int dir)
 * @param p point p
 * @param q point q
 * @param dir the direction considered
 * @return returns 1 if p is to the left of q or was to the left at
 * now - epsilon, 0 otherwise
 */
int wasLeft(Point *p, Point *q, int dir);

/*! int left(Point * p, Point * q, int dir)
 * @param p point p
 * @param q point q
 * @param dir the direction considered
 * @return returns 1 if p is to the left of q (based on the state of
 * the lists, but not using the lists), 0 otherwise
 */
int leftTest(Point * p, Point * q, int dir);

/*! Prints the name of the given direction (for debug)
 * @param dir the given direction
 */
void printDir(int dir);

/* Frees all memory
 *
 */
void destroy();

#endif