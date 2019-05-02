//
// Created by maxim on 3/6/19.
//

#include "shader.h"

shader_t* shaderCreate(char* vertexPath, char* fragmentPath)
{
    shader_t* sh = malloc(sizeof(shader_t));
    sh->fragmentPath = fragmentPath;
    sh->vertexPath = vertexPath;
    sh->progID = 0;

    if(!shaderLoad(sh)) return NULL;

    printf("[shader_t.c]: Loaded shader_t. vertex path: %s, fragment path: %s\n", vertexPath, fragmentPath);

    return sh;
}

void shaderFree(shader_t* sh)
{
    free(sh);
}

void loadShaderSrc(const char *szShaderSrc, GLuint shader)
{
    GLchar *fsStringPtr[1];
    fsStringPtr[0] = (GLchar *)szShaderSrc;

    glShaderSource(shader, 1, (const GLchar **)fsStringPtr, NULL);
}

int loadShaderFile(const char *szFile, GLuint shader)
{
    FILE* f = fopen(szFile, "r");
    if(!f) return 0;

    fseek(f, 0, SEEK_END);

    size_t size = (size_t)ftell(f);
    fseek(f, 0, SEEK_SET);

    char* rawInput = malloc(size + 1);
    memset(rawInput, 0, size + 1);
    fread(rawInput, size, size, f);

    fclose(f);

    loadShaderSrc((const char *)rawInput, shader);

    free(rawInput);

    return 1;
}

int shaderLoad(shader_t* sh)
{
    GLuint vertexShader;
    GLuint fragmentShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if(vertexShader == 0 || fragmentShader == 0) {
        printf("[shader_t.c]: Unable to create shaders\n");
        return 0;
    }

    if(!loadShaderFile(sh->fragmentPath, fragmentShader)) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        printf("[shader_t.c][ERROR]: The fragment shader_t at %s could not be found.\n", sh->fragmentPath);
        return 0;
    }

    if(!loadShaderFile(sh->vertexPath, vertexShader)) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        printf("[shader_t.c][ERROR]: The vertex shader_t at %s could not be found.\n", sh->vertexPath);
        return 0;
    }

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLint testVal;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
        char infoLog[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        printf("[shader_t.c][ERROR]: The vertex shader_t at %s failed to compile with the following error:\n%s\n", sh->vertexPath, infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
        char infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        printf("[shader_t.c][ERROR]: The fragment shader_t at %s failed to compile with the following error:\n%s\n", sh->fragmentPath, infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    sh->progID = glCreateProgram();

    glAttachShader(sh->progID, vertexShader);
    glAttachShader(sh->progID, fragmentShader);

    glLinkProgram(sh->progID);

    glGetProgramiv(sh->progID, GL_LINK_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
        char infoLog[1024];
        glGetProgramInfoLog(sh->progID, 1024, NULL, infoLog);
        printf("[shader_t.c][ERROR]: The programs %s and %s failed to link with the following errors:\n%s\n",
               sh->vertexPath, sh->fragmentPath, infoLog);
        glDeleteProgram(sh->progID);
        return 0;

    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return 1;
}

void shaderUse(shader_t* sh)
{
    glUseProgram(sh->progID);
}

void shaderSetInt(shader_t* sh, const char* name, int value)
{
    glUniform1i(glGetUniformLocation(sh->progID, name), value);
}

void shaderSetFloat(shader_t* sh, const char* name, float value)
{
    glUniform1f(glGetUniformLocation(sh->progID, name), value);
}