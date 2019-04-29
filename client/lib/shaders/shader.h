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
#include <string.h>

typedef struct _shader
{
    char* vertexPath;
    char* fragmentPath;
    GLint progID;
}
shader;

shader* shaderCreate(char* vertexPath, char* fragmentPath);
void shaderFree(shader* shader);
void shaderSetInt(shader* shader, const char* name, int value);
void shaderSetFloat(shader* shader, const char* name, float value);

#endif //SHADER_H

#endif //ZOMBOID2_SHADER_H
