#include"draw.h"
#include<stdio.h>

cairo_surface_t *cairo_create_x11_surface(int x, int y){
    Display *dsp;
    Drawable da;
    int screen;
    cairo_surface_t *sfc;

    if((dsp = XOpenDisplay(NULL)) == NULL)
        exit(1);
    screen = DefaultScreen(dsp);
    da = XCreateSimpleWindow(dsp, DefaultRootWindow(dsp), 0, 0, x, y, 0, 0, 0);
    XStoreName(dsp, da, "Kinetic Pair");

    XSelectInput(dsp, da, ButtonPressMask | KeyPressMask);
    XMapWindow(dsp, da);

    sfc = cairo_xlib_surface_create(dsp, da, DefaultVisual(dsp, screen), x, y);
    cairo_xlib_surface_set_size(sfc, x, y);

    return sfc;
}

void cairo_close_x11_surface(cairo_surface_t *sfc){
   Display *dsp = cairo_xlib_surface_get_display(sfc);

   cairo_surface_destroy(sfc);
   XCloseDisplay(dsp);
}

void drawInit(){
    drawState = 0;
    drawDebug = 0;
    SCALE = INITIAL_SCALE;
    drawCircle = 0;
    theta = 0;
    current_theta = 0;
}

Coordinate getPointCoord(Point * p){
    Coordinate a;
    double vx, vy, aux_norm, cos_aux, sin_aux;
    vx = getVx(p, HORIZONTAL);
    vy = getVy(p, HORIZONTAL);
    aux_norm = sqrt(vx*vx + vy*vy);
    vx /= aux_norm;
    vy /= aux_norm;
    cos_aux = vx;
    sin_aux = vy;
    vx = cos_aux*cos(current_theta) - sin_aux*sin(current_theta);
    vy = sin_aux*cos(current_theta) + sin(current_theta)*cos_aux;

    a.x = -aux_norm*vx;
    a.y = -aux_norm*vy;

    return a;
}

void drawCreate(int x, int y){
    cairo_matrix_t matrix;
    sfc = cairo_create_x11_surface(x, y);
    ctx = cairo_create(sfc);
    matrix.x0 = matrix.y0 = 0;
    matrix.xy = matrix.yx = 0;
    matrix.xx = FONT_SIZE;
    matrix.yy = -FONT_SIZE;
    ts.tv_nsec = 5000000;
    ts.tv_sec = 0;
    translate = SCALE;
    x_c = y_c = 0;

    cairo_translate(ctx, x/2, y/2);
    cairo_scale(ctx, 1, -1);
    cairo_set_font_matrix(ctx, &matrix);
    cairo_set_line_width (ctx, LINE_WIDTH);

    red.r = 1;
    red.g = 0;
    red.b = 0;
    green.r = 0;
    green.g = 1;
    green.b = 0;
    blue.r = 0;
    blue.g = 0;
    blue.b = 1;
    black.r = 0;
    black.g = 0;
    black.b = 0;
    white.r = 1;
    white.g = 1;
    white.b = 1;
    yellow.r = 1;
    yellow.g = 1;
    yellow.b = 0;
    pblue.r = 0.4;
    pblue.g = 1;
    pblue.b = 1;
}

Vector getVector(int dir, int order){
    Vector v;
    double angle = 0;
    if(dir == UP)
        angle += PI_3;
    else if(dir == DOWN)
        angle -= PI_3;
    if(order == UP)
        angle += PI_3/2;
    else if(order == DOWN)
        angle -= PI_3/2;
    v.x = cos(angle);
    v.y = sin(angle);
    return v;
}

