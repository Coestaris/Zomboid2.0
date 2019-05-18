//
// Created by maxim on 5/2/19.
//

#include "font.h"

FT_Library ft;

#define glFontCheck(s) glCheck("font.c", s)
font_t* fontLoad(char* filename, int penSize, uint8_t startIndex, uint8_t endIndex)
{
    GLint glerror;
    FT_Face face;

    if (!fileExists(filename))
    {
        printf("[font.c][ERROR]: Unable to find file %s", filename);
        return NULL;
    }

    if (FT_New_Face(ft, filename, 0, &face))
    {
        puts("[font.c][ERROR]: Failed to load font");
        return NULL;
    }

    if (FT_Set_Pixel_Sizes(face, penSize, 0))
    {
        puts("[font.c][ERROR]: Failed set pixel sizes");
        return NULL;
    }

    glGetError(); //Reset error flag

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glFontCheck("Unable to disable pixel alignment")

    font_t* f = malloc(sizeof(font_t));
    f->chars = malloc(sizeof(font_character_t) * (endIndex - startIndex + 1));
    f->endIndex = endIndex;
    f->startIndex = startIndex;
    f->filename = filename;

    for (GLubyte c = startIndex; c < endIndex; c++)
    {
        int errorCode = FT_Load_Char(face, c, FT_LOAD_RENDER | FT_LOAD_COLOR);
        if (errorCode)
        {
            printf("[font.c][ERROR]: Failed to load %i Glyph. Error code: %i\n", c, errorCode);
            return NULL;
        }

        GLuint texture;

        glGenTextures(1, &texture);
        glFontCheck("Unable to generate texture")

        glBindTexture(GL_TEXTURE_2D, texture);
        glFontCheck("Unable to bind texture")

        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_ALPHA,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_ALPHA,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        glFontCheck("Unable fill texture data")

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glFontCheck("Unable to set texture attribute: wrap_s")

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFontCheck("Unable to set texture attribute: wrap_t")

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFontCheck("Unable to set texture attribute: min_filt")

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFontCheck("Unable to set texture attribute: mag_filt")

        font_character_t ch =
                {
                        c,
                        texture,
                        {face->glyph->bitmap.width, face->glyph->bitmap.rows},
                        {face->glyph->bitmap_left * 1.2,
                         (face->glyph->metrics.vertBearingY / 28.0) + face->glyph->bitmap_top * 1.2},
                        face->glyph->advance.x
                };
        f->chars[c - startIndex] = ch;
    }

    /*
    glGenVertexArrays(1, &f->VAO);
    glCheck("Unable to generate vertex arrays")

    glGenBuffers(1, &f->VBO);
    glCheck("Unable to generate vertex buffer")

    glBindVertexArray(f->VAO);
    glCheck("Unable to bind vertex array")

    glBindBuffer(GL_ARRAY_BUFFER, f->VBO);
    glCheck("Unable to bind buffer")

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glCheck("Unable to bind fill buffer data")

    glEnableVertexAttribArray(0);
    glCheck("Unable to enable vertex attribute")

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glCheck("Unable to set vertex attribute")

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glCheck("Unable to unbind VBO")

    glBindVertexArray(0);
    glCheck("Unable to unbind VAO")*/

    printf("[font.c]: Loaded font. Font path: %s. In total %i symbols\n", filename, endIndex - startIndex + 1);

    return f;
}

double fontGetStringWidth(char* string, font_t* font, double fontSize)
{
    double w = 0;
    for (size_t i = 0; i < strlen(string); i++)
    {
        font_character_t ch = font->chars[string[i] - font->startIndex];
        w += (ch.advance >> 6) * fontSize;
    }
    return w;
}

double fontGetStringHeight(char* string, font_t* font, double fontSize)
{
    font_character_t ch = font->chars[string[0] - font->startIndex];
    double h = ch.size.y * fontSize;

    for (size_t i = 0; i < strlen(string); i++)
        if (string[i] == '\n') h += ch.size.y * fontSize;

    return h;
}

void fontFree(font_t* f)
{
    free(f->chars);
    free(f);
}

void fontsInit(void)
{
    if (FT_Init_FreeType(&ft))
    {
        puts("[font.c][ERROR]: Could not init FreeType Library");
        exit(1);
    }
}