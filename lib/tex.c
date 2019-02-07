//
// Created by maxim on 1/22/19.
//

#include <assert.h>
#include "tex.h"

tex2d* createTex(char *fn, int uid, int scope, vec_t center, int mode)
{
    tex2d* tex = malloc(sizeof(tex2d));

    tex->textureIds = malloc(sizeof(GLuint));
    tex->textureIds[0] = 0;
    tex->mode = mode;

    tex->fns = malloc(sizeof(char*));
    tex->fns[0] = fn;

    tex->center = center;
    tex->framesCount = 1;

    tex->id = uid;
    tex->scope = scope;
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

int texSize(char* filename, int* w, int* h)
{
    FILE *f = fopen(filename, "rb");

    fseek(f, 0, SEEK_END);
    long len = ftell(f);

    fseek(f, 0, SEEK_SET);
    if (len < 24)
    {
        fclose(f);
        return 0;
    }

    unsigned char buf[24];
    fread(buf, 1, 24, f);

    if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF && buf[3] == 0xE0 && buf[6] == 'J' && buf[7] == 'F' && buf[8] == 'I' && buf[9] == 'F')
    {
        long pos = 2;
        while (buf[2] == 0xFF)
        {
            if (buf[3] == 0xC0 || buf[3] == 0xC1 || buf[3] == 0xC2 || buf[3] == 0xC3 || buf[3] == 0xC9 || buf[3] == 0xCA || buf[3] == 0xCB) break;
            pos += 2 + (buf[4] << 8) + buf[5];
            if (pos + 12 > len) break;
            fseek(f, pos, SEEK_SET);
            fread(buf + 2, 1, 12, f);
        }
    }
    fclose(f);

    if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF)
    {
        *w = (buf[7] << 8) + buf[8];
        *h = (buf[9] << 8) + buf[10];
        return 1;
    }

    if (buf[0] == 'G' && buf[1] == 'I' && buf[2] == 'F')
    {
        *w = buf[6] + (buf[7] << 8);
        *h = buf[8] + (buf[9] << 8);
        return 1;
    }

    if (
            buf[0] == 0x89 && buf[1] == 'P' && buf[2] == 'N' &&
            buf[3] == 'G' && buf[4] == 0x0D && buf[5] == 0x0A &&
            buf[6] == 0x1A && buf[7] == 0x0A && buf[12] == 'I' &&
            buf[13] == 'H' && buf[14] == 'D' && buf[15] == 'R')
    {
        *w = (buf[16] << 24) + (buf[17] << 16) + (buf[18] << 8) + (buf[19] << 0);
        *h = (buf[20] << 24) + (buf[21] << 16) + (buf[22] << 8) + (buf[23] << 0);

        return 1;
    }

    return 0;
}

void loadTex(tex2d* tex)
{
    int w, h;
    if(!texSize(tex->fns[0], &w, &h)) {
        w = -1;
        h = -1;
    }

    for(int i = 0; i < tex->framesCount; i++)
    {
        GLuint id = SOIL_load_OGL_texture (
                tex->fns[i],
                SOIL_LOAD_RGBA,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
        );

        if(tex->framesCount == 1)
        {
            printf("Loaded texture \"%s\". W: %i, H: %i, OGlID: %i\n", tex->fns[i], w, h, id);
        }
        else
        {
            printf("Loaded frame (%i/%i) \"%s\". W: %i, H: %i OGlID: %i\n", i + 1, tex->framesCount, tex->fns[i], w, h, id);
        }
        tex->textureIds[i] = id;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if(tex->mode == TEXMODE_BACKGROUND)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
    }
    tex->width = w;
    tex->height = h;
}

void bindTex(tex2d* tex, int frame)
{
    if(!tex) glBindTexture(GL_TEXTURE_2D, 0);
    else {

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