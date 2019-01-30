//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_TEX_H
#define ZOMBOID2_TEX_H

#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory.h>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

#define TEXMODE_DEFAULT 0
#define TEXMODE_BACKGROUND 1
#define TEXMODE_OVERLAY 2

typedef struct _tex2d {
    const char** fns;
    int mode;

    GLuint* textureIds;

    int id;
    int scope;

    int framesCount;

    double centerX;
    double centerY;

    int width;
    int height;
} tex2d;

tex2d* createTex(const char *fn, int uid, int scope, double centerX, double centerY, int mode);
tex2d* createAnimation(const char **fileNames, int framesCount, int uid, int scope, double centerX, double centerY,
                       int mode);

void freeOGlTex(tex2d* tex);
void freeTex(tex2d* tex);

int texSize(const char* filename, int* w, int* h);
void loadTex(tex2d* tex);

#endif //ZOMBOID2_TEX_H
