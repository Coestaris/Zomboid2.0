//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_TEX_H
#define ZOMBOID2_TEX_H

#include <malloc.h>
#include <stdio.h>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

typedef struct {
    const char* fn;

    int id;
    int scope;

    GLuint textureId;

    int width;
    int height;
} tex2d;

tex2d* createTex(const char* fn, int uid, int scope);

void freeOGlTex(tex2d* tex);
void freeTex(tex2d* tex);

int texSize(const char* filename, int* w, int* h);
void loadTex(tex2d* tex);

#endif //ZOMBOID2_TEX_H
