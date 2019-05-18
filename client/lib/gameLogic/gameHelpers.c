//
// Created by maxim on 1/31/19.
//

#include "gameHelpers.h"

int isInObjectRect(gameObject_t* obj, vec_t point)
{
    if (!obj->cachedTex)
    {
        return point.x == obj->pos.x && point.y == obj->pos.y;
    }
    else
    {
        return point.x > obj->pos.x - obj->cachedTex->width / 2.0 * obj->size &&
               point.x < obj->pos.x + obj->cachedTex->width / 2.0 * obj->size &&
               point.y > obj->pos.y - obj->cachedTex->height / 2.0 * obj->size &&
               point.y < obj->pos.y + obj->cachedTex->height / 2.0 * obj->size;
    }
}

int isInWindowExtendedRect(gameObject_t* object, int exW, int exH)
{
    int winW, winH, texW = 0, texH = 0;
    getWinSize(&winW, &winH);

    if (object->cachedTex)
    {
        texW = object->cachedTex->width;
        texH = object->cachedTex->height;
    }

    return object->pos.x < -texW * object->size - exW ||
           object->pos.x > texW * object->size + exW + winW ||
           object->pos.y < -texH * object->size - exH ||
           object->pos.y > texH * object->size + exH + winH;
}

int isInWindowRect(gameObject_t* object)
{
    int winW, winH, texW = 0, texH = 0;
    getWinSize(&winW, &winH);

    if (object->cachedTex)
    {
        texW = object->cachedTex->width;
        texH = object->cachedTex->height;
    }

    return object->pos.x < -texW * object->size ||
           object->pos.x > texW * object->size + winW ||
           object->pos.y < -texH * object->size ||
           object->pos.y > texH * object->size + winH;
}

vec_t relativeCoordinatesEx(tex_t* tex, vec_t pos, double angle)
{
    vec_t result;
    createRotatedPoint(
            &result,
            pos,
            cos(angle),
            sin(angle),
            0,
            0,
            vec(
                    -tex->center.x + pos.x,
                    -tex->center.y + pos.y),
            0, 0);
    return result;
}

vec_t relativeCoordinates(gameObject_t* obj)
{
    if (!obj->cachedTex)
    {
        return obj->pos;
    }
    else
    {
        vec_t result;
        createRotatedPoint(
                &result,
                obj->pos,
                cos(obj->angle),
                sin(obj->angle),
                0,
                0,
                vec(
                        -obj->cachedTex->center.x + obj->pos.x,
                        -obj->cachedTex->center.y + obj->pos.y),
                0, 0);
        return result;
    }
}


void loadTexture(char* fn, int id, int scope, vec_t pos, int mode)
{
    if (texmGetID(id))
    {
        printf("[gameHelpers.c][ERROR]: Error while loading texture %i. Texture with same ID alreay exists", id);
        exit(1);
    }

    if (fileExists(fn))
    {
        texmPush(createTex(fn, id, scope, pos, mode));
    }
    else
    {
        printf("[gameHelpers.c][ERROR]: Error while loading texture %i. Unable to reach file \"%s\"", id, fn);
        exit(1);
    }
}

void loadAnimation(int framesCount, int id, int scope, vec_t pos, int mode, ...)
{
    if (texmGetID(id))
    {
        printf("[gameHelpers.c][ERROR]: Error while loading animation %i. Texture with same ID alreay exists", id);
        exit(1);
    }

    va_list args;
    va_start(args, mode);

    char** fileNames = malloc(sizeof(char*) * framesCount);
    for (int i = 0; i < framesCount; i++)
    {
        char* fn = va_arg(args, char*);
        if (!fileExists(fn))
        {
            printf("[gameHelpers.c][ERROR]: Error while loading animation %i (frame %i of %i). Unable to reach file \"%s\"",
                   id, i + 1, framesCount, fn);
            exit(1);
        }
        fileNames[i] = fn;
    }
    texmPush(createAnimation(fileNames, framesCount, id, scope, pos, mode));
}
