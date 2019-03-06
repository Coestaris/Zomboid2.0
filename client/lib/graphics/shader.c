//
// Created by maxim on 3/6/19.
//

#include "shader.h"

//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wimplicit-function-declaration"

shader* createShader(char* vertexPath, char* fragmentPath)
{
    shader* sh = malloc(sizeof(shader));
    sh->fragmentPath = fragmentPath;
    sh->vertexPath = vertexPath;
    sh->progID = 0;
    return sh;
}

void freeShader(shader* sh)
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
    if(!f) return false;

    fseek(f, 0, SEEK_END);

    size_t size = (size_t)ftell(f);
    fseek(f, 0, SEEK_SET);

    char* rawInput = malloc(size + 1);
    memset(rawInput, 0, size + 1);
    fread(rawInput, size, size, f);

    fclose(f);

    loadShaderSrc((const char *)rawInput, shader);

    free(rawInput);

    return true;
}

int loadShader(shader* sh)
{
    GLuint vertexShader;
    GLuint fragmentShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if(vertexShader == 0 || fragmentShader == 0) {
        printf("Error: Unable to create shaders\n");
        return false;
    }
    if(!loadShaderFile(sh->fragmentPath, fragmentShader)) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        printf("Error: The fragment shader at %s could not be found.\n", sh->fragmentPath);
        return false;
    }
    else {
        printf("Fragment Shader was loaded successfully\n");
    }

    if(!loadShaderFile(sh->vertexPath, vertexShader)) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        printf("Error: The vertex shader at %s could not be found.\n", sh->vertexPath);
        return false;
    }
    else {
        printf("Vertex Shader was loaded successfully\n");
    }

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLint testVal;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
        char infoLog[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        printf("Error: The vertex shader at %s failed to compile with the following error:\n%s\n", sh->vertexPath, infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;

    } else {
        printf("Vertex Shader compiled successfully\n");
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
        char infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        printf("The fragment shader at %s failed to compile with the following error:\n%s\n", sh->fragmentPath, infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;

    } else {
        printf("Fragment Shader compiled successfully\n");
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
        printf("The programs %s and %s failed to link with the following errors:\n%s\n",
                sh->vertexPath, sh->fragmentPath, infoLog);
        glDeleteProgram(sh->progID);
        return false;

    } else {
        fprintf(stderr,"Shaders linked successfully\n");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

#pragma clang diagnostic pop