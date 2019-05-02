//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_DRAWER_H
#define ZOMBOID2_DRAWER_H

#include <math.h>

#include <GL/freeglut.h>
#include <GL/gl.h>

#include "gmath.h"
#include "surface.h"
#include "../shaders/shaderManager.h"
#include "../resources/font.h"
#include "../resources/tex.h"
#include "../structs.h"

#define BACKGROUND_OFFSET 15

#define MAXDP_START 2000
#define MAX_DP_LEVELS 20
#define SIZE_INCREASE 1.2

#define DPTYPE_TEXT 0
#define DPTYPE_SPRITE 1
#define DPTYPE_LINE 2
#define DPTYPE_POLY 3
#define DPTYPE_POLY_TEX 4
#define DPTYPE_POLY_ROTATEDTEX 5

typedef struct _relPoint {
    vec_t point;
    double angle;
    double distance;

} relPoint_t;

typedef struct _drawingPrimitive {

    int type;

    int frame;
    color_t col;
    vec_t p1;
    vec_t p2;

    double scale, angle;
    font_t* font;
    char* string;
    int count;
    tex_t* tex;
    relPoint_t* points;

    vec_t texOffset;
    vec_t texScaleFactor;

} drawingPrimitive_t;

void dqnDrawText(vec_t pos, color_t col, font_t* font, char* string, double size, int depth);
void dqnDrawSprite(tex_t *tex, color_t color, int frame, vec_t pos, double angle, double scaleFactor, int depth);
void dqnDrawLine(vec_t p1, vec_t p2, color_t col, int depth);
void dqnDrawPolygon(relPoint_t* points, int count, vec_t center, color_t col, int depth);
void dqnDrawTexPolygon(tex_t* tex, int frame, relPoint_t *points, int count, vec_t center, color_t col, double scale, int depth);
void dqnDrawRotatedTexPolygon(tex_t* tex, int frame, relPoint_t *points, int count, vec_t center, color_t col, double angle,
                             double scale, vec_t texOffset, vec_t texScaleFactor, int depth);
void dqnClearQueue(void);

void dcRotateScreen(double angle, double sceneW, double sceneH);
void dcCreatePoint(vec_t* p, vec_t inp, double vcos, double vsin, double hw, double hh, vec_t cp, int s1, int s2);
void dcDrawText(vec_t pos, color_t col, font_t* font, const char* string, double size);
void dcDrawBackground(tex_t *tex, int frame, int windowW, int windowH);
void dcDrawTexture(tex_t *tex, color_t color, int frame, vec_t pos, double angle, double scaleFactor);
void dcDrawLine(vec_t p1, vec_t p2, color_t col);
void dcDrawPolygon(relPoint_t* points, int count, vec_t center, color_t col);
void dcDrawTexPolygon(tex_t* tex, int frame, relPoint_t *points, int count, vec_t center, color_t col, double scale);
void dcDrawRotatedTexPolygon(tex_t* tex, int frame, relPoint_t *points, int count, vec_t center, color_t col, double angle,
                             double scale, vec_t texOffset, vec_t texScaleFactor);

void dcDrawSurface();
void dcDrawPrimitives(void);
void dcBeginDraw(void);
void dcEndDraw(void);
void dcInit();

#endif //ZOMBOID2_DRAWER_H
