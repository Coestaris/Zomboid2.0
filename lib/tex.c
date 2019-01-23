//
// Created by maxim on 1/22/19.
//

#include "tex.h"

tex2d* createTex(const char* fn, int uid, int scope)
{
    tex2d* tex = malloc(sizeof(tex2d));

    tex->textureId = 0;
    tex->fn = fn;
    tex->id = uid;
    tex->scope = scope;
}

void freeOGlTex(tex2d* tex)
{
    glDeleteTextures(1, &tex->textureId);
    tex->textureId = 0;
}

void freeTex(tex2d* tex)
{
    free(tex);
}

int fileExists(const char* filename)
{
    FILE *f = fopen(filename,"rb");

    if (f == 0) {
        return 0;
    };

    fclose(f);
    return 1;
}

int texSize(const char* filename, int* w, int* h)
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
    if(!texSize(tex->fn, &w, &h)) {
        w = -1;
        h = -1;
    }

    GLuint id = SOIL_load_OGL_texture
    (
            tex->fn,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    printf("Loaded texture \"%s\". W: %i, H: %i OGlID: %i\n", tex->fn, w, h, id);

    tex->textureId = id;
    tex->width = w;
    tex->height = h;
}
