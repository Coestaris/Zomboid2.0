//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_DRAWER_H
#define ZOMBOID2_DRAWER_H

#include <math.h>

#include <GL/freeglut.h>
#include <GL/gl.h>

#include "surface.h"
#include "tex.h"

#define BACKGROUND_OFFSET 15

#define DPTYPE_TEXT 0
#define DPTYPE_SPRITE 1
#define DPTYPE_LINE 2
#define DPTYPE_POLY 3
#define DPTYPE_POLY_TEX 4

typedef struct {
    double x;
    double y;

    double _angle;
} _point;

typedef struct _drawingPrimitive {

    int type;

    int frame;
    double r, g, b, a;
    double x1, x2, y1, y2;
    double scale, angle;
    void* font;
    char* string;
    tex2d* tex;
    _point* points;

} drawingPrimitive;

void dqnDrawText(double x, double y, double r, double g, double b, double a, void* font, char *string);
void dqnDrawSprite(tex2d* tex, double alpha, int frame, double x, double y, double angle, double scaleFactor);
void dqnDrawLine(double x1, double y1, double x2, double y2, double r, double g, double b, double a);
void dqnDrawPolygon(_point *points, int count, double x, double y, double r, double g, double b, double a);
void dqnDrawTexPolygon(tex2d* tex, _point *points, int count, double x, double y, double r, double g, double b, double a, double scale);

void dcRotateScreen(double angle, double sceneW, double sceneH);
void dcCreatePoint(double *x, double *y, double inx, double iny, double vcos, double vsin, double hw, double hh, double cx, double cy, int s1, int s2);
void dcDrawText(double x, double y, double r, double g, double b, double a, void *font, const char *string);
void dcDrawBackground(tex2d *tex, int frame, int windowW, int windowH);
void dcDrawTexture(tex2d *tex, double alpha, int frame, double x, double y, double angle, double scaleFactor);
void dcDrawLine(double x1, double y1, double x2, double y2, double r, double g, double b, double a);
void dcDrawPolygon(_point* points, int count, double x1, double y1, double r, double g, double b, double a);
void dcDrawTexPolygon(tex2d* tex, _point *points, int count, double x, double y, double r, double g, double b, double a, double scale);

void dcDrawSurface(int winW, int winH);
void dcDrawPrimitives(void);
void dcBeginDraw(void);
void dcEndDraw(void);
void dcInit();

#endif //ZOMBOID2_DRAWER_H
