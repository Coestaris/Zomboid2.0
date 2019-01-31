//
// Created by maxim on 1/31/19.
//

#include "gameHelpers.h"


int isInWindowRect(gameObject* object)
{
    int winW, winH, texW = 0, texH = 0;
    getWinSize(&winW, &winH);

    if(object->cachedTex) {
        texW = object->cachedTex->width;
        texH = object->cachedTex->height;
    }

    return object->x < - texW * object->size || object->x > winW + texW * object->size ||
           object->y < - texH * object->size || object->y > winH + texH * object->size;
}

void relativeCoordinates(double* x, double* y, gameObject* obj)
{
    if(!obj->cachedTex) {
        *x = obj->x;
        *y = obj->y;
    } else {
        dcCreatePoint(
                x, y,
                obj->x, obj->y,
                cos(obj->angle),
                sin(obj->angle),
                0, //obj->cachedTex->width / 2.0,
                0, //obj->cachedTex->height / 2.0,
                -obj->cachedTex->centerX + obj->x,
                -obj->cachedTex->centerY + obj->y,
                0, 0);
    }
}


void loadTexture(char* fn, int id, int scope, double cX, double cY, int mode)
{
    if(texmGetID(id)) {
        printf("Error while loading texture %i. Texture with same ID alreay exists", id);
        exit(1);
    }

    if(fileExists(fn)) {
        texmPush(createTex(fn, id, scope, cX, cY, mode));
    } else {
        printf("Error while loading texture %i. Unable to reach file \"%s\"", id, fn);
        exit(1);
    }
}

void loadAnimation(int framesCount, int id, int scope, double cX, double cY, int mode, ...)
{
    if(texmGetID(id)) {
        printf("Error while loading animation %i. Texture with same ID alreay exists", id);
        exit(1);
    }

    va_list args;
    va_start(args, mode);

    char** fileNames = malloc(sizeof(char*) * framesCount);
    for(int i = 0; i < framesCount; i++) {
        char* fn = va_arg(args, char* );
        if(!fileExists(fn))
        {
            printf("Error while loading animation %i (frame %i of %i). Unable to reach file \"%s\"",
                   id, i + 1, framesCount, fn);
            exit(1);
        }
        fileNames[i] = fn;
    }
    texmPush(createAnimation(fileNames, framesCount, id, scope, cX, cY, mode));
}
