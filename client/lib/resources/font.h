//
// Created by maxim on 5/2/19.
//

#ifndef ZOMBOID2_FONT_H
#define ZOMBOID2_FONT_H

#include <GL/gl.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <malloc.h>

#include "../helpers.h"
#include "../structs.h"

typedef struct _fontCharacter {

    // ID handle of the glyph texture
    GLuint textureID;

    // Size of glyph
    vec_t size;

    // Offset from baseline to left/top of glyph
    vec_t bearing;

    // Offset to advance to next glyph
    GLuint advance;

} font_character_t;

typedef struct _font {
    char* filename;
    uint8_t startIndex;
    uint8_t endIndex;
    font_character_t* chars;

    GLint VAO, VBO;

} font_t;

font_t* fontLoad(char* filename, int penSize, uint8_t startIndex, uint8_t endIndex);
void fontFree(font_t* f);

void fontsInit(void);

#endif //ZOMBOID2_FONT_H
