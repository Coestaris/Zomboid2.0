//
// Created by maxim on 1/26/19.
//

#include "surface.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

uint8_t pixelData[SCREEN_HEIGHT][SCREEN_WIDTH][4];

int winW;
int winH;
GLuint surfGLID;

void srfFree()
{
    /*for(int i = 0; i < winW; i++) {
        for(int j = 0; j < winH; j++) {
            free(pixelData[i][j]);
        }
        free(pixelData[i]);
    }
    free(pixelData);
    pixelData = NULL;*/
}

void srfBind()
{
    glBindTexture(GL_TEXTURE_2D, surfGLID);
}

void srfInit(int wW, int wH)
{
    winW = wW;
    winH = wH;

    for(int y = 0; y < SCREEN_HEIGHT; ++y)
        for(int x = 0; x < SCREEN_WIDTH; ++x) {
            pixelData[y][x][0] = pixelData[y][x][1] = pixelData[y][x][2] = 4;
            pixelData[y][x][3] = 0;
        }

    glGenTextures(1, &surfGLID);

    glBindTexture(GL_TEXTURE_2D, surfGLID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pixelData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void srfClear()
{
    for(int y = 0; y < SCREEN_HEIGHT; ++y)
        for(int x = 0; x < SCREEN_WIDTH; ++x) {
            pixelData[y][x][0] = 0;
            pixelData[y][x][1] = 0;
            pixelData[y][x][2] = 0;
            pixelData[y][x][3] = 0;
        }

    glBindTexture(GL_TEXTURE_2D, surfGLID);
    glTexSubImage2D(GL_TEXTURE_2D, 0 ,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pixelData);
}

void getPixel(uint8_t* pixels, int x, int y, int w, int h, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * a)
{
    const int offset = (y * w + x) * 4;
    *r = pixels[offset];
    *g = pixels[offset + 1];
    *b = pixels[offset + 2];
    *a = pixels[offset + 3];
}

void srfDrawTexture(tex2d* tex, int frame, double alpha, int inx, int iny)
{
    GLint width,height;
    glBindTexture(GL_TEXTURE_2D, tex->textureIds[frame]);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    size_t numBytes = width * height * 4U;

    uint8_t  *pixels = (uint8_t*) malloc(numBytes);

    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {

            if(x + inx >= SCREEN_WIDTH || y + iny >= SCREEN_HEIGHT)
                continue;

            uint8_t r, g, b, a;
            getPixel(pixels, x, y, width, height, &r, &g, &b, &a);

            if(a) {

                pixelData[y + iny][x + inx][0] = r;
                pixelData[y + iny][x + inx][1] = g;
                pixelData[y + iny][x + inx][2] = b;
                pixelData[y + iny][x + inx][3] = (uint8_t)(alpha * a);
            }
        }
    }
    free(pixels);

    glBindTexture(GL_TEXTURE_2D, surfGLID);
    glTexSubImage2D(GL_TEXTURE_2D, 0 ,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pixelData);
}