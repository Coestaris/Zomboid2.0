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
#include "../structs.h"

#define TEXMODE_DEFAULT 0
#define TEXMODE_BACKGROUND 1
#define TEXMODE_OVERLAY 2

typedef struct _tex2d {
    char** fns;
    int mode;

    GLuint* textureIds;

    int id;
    int scope;

    int framesCount;

    vec_t center;

    int width;
    int height;
} tex2d;

tex2d* createTex(char *fn, int uid, int scope, vec_t center, int mode);
tex2d* createAnimation(char **fileNames, int framesCount, int uid, int scope, vec_t center, int mode);

void freeOGlTex(tex2d* tex);
void freeTex(tex2d* tex);
void bindTex(tex2d* tex, int frame);

int texSize(char* filename, int* w, int* h);
void loadTex(tex2d* tex);

#endif //ZOMBOID2_TEX_H
