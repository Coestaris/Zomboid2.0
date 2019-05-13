//
// Created by maxim on 1/22/19.
//

#include "tex.h"

tex_t* createTex(char* fn, int uid, int scope, vec_t center, int mode)
{
    tex_t* tex = malloc(sizeof(tex_t));

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

tex_t* createAnimation(char** fileNames, int framesCount, int uid, int scope, vec_t center, int mode)
{
    tex_t* tex = malloc(sizeof(tex_t));
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

void freeOGlTex(tex_t* tex)
{
    for (int i = 0; i < tex->framesCount; i++)
        if (tex->textureIds[i]) glDeleteTextures(1, &tex->textureIds[i]);
    memset(tex->textureIds, 0, sizeof(GLuint) * tex->framesCount);
}

void freeTex(tex_t* tex)
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
    fclose(f);

    *w = (buf[16] << 24) + (buf[17] << 16) + (buf[18] << 8) + (buf[19] << 0);
    *h = (buf[20] << 24) + (buf[21] << 16) + (buf[22] << 8) + (buf[23] << 0);

    return 1;
}


void loadTex(tex_t* tex)
{
    int w, h;
    for (int i = 0; i < tex->framesCount; i++)
    {
#ifdef USE_SOIL
        GLuint id = SOIL_load_OGL_texture
        (
                tex->fns[i],
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA
        );

        if(id == 0) {
            printf("[tex.c][ERROR]: Unable to load texture %s", tex->fns[i]);
            exit(1);
        }


        if(!texSize(tex->fns[i], &w, &h)) {
            printf("[tex.c][ERROR]: Unable to get texture size of %s", tex->fns[i]);
            exit(1);
        }

        glBindTexture(GL_TEXTURE_2D, id);
        /*glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
*/
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //1glGenerateMipmap(GL_TEXTURE_2D);

#else
        texData data;
        data.wrappingMode = tex->mode == TEXMODE_BACKGROUND ? GL_REPEAT : GL_CLAMP_TO_EDGE;
        data.minFilter = GL_LINEAR;
        data.magFilter = GL_LINEAR;
        data.flipY = 1;

        GLuint id = oilTextureFromPngFile(tex->fns[i], GL_RGBA,
                                          OIL_TEX_WRAPPING | OIL_TEX_MIN | OIL_TEX_MAG | OIL_TEX_FLIPY,
                                          &data);
        if (!id)
        {
            printf("[tex.c][ERROR]: Unable to load texture %s\n", tex->fns[i]);
            oilPrintError();
            exit(EXIT_FAILURE);
        }

        w = data.out_width;
        h = data.out_height;
#endif

        if (tex->framesCount == 1)
        {
            printf("[tex.c]: Loaded texture \"%s\". W: %i, H: %i, OGlID: %i\n", tex->fns[i], w, h, id);
        }
        else
        {
            printf("[tex.c]: Loaded frame (%i/%i) \"%s\". W: %i, H: %i OGlID: %i\n", i + 1, tex->framesCount,
                   tex->fns[i], w, h, id);
        }
        tex->textureIds[i] = id;

#ifdef USE_SOIL
        if (tex->mode == TEXMODE_BACKGROUND)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
#endif
    }

    tex->width = w;
    tex->height = h;
}

void bindTex(tex_t* tex, int frame)
{
    if (!tex)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        assert(frame >= 0 && frame < tex->framesCount);

        if (tex->mode == TEXMODE_OVERLAY)
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