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

typedef struct {
    const char** fns;
    GLuint* textureIds;

    int id;
    int scope;

    int framesCount;

    int centerX;
    int centerY;

    int width;
    int height;
} tex2d;

tex2d* createTex(const char* fn, int uid, int scope, int centerX, int centerY);

tex2d* createAnimation(int framesCount, int uid, int centerX, int centerY, int scope, ...);

void freeOGlTex(tex2d* tex);
void freeTex(tex2d* tex);

int texSize(const char* filename, int* w, int* h);
void loadTex(tex2d* tex);

#endif //ZOMBOID2_TEX_H