Coordinate drawEdge(Point * p, int dir, int edge){
    Point * up, * low;
    Coordinate a, b;
    double alpha;
    const double norm = 20.0;
    Vector v1 = getVector(dir, UP);
    Vector v2 = getVector(dir, DOWN);
    a.x = getX(p, HORIZONTAL);
    a.y = getY(p, HORIZONTAL);
    db(
    if(drawCircle){
        a = getPointCoord(p);
    }
    );
    if(edge == UP){

        up = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);

        if(up == NULL){
            b.x = a.x + norm*v1.x;
            b.y = a.y + norm*v1.y;
        }
        else{
            b.x = getX(up, HORIZONTAL);
            b.y = getY(up, HORIZONTAL);
            db(
            if(drawCircle){
                b = getPointCoord(up);
            }
            );
            alpha = (b.y - a.y)*v2.x - v2.y*(b.x - a.x);
            alpha /= -v1.x*v2.y + v2.x*v1.y;

            b.x = a.x + alpha*v1.x;
            b.y = a.y + alpha*v1.y;
        }
        return b;
    }
    v1 = getVector(dir, DOWN);
    v2 = getVector(dir, UP);

    low = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);

    if(low == NULL){
        b.x = a.x + norm*v1.x;
        b.y = a.y + norm*v1.y;
    }
    else{
        b.x = getX(low, HORIZONTAL);
        b.y = getY(low, HORIZONTAL);
        db(
        if(drawCircle){
            b = getPointCoord(low);
        }
        );
        alpha = (b.y - a.y)*v2.x - v2.y*(b.x - a.x);
        alpha /= -v1.x*v2.y + v2.x*v1.y;

        b.x = a.x + alpha*v1.x;
        b.y = a.y + alpha*v1.y;
    }

    return b;
}

int drawHandleXEvent(cairo_surface_t * sfc){
    XEvent e;
    char keybuf[8];
    KeySym key;
    if (XPending(cairo_xlib_surface_get_display(sfc)))
        XNextEvent(cairo_xlib_surface_get_display(sfc), &e);
    else
        return 0;

    switch (e.type)
    {
        case ButtonPress:
            return -e.xbutton.button;
        case KeyPress:
            XLookupString(&e.xkey, keybuf, sizeof(keybuf), &key, NULL);
            return key;
        default:
            break;
    }

    return 0;
}

void drawEdges(int dir){
    int i;
    Point * p;
    Coordinate a, b;

    for(i = 1; i <= n; i++){
        p = initial[i];
        a.x = getX(p, HORIZONTAL);
        a.y = getY(p, HORIZONTAL);
        db(
        if(drawCircle){
            a = getPointCoord(p);
        }
        );
        cairo_set_line_width (ctx, 2);
        b = drawEdge(p, dir, UP);
        a.x *= SCALE;
        a.y *= SCALE;
        b.x *= SCALE;
        b.y *= SCALE;
        cairo_set_source_rgb(ctx, red.r, red.g, red.b);
        cairo_move_to(ctx, a.x, a.y);
        cairo_line_to(ctx, b.x, b.y);
        cairo_stroke(ctx);
        b = drawEdge(p, dir, DOWN);
        b.x *= SCALE;
        b.y *= SCALE;
        cairo_set_source_rgb (ctx, red.r, red.g, red.b);
        cairo_move_to(ctx, a.x, a.y);
        cairo_line_to(ctx, b.x, b.y);
        cairo_stroke(ctx);

        drawLcand(p, dir);
    }
}

void drawPoints(Point * sel, Point * sel2){
    int i;
    Point * p;
    Coordinate a;
    cairo_text_extents_t te;
    char text[2];
    double norm, vx, vy;

    for(i = 1; i <= n; i++){
        p = initial[i];
        a.x = getX(p, HORIZONTAL);
        a.y = getY(p, HORIZONTAL);
        if(drawCircle){
            vx = getVx(p, HORIZONTAL);
            vy = getVy(p, HORIZONTAL);
            norm = sqrt(vx*vx + vy*vy);
            cairo_set_line_width (ctx, 2);
            cairo_set_source_rgb(ctx, pblue.r, pblue.g, pblue.b);
            cairo_arc(ctx, a.x + vx, a.y + vy,
            norm*SCALE, 0, 2*M_PI);
            cairo_stroke(ctx);
            cairo_set_line_width (ctx, LINE_WIDTH);
        }
        if(drawCircle){
            a = getPointCoord(p);
        }
        a.x *= SCALE;
        a.y *= SCALE;
        cairo_set_line_width (ctx, LINE_WIDTH);
        text[0] = p->name;
        text[1] = '\0';
        if(sel == p || sel2 == p)
            cairo_set_source_rgb (ctx, green.r, green.g, green.b);
        else
            cairo_set_source_rgb (ctx, blue.r, blue.g, blue.b);
        cairo_arc(ctx, a.x, a.y, 2, 0, 2*M_PI);
        cairo_stroke(ctx);

        cairo_set_source_rgb (ctx, white.r, white.g, white.b);
        cairo_move_to(ctx, a.x + 10, a.y - 10);
        cairo_text_extents (ctx, text, &te);
        cairo_show_text(ctx, text);
        cairo_stroke(ctx);
    }
}

