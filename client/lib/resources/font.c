//
// Created by maxim on 5/2/19.
//

#include "font.h"

FT_Library ft;

#define glCheck(s) if((glerror = glGetError()) != GL_NO_ERROR) { printf("[font.c][ERROR]: "s".Gl error: %i\n", glerror); return NULL; }

font_t* fontLoad(char* filename, int penSize, char startIndex, char endIndex)
{
    GLint glerror;
    FT_Face face;
    if (FT_New_Face(ft, filename, 0, &face)) {
        puts("[font_t.c][ERROR]: Failed to load font_t");
        return NULL;
    }


    if(FT_Set_Pixel_Sizes(face, penSize, 0)) {
        puts("[font_t.c][ERROR]: Failed set pixel sizes");
        return NULL;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glCheck("Unable to disable pixel alignment")

    font_t* f = malloc(sizeof(font_t));
    f->chars = malloc(sizeof(font_character_t) * (endIndex - startIndex + 1));
    f->endIndex = endIndex;
    f->startIndex = startIndex;
    f->filename = filename;

    for (GLubyte c = startIndex; c < endIndex; c++)
    {
        int errorCode = FT_Load_Char(face, c, FT_LOAD_RENDER);
        if (errorCode)
        {
            printf("[font_t.c][ERROR]: Failed to load %i Glyph. Error code: %i\n", c, errorCode);
            return NULL;
        }

        GLuint texture;

        glGenTextures(1, &texture);
        glCheck("Unable to generate texture")

        glBindTexture(GL_TEXTURE_2D, texture);
        glCheck("Unable to bind texture")

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glCheck("Unable fill texture data")

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glCheck("Unable to set texture attribute: wrap_s")

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glCheck("Unable to set texture attribute: wrap_t")

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glCheck("Unable to set texture attribute: min_filt")

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glCheck("Unable to set texture attribute: mag_filt")

        font_character_t ch =
        {
                texture,
                { face->glyph->bitmap.width, face->glyph->bitmap.rows },
                { face->glyph->bitmap_left, face->glyph->bitmap_top },
                face->glyph->advance.x
        };
        f->chars[c - startIndex] = ch;
    }

    return f;
}

void fontFree(font_t* f)
{
    free(f->chars);
    free(f);
}

void fontsInit(void)
{
    if (FT_Init_FreeType(&ft)) {
        puts("[font_t.c][ERROR]: Could not init FreeType Library");
        exit(1);
    }
}