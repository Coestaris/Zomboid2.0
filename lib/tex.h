//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_TEX_H
#define ZOMBOID2_TEX_H

#include <malloc.h>
#include <stdio.h>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <SOIL.h>

typedef struct {
    GLuint textureId;

    int width;
    int height;
} tex2d;

void freeTex(tex2d* tex);
int fileexists(char* filename);
int texsize(char* filename, int* w, int* h);
tex2d* loadTex(char* filename);

#endif //ZOMBOID2_TEX_H