void drawTest(){
    Point *p, *q, *r, *s;
    struct timespec tc = {0, 500000000};
    int i, j, x, y, c;
    double dmin = distance(initial[1], initial[2], HORIZONTAL);
    x = 1;
    y = 2;

    for(c = i = 1, j = 2; c && (i <= n && j <= n);){
        cairo_push_group(ctx);
        cairo_set_source_rgb(ctx, black.r, black.g, black.b);
        cairo_paint(ctx);

        if(distance(initial[i], initial[j], HORIZONTAL) < dmin){
            x = i;
            y = j;
            dmin = distance(initial[i], initial[j], HORIZONTAL);
        }

        p = initial[x];
        q = initial[y];
        r = initial[i];
        s = initial[j];

        drawLine(p, q, green, SOLID);

        drawPoints(p, q);

        drawLine(r, s, blue, SOLID);

        drawPoint(r, red);
        drawPoint(s, red);

        cairo_pop_group_to_source(ctx);
        cairo_paint(ctx);
        cairo_surface_flush(sfc);
        nanosleep(&tc, NULL);
        switch(drawHandleXEvent(sfc)){
            case C_KEY:
                c = 0;
                break;
            default:
                break;
        }
        if(j != n)
            j++;
        else{
            i++;
            j = i + 1;
        }
    }

    printf("%c -- %c, distance: %.3lf\n", initial[x]->name, initial[y]->name, dmin);
}

void drawPointsTree(void * root, int type, Color color){
    Point * p;
    if(root != NULL){
        drawPointsTree(getLeftS(root, type), type, color);
        drawPointsTree(getRightS(root, type), type, color);

        p = getKeyS(root, type);
        drawPoint(p, color);
    }
}

void drawNextEvent(){
    int j;
    char text[100], eventType[50], direct[50];
    j = minPQ()->certType;
    if(j < TOURN_CERT){
        if(j != ALL_CERT)
            sprintf(eventType, "Swap in order: ");
        else
            sprintf(eventType, "Swap in all orders");
    }
    else{
        sprintf(eventType, "Tourn event: ");
    }
    if(getDirection(j) == HORIZONTAL){
        sprintf(direct, "HORIZONTAL");
    }
    else if(getDirection(j) == UP){
        sprintf(direct, "UP");
    }
    else if(getDirection(j) == DOWN){
        sprintf(direct, "DOWN");
    }
    else sprintf(direct, " ");
    sprintf(text, "%s%s", eventType, direct);

    drawText(text, BOTTOM_LEFT);
}

void drawClosestPair(){
    TournObject * x = tourn[1];
    Point *p, *q;
    char text[100];
    p = x->p;
    q = x->lcandp;

    if(q != NULL){
        drawLine(p, q, green, SOLID);

        sprintf(text, "Distance: %.3lf", distance(p, q, HORIZONTAL));
        drawText(text, TOP_RIGHT);
    }
    else{
        fprintf(stderr, "Something gone wrong!!\n");
        exit(1);
    }
}

void drawTime(){
    char text[20];
    sprintf(text, "Now: %.3lf", now);

    drawText(text, TOP_LEFT);
}

void drawPoint(Point * p, Color color){
    Coordinate a;
    a.x = getX(p, HORIZONTAL);
    a.y = getY(p, HORIZONTAL);
    if(drawCircle){
        a = getPointCoord(p);
    }
    a.x *= SCALE;
    a.y *= SCALE;

    cairo_set_source_rgb(ctx, color.r, color.g, color.b);
    cairo_arc(ctx, a.x, a.y, 2, 0, 2*M_PI);
    cairo_stroke(ctx);
}

