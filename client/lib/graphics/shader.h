//
// Created by maxim on 3/6/19.
//

#ifndef ZOMBOID2_SHADER_H
#define ZOMBOID2_SHADER_H

#ifndef SHADER_H
#define SHADER_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

#include "../helpers.h"

typedef struct _shader {
    char* vertexPath;
    char* fragmentPath;

    GLint progID;
} shader;

shader* createShader(char* vertexPath, char* fragmentPath);
void freeShader(shader* shader);
int loadShader(shader* shader);

#endif //SHADER_H

#endif //ZOMBOID2_SHADER_H
