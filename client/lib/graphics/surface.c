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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, surfGLID);
}
/*

void free_data(uint8_t ***data, size_t xlen, size_t ylen)
{
    size_t i, j;

    for (i=0; i < xlen; ++i) {
        if (data[i] != NULL) {
            for (j=0; j < ylen; ++j)
                free(data[i][j]);
            free(data[i]);
        }
    }
    free(data);
}

uint8_t  ***alloc_data(size_t xlen, size_t ylen, size_t zlen)
{
    uint8_t  ***p;
    size_t i, j;

    if ((p = malloc(xlen * sizeof *p)) == NULL) {
        perror("malloc 1");
        return NULL;
    }

    for (i=0; i < xlen; ++i)
        p[i] = NULL;

    for (i=0; i < xlen; ++i)
        if ((p[i] = malloc(ylen * sizeof *p[i])) == NULL) {
            perror("malloc 2");
            free_data(p, xlen, ylen);
            return NULL;
        }

    for (i=0; i < xlen; ++i)
        for (j=0; j < ylen; ++j)
            p[i][j] = NULL;

    for (i=0; i < xlen; ++i)
        for (j=0; j < ylen; ++j)
            if ((p[i][j] = malloc(zlen * sizeof *p[i][j])) == NULL) {
                perror("malloc 3");
                free_data(p, xlen, ylen);
                return NULL;
            }

    return p;
}
*/

void srfInit(int wW, int wH)
{
    winW = wW;
    winH = wH;
/*
    if(!(pixelData = alloc_data((size_t)SCREEN_HEIGHT, (size_t)SCREEN_WIDTH, 4))) {
        puts("Unable allocate data to surface");
        exit(1);
    }*/


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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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

uint8_t clip(double a)
{
    if(a >= 255) return 255;
    else if(a <= 0) return 0;
    else return (uint8_t)a;
}

void srfDrawTexture(tex2d* tex, int frame, double alpha, vec_t pos, int flipX, int flipY)
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

            uint8_t r, g, b, a;
            getPixel(pixels, x, y, width, height, &r, &g, &b, &a);

            if(a) {

                int xPos = (int)(flipX ? (width - x + pos.x) : (x + pos.x));
                int yPos = (int)(flipY ? (height- y + pos.y) : (y + pos.y));

                if(xPos >= SCREEN_WIDTH || yPos >= SCREEN_HEIGHT || xPos <= 0 || yPos <= 0)
                    continue;

                if(tex->mode == TEXMODE_OVERLAY) {

                    double oldAlpha = pixelData[yPos][xPos][3] / 255.0 * alpha;

                    pixelData[yPos][xPos][0] = clip((oldAlpha * pixelData[yPos][xPos][0] + (1 - oldAlpha) * r));
                    pixelData[yPos][xPos][1] = clip((oldAlpha * pixelData[yPos][xPos][1] + (1 - oldAlpha) * g));
                    pixelData[yPos][xPos][2] = clip((oldAlpha * pixelData[yPos][xPos][2] + (1 - oldAlpha) * b));
                    pixelData[yPos][xPos][3] = clip((oldAlpha * pixelData[yPos][xPos][3] + (1 - oldAlpha) * a));


                } else {

                    pixelData[yPos][xPos][0] = clip(r);
                    pixelData[yPos][xPos][1] = clip(g);
                    pixelData[yPos][xPos][2] = clip(b);
                    pixelData[yPos][xPos][3] = clip(a * alpha);
                }
            }
        }
    }
    free(pixels);

    glBindTexture(GL_TEXTURE_2D, surfGLID);
    glTexSubImage2D(GL_TEXTURE_2D, 0 ,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pixelData);
}