void drawLine(Point * p, Point * q, Color color, int style){
    Coordinate a, b;
    double dashes[2] = {5, 2};
    a.x = getX(p, HORIZONTAL);
    a.y = getY(p, HORIZONTAL);
    if(drawCircle){
        a = getPointCoord(p);
    }
    a.x *= SCALE;
    a.y *= SCALE;

    b.x = getX(q, HORIZONTAL);
    b.y = getY(q, HORIZONTAL);
    if(drawCircle){
        b = getPointCoord(q);
    }
    b.x *= SCALE;
    b.y *= SCALE;

    cairo_set_line_width (ctx, 2);
    cairo_set_source_rgb(ctx, color.r, color.g, color.b);
    if(style == DASHED){
        cairo_set_antialias(ctx,  CAIRO_ANTIALIAS_FAST);
        cairo_set_dash(ctx, dashes, 1, 0);
    }
    cairo_move_to(ctx, a.x, a.y);
    cairo_line_to(ctx, b.x, b.y);
    cairo_stroke(ctx);
    cairo_set_line_width (ctx, LINE_WIDTH);
    cairo_set_dash(ctx, dashes, 0, 0);
}

void drawText(char * text, int pos){
    Coordinate a;
    double c = 30, d = 45;
    cairo_text_extents_t te;
    switch (pos){
        case TOP_LEFT:
            a.x = x_c - WIDTH/2 + c/2;
            a.y = y_c + HEIGHT/2 - c;
            break;
        case TOP:
            a.x = x_c - d*sizeof(text);
            a.y = y_c + HEIGHT/2 - c;
            break;
        case TOP_RIGHT:
            a.x = x_c + WIDTH/2 - d*sizeof(text);
            a.y = y_c + HEIGHT/2 - c;
            break;
        case CENTER_LEFT:
            a.x = x_c - WIDTH/2 + c/2;
            a.y = y_c;
            break;
        case CENTER:
            a.x = x_c - d*sizeof(text)/2;
            a.y = y_c;
            break;
        case CENTER_RIGHT:
            a.x = x_c + WIDTH/2 - d*sizeof(text);
            a.y = y_c;
            break;
        case BOTTOM_LEFT:
            a.x = x_c - WIDTH/2 + c/2;
            a.y = y_c - HEIGHT/2 + c/2;
            break;
        case BOTTOM:
            a.x = x_c - d*sizeof(text);
            a.y = y_c - HEIGHT/2 + c/2;
            break;
        case BOTTOM_RIGHT:
            a.x = x_c + WIDTH/2 - d*sizeof(text);
            a.y = y_c - HEIGHT/2 + c/2;
            break;
        default:
            break;
    }

    cairo_set_source_rgb (ctx, white.r, white.g, white.b);
    cairo_move_to(ctx, a.x, a.y);
    cairo_text_extents (ctx, text, &te);
    cairo_show_text(ctx, text);
    cairo_stroke(ctx);
}

void drawLcand(Point * p, int dir){
    Point * q;
    q = p->lcand[dir];
    if(q != NULL)
        drawLine(p, q, yellow, DASHED);
}

void drawTourn(){
    int i;
    TournObject * x, * y;
    Point *p, *q, *r, *s;
    int autom = 0;
    double dist1, dist2;
    for(i = 2*tournElem - 1; i > 1;){
        cairo_push_group(ctx);
        cairo_set_source_rgb(ctx, black.r, black.g, black.b);
        cairo_paint(ctx);

        drawPoints(NULL, NULL);
        x = tourn[i];
        y = tourn[i - 1];
        p = x->p;
        q = x->lcandp;
        r = y->p;
        s = y->lcandp;
        if(q != NULL)
            drawPoint(q, green);

        drawPoint(p, green);
        drawPoint(r, yellow);
        if(s != NULL)
            drawPoint(s, yellow);

        dist1 = distance(x->p, x->lcandp, x->direction);
        dist2 = distance(y->p, y->lcandp, y->direction);
        if(dist1 < dist2 && mod(dist1 - dist2) > EPS){
            if(tourn[i/2] != x){
                /* tourn is wrong */
                if(s != NULL){
                    drawLine(r, s, red, SOLID);
                    drawPoint(s, red);
                }
                drawPoint(r, red);
                if(autom) i += 2;
            }
            else{
                if(q != NULL){
                    drawLine(p, q, white, SOLID);
                    drawPoint(q, white);
                }
                drawPoint(p, white);
            }
        }
        else if(dist2 < dist1 && mod(dist1 - dist2) > EPS){
            if(tourn[i/2] != y){
                if(q != NULL){
                    drawLine(p, q, red, SOLID);
                    drawPoint(q, red);
                }
                drawPoint(p, red);
                if(autom) i += 2;
            }
            else{
                if(s != NULL){
                    drawLine(r, s, white, SOLID);
                    drawPoint(s, white);
                }
                drawPoint(s, white);
            }
        }
        cairo_pop_group_to_source(ctx);
        cairo_paint(ctx);
        cairo_surface_flush(sfc);
        switch (drawHandleXEvent(sfc))
        {
            case N_KEY:
                i -= 2;
                break;
            case A_KEY:
                autom = 1;
                break;
            default:
                break;
        }
        if(autom)
            i -= 2;
        nanosleep(&ts, NULL);
    }
}

