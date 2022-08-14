#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <math.h>
#include <time.h>
#include"util.h"
#include"kds.h"
#ifndef _DRAW_H
#define _DRAW_H

#define LINE_WIDTH 5
#define WIDTH 1600
#define HEIGHT 900
#define FONT_SIZE 20
#define INITIAL_SCALE 60.0
#define STEP 0.01
#define STEP10 10*STEP

#define A_KEY 0x61
#define B_KEY 0x62
#define C_KEY 0x63
#define D_KEY 0x64
#define J_KEY 0x6a
#define K_KEY 0x6b
#define L_KEY 0x6c
#define I_KEY 0x69
#define E_KEY 0x65
#define M_KEY 0x6d
#define N_KEY 0x6e
#define S_KEY 0x73
#define T_KEY 0x74
#define V_KEY 0x76
#define X_KEY 0x78
#define Z_KEY 0x7a
#define RIGHT_KEY 0xff53
#define LEFT_KEY 0xff51
#define UP_KEY 0xff52
#define DOWN_KEY 0xff54
#define ENTER_KEY 0xff0d
#define ESC_KEY 0xff1b

#define RADIUS 4

/* surface where things are drawn */
cairo_surface_t *sfc;
/* context used */
cairo_t *ctx;

/* 1 - draw, 0 - don't draw */
int drawState;
/* 1 - draw debug info, 0 - don't draw */
int drawDebug;
/* SCALE - how much scale space
 * translate - how much translate space
 * x_c - new x center of coordinate system
 * y_c - new y center of coordinate system
 */
double SCALE, translate, x_c, y_c;

int drawCircle;
double theta, current_theta;
/* rgb colors */
typedef struct Color{
    double r, g, b;
} Color;

enum screen_positions{
    BOTTOM_LEFT,
    BOTTOM,
    BOTTOM_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    TOP_LEFT,
    TOP,
    TOP_RIGHT
};

enum line_style{
    SOLID,
    DASHED
};

/* some predefined colors */
Color red, green, blue, black, white, yellow, pblue;

/* time to wait for screen to be refreshed */
struct timespec ts;

/*! Open an X11 window and create a cairo surface base on that window.
 * @param x Width of window.
 * @param y Height of window.
 * @return Returns a pointer to a Xlib cairo surface.
 */
cairo_surface_t *cairo_create_x11_surface(int x, int y);

/*! Closes cairo surface and X11 display
 * @param sfc The surface to be closed.
 */
void cairo_close_x11_surface(cairo_surface_t *sfc);

/*! Creates a new surface and context and initializes
 *! important values
 * @param x Width of window.
 * @param y Height of window.
 */
void drawCreate(int x, int y);

/*! Initializes the draw states.
 *
 */
void drawInit();

/*! Draws now value on the top left of the screen
 *
 */
void drawTime();

/*! Calculates the edges of Dom(p)
 *
 * @param p point whose edges are calculated
 * @param dir direction of the edge (HORIZONTAL, DOWN or UP)
 * @param edge the edge to be calculated (UP or DOWN)
 * @return returns a coordinate (x, y) where (x(p), y(p)) -- (x, y)
 * is the edge to be drawn
 */
Coordinate drawEdge(Point *p, int dir, int edge);

/*! Draws all the points in blue
 * @param sel this point will be drawn in green
 * @param sel2 this point will be drawn in green
 */
void drawPoints(Point * sel, Point * sel2);

/*! Draws the point in blue (without label)
 * @param p point to be drawn
 * @param color color to be used
 */
void drawPoint(Point * p, Color color);

/*! Draws a line from p to q using color
 * @param p one of the vertex of the line
 * @param q the other vertex of the line
 * @param color color to be used
 * @param style the style of the line
 */
void drawLine(Point * p, Point * q, Color color, int style);

/*! Draws the given text into the screen given position
 * @param text the text to be drawn
 * @param pos the position where the text goes
 */
void drawText(char * text, int pos);

/*! Draws all the edges of the points with directiond dir
 * @param dir the direction of the edges
 */
void drawEdges(int dir);

/*! Draws next event time on the bottom left of the screen
 *
 */
void drawNextEvent();

/*! Checks all possible pair of points looking for the closest pair
 *
 */
void drawTest();

/*! Draws a green line between the closest pair of points
 *
 */
void drawClosestPair();

/*! Draws up(p) using the given color
 * @param p the point whose up will be drawn
 * @param dir the direction (UP, HORIZONTAL or DOWN)
 * @param color color to be used
 */
void drawUp(Point * p, int dir, Color color);

/*! Draws low(p) using the given color
 * @param p the point whose low will be drawn
 * @param dir the direction (UP, HORIZONTAL or DOWN)
 * @param color color to be used
 */
void drawLow(Point * p, int dir, Color color);

/*! Draws cands(p) using the given color
 * @param p the point whose cands will be drawn
 * @param dir the direction (UP, HORIZONTAL or DOWN)
 * @param color color to be used
 */
void drawCands(Point * p, int dir, Color color);

/*! Detects key presses and mouse clicks in the window
 * @param sfc the surface selected
 */
int drawHandleXEvent(cairo_surface_t *sfc);

/*! gets a unit vector of the edge in direction dir
 * @param dir the direction (HORIZONTAL, UP or DOWN)
 * @param order the edge (UP or DOWN)
 */
Vector getVector(int dir, int order);

/*! draws everything in the screen
 */
void draw();

/*! draws every "match" of the tournament
 */
void drawTourn();

/*! draws some phases of events
 * @param p point involved in the event
 * @param q point involved in the event
 * @param t point to be drawn
 * @param root root of the tree to be drawn
 * @param type type of the tree
 * @param dir direction
 * @param text text to be drawn at the bottom
 * @param eventType type of the event
 */
void drawEvent(Point * p, Point * q, Point * t, void * root, int type,
int dir, char * text, int eventType, int * skip);

/*! draws every point in the tree with root
 * @param root root of the tree
 * @param type type of the tree
 * @param color color to be used
 */
void drawPointsTree(void * root, int type, Color color);

/*! Draws a line between p and lcandp in the given direction
 * @param p the given point
 * @param dir the direction considered
 */
void drawLcand(Point * p, int dir);

/*! menu for draw interface
 *
 */
void draw_menu();

/*! Receives a point p and returns a coordinate in the circunference
 * that is drawn for collisions (for debug)
 * @param p the given point
 * @return returns a coordinate in the circunference of the point
*/
Coordinate getPointCoord(Point * p);

#endif