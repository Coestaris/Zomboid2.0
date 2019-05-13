//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_TEX_H
#define ZOMBOID2_TEX_H

#define USE_SOIL

#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <assert.h>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include "../structs.h"

#ifdef USE_SOIL
    #include <SOIL/SOIL.h>
#else
    #include "../../../lib/oil/oil.h"
#endif

#define TEXMODE_DEFAULT 0
#define TEXMODE_BACKGROUND 1
#define TEXMODE_OVERLAY 2

typedef struct _tex2d
{
    char** fns;
    int mode;

    GLuint* textureIds;

    int id;
    int scope;

    int framesCount;

    vec_t center;

    int width;
    int height;

    GLint VAO;

} tex_t;

tex_t* createTex(char* fn, int uid, int scope, vec_t center, int mode);
tex_t* createAnimation(char** fileNames, int framesCount, int uid, int scope, vec_t center, int mode);
void freeOGlTex(tex_t* tex);
void freeTex(tex_t* tex);
void bindTex(tex_t* tex, int frame);
void loadTex(tex_t* tex);

#endif //ZOMBOID2_TEX_H