void drawLow(Point * p, int dir, Color color){
    Point * q = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);
    Coordinate a;

    /* drawPointsTree(p->hitsLowRoot[dir]->parent, HITS_LOW_TREE, color); */

    if(q != NULL){
        a.x = getX(q, HORIZONTAL);
        a.y = getY(q, HORIZONTAL);
        if(drawCircle){
            a = getPointCoord(q);
        }
        a.x *= SCALE;
        a.y *= SCALE;
        cairo_set_source_rgb(ctx, color.r, color.g, color.b);
        cairo_arc(ctx, a.x, a.y, 2, 0, 2*M_PI);
        cairo_stroke(ctx);
    }
}

void drawUp(Point * p, int dir, Color color){
    Point * q = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);
    Coordinate a;

    /* drawPointsTree(p->hitsUpRoot[dir]->parent, HITS_UP_TREE, color); */
    if(q != NULL){
        a.x = getX(q, HORIZONTAL);
        a.y = getY(q, HORIZONTAL);
        if(drawCircle){
            a = getPointCoord(q);
        }
        a.x *= SCALE;
        a.y *= SCALE;
        cairo_set_source_rgb(ctx, color.r, color.g, color.b);
        cairo_arc(ctx, a.x, a.y, 2, 0, 2*M_PI);
        cairo_stroke(ctx);
    }
}

void drawCands(Point * p, int dir, Color color){
    drawPointsTree(p->candsRoot[dir]->parent, CANDS_TREE, color);
}

void drawEvent(Point * p, Point * q, Point * t, void * root, int type,
int dir, char * text, int eventType, int * skip){
    int c;
    char event[100];
    if(dir != UP)
        return;
    if(eventType == HORIZONTAL)
        sprintf(event, "Horizontal event between %c and %c", p->name, q->name);
    else if(eventType == UP)
        sprintf(event, "Up event between %c and %c", p->name, q->name);
    else if(eventType == DOWN)
        sprintf(event, "Down event between %c and %c", p->name, q->name);
    for(c = 1; c && drawDebug && drawState && *skip;){
        cairo_push_group(ctx);
        cairo_set_source_rgb(ctx, black.r, black.g, black.b);
        cairo_paint(ctx);

        if(dir >= 0) drawEdges(dir);

        drawPoints(p, q);

        if(t != NULL)
            drawPoint(t, yellow);

        drawPointsTree(root, type, white);

        if(text != NULL)
            drawText(text, BOTTOM);

        if(eventType >= 0)
            drawText(event, TOP_RIGHT);

        drawTime();

        cairo_pop_group_to_source(ctx);
        cairo_paint(ctx);
        cairo_surface_flush(sfc);
        nanosleep(&ts, NULL);
        switch(drawHandleXEvent(sfc)){
            case C_KEY:
                c = 0;
                break;
            case S_KEY:
                *skip = 0;
                break;
            case J_KEY:
                x_c -= translate;
                cairo_translate(ctx, translate, 0);
                break;
            case K_KEY:
                y_c -= translate;
                cairo_translate(ctx, 0, translate);
                break;
            case L_KEY:
                x_c += translate;
                cairo_translate(ctx, -translate, 0);
                break;
            case I_KEY:
                y_c += translate;
                cairo_translate(ctx, 0, -translate);
                break;
            case Z_KEY:
                SCALE += 1;
                break;
            case X_KEY:
                SCALE -= 1;
                break;
            default:
                break;
        }
        if(current_theta < theta){
            current_theta += STEP/10;
        }
        if(current_theta > theta){
            current_theta = theta;
        }
    }
}

