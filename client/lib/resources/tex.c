//
// Created by maxim on 1/22/19.
//

#include "tex.h"
#include "../../../lib/oil/oil.h"

int winW, winH;
tex2d* createTex(char *fn, int uid, int scope, vec_t center, int mode)
{
    tex2d* tex = malloc(sizeof(tex2d));

    tex->textureIds = malloc(sizeof(GLuint) * 1);
    tex->textureIds[0] = 0;
    tex->mode = mode;

    tex->fns = malloc(sizeof(char*));
    tex->fns[0] = fn;

    tex->center = center;
    tex->framesCount = 1;

    tex->id = uid;
    tex->scope = scope;
    tex->VAO = 0;
}

tex2d* createAnimation(char **fileNames, int framesCount, int uid, int scope, vec_t center, int mode)
{
    tex2d* tex = malloc(sizeof(tex2d));
    tex->mode = mode;

    tex->textureIds = malloc(sizeof(GLuint) * framesCount);
    memset(tex->textureIds, 0, sizeof(GLuint) * framesCount);

    tex->center = center;

    tex->fns = fileNames;

    tex->framesCount = framesCount;
    tex->id = uid;
    tex->scope = scope;
    tex->VAO = 0;
}

void freeOGlTex(tex2d* tex)
{
    for(int i = 0; i < tex->framesCount; i++)
        if(tex->textureIds[i]) glDeleteTextures(1, &tex->textureIds[i]);
    memset(tex->textureIds, 0, sizeof(GLuint) * tex->framesCount);
}

void freeTex(tex2d* tex)
{
    free(tex->textureIds);
    free(tex->fns);
    free(tex);
}

void loadTex(tex2d* tex)
{
    int w, h;
    for(int i = 0; i < tex->framesCount; i++)
    {
        texData data;
        data.wrappingMode = tex->mode == TEXMODE_BACKGROUND ? GL_REPEAT : GL_CLAMP_TO_EDGE;
        data.minFilter = GL_LINEAR;
        data.magFilter = GL_LINEAR;

        GLuint id = oilTextureFromPngFile(tex->fns[i], GL_RGBA, OIL_TEX_WRAPPING, &data);
        if(!id)
        {
            printf("[tex.c][ERROR]: Unable to load texture %s\n", tex->fns[i]);
            oilPrintError();
            exit(EXIT_FAILURE);
        }

        w = data.out_width;
        h = data.out_height;

        if(tex->framesCount == 1)
        {
            printf("[tex.c]: Loaded texture \"%s\". W: %i, H: %i, OGlID: %i\n", tex->fns[i], w, h, id);
        }
        else
        {
            printf("[tex.c]: Loaded frame (%i/%i) \"%s\". W: %i, H: %i OGlID: %i\n", i + 1, tex->framesCount, tex->fns[i], w, h, id);
        }
        tex->textureIds[i] = id;

        if(tex->mode == TEXMODE_BACKGROUND)
        {
            GLint VBO, EBO;

            GLfloat vertices[] = {
                 1.0f,  1.0f,  0.0f, (float)winW / w,  0.0f,
                 1.0f, -1.0f,  0.0f, (float)winW / w,  (float)winH / h,
                -1.0f, -1.0f,  0.0f,  0.0f,            (float)winH / h,
                -1.0f,  1.0f,  0.0f,  0.0f,             0,
            };

            GLint indices[] = {
                0, 1, 3,
                1, 2, 3
            };

            glGenVertexArrays(1, &tex->VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(tex->VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
    }

    tex->width = w;
    tex->height = h;
}

void bindTex(tex2d* tex, int frame)
{
    if(!tex)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        assert(frame < tex->framesCount);

        if(tex->mode == TEXMODE_OVERLAY)
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glBlendEquation(GL_ADD);
        }
        else
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        glBindTexture(GL_TEXTURE_2D, tex->textureIds[frame]);
    }
}