void draw(){
    int dir = HORIZONTAL, sel, autom, enter;
    Point * p;

    drawCreate(WIDTH, HEIGHT);
    drawState = 1;
    sel = enter = 0;
    autom = 0;

    draw_menu();

    for(;;){
        cairo_push_group(ctx);
        cairo_set_source_rgb(ctx, black.r, black.g, black.b);
        cairo_paint(ctx);

        // if(drawCircle){
        //     cairo_set_line_width (ctx, 2);
        //     cairo_set_source_rgb(ctx, pblue.r, pblue.g, pblue.b);
        //     cairo_arc(ctx, 0, 0, RADIUS*SCALE, 0, 2*M_PI);
        //     cairo_stroke(ctx);
        //     cairo_set_line_width (ctx, LINE_WIDTH);
        // }

        drawNextEvent();
        drawTime();

        if(dir >= 0) drawEdges(dir);

        drawClosestPair();
        if(sel > 0)
            p = initial[sel];
        else
            p = NULL;
        drawPoints(p, NULL);

        if(enter){
            drawLow(p, dir, yellow);
            drawUp(p, dir, yellow);
            drawCands(p, dir, white);
        }

        cairo_pop_group_to_source(ctx);
        cairo_paint(ctx);
        cairo_surface_flush(sfc);
        nanosleep(&ts, NULL);

        switch(drawHandleXEvent(sfc)){
            case N_KEY:
                sel--;
                sel += n*(sel == 0);
                break;
            case M_KEY:
                sel++;
                sel %= (n + 1);
                sel += (sel == 0);
                break;
            case A_KEY:
                advance(now + STEP10);
                break;
            case D_KEY:
                drawDebug = !drawDebug;
                break;
            case S_KEY:
                fprintf(stdout, "New scale\n");
                scanf("%lf", &SCALE);
                break;
            case B_KEY:
                if(sel <= 0)
                    sel = 1;
                else
                    sel = enter = 0;
                break;
            case E_KEY:
                autom = !autom;
                break;
            case T_KEY:
                /* drawTourn(); */
                drawTest();
                break;
            case RIGHT_KEY:
                dir = HORIZONTAL;
                break;
            case LEFT_KEY:
                dir = -1;
                enter = 0;
                break;
            case UP_KEY:
                dir = UP;
                break;
            case DOWN_KEY:
                dir = DOWN;
                break;
            case ENTER_KEY:
                /*  */
                if(sel > 0){
                    enter = !enter;
                    printS(initial[sel]->hitsUpRoot[UP], HITS_UP_TREE);
                }
                else
                    enter = 0;
                break;
            case J_KEY:
                x_c -= translate;
                cairo_translate(ctx, translate, 0);
                break;
            case K_KEY:
                y_c -= translate;
                cairo_translate(ctx, 0, translate);
                break;
            case L_KEY:
                x_c += translate;
                cairo_translate(ctx, -translate, 0);
                break;
            case I_KEY:
                y_c += translate;
                cairo_translate(ctx, 0, -translate);
                break;
            case V_KEY:
                drawCircle = !drawCircle;
                break;
            case Z_KEY:
                SCALE += 1;
                break;
            case X_KEY:
                SCALE -= 1;
                break;
            default:
                break;
        }
        if(autom){
            if(min(now + STEP, nextEvent()) == nextEvent() && drawDebug){
                autom = !autom;
            }
            advance(min(now + STEP, nextEvent()));
        }
        if(current_theta < theta){
            current_theta += STEP/10;
        }
        if(current_theta > theta){
            current_theta = theta;
        }
    }
}


void draw_menu(){
    printf("a - advance 0.1s in time\n");
    printf("e - auto advance in time\n");
    printf("z - zoom in\n");
    printf("x - zoom out\n");
    printf("j - move left\n");
    printf("k - move down\n");
    printf("i - move up\n");
    printf("l - move down\n");
    printf("right arrow - draw edges in horizontal direction\n");
    printf("up arrow - draw edges in up direction\n");
    printf("down arrow - draw edges in down direction\n");
    printf("left arrow - no edges drawn\n");
}