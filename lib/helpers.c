//
// Created by maxim on 1/24/19.
//

#include "helpers.h"
#include "eventfuncs.h"

int fileExists(const char* filename)
{
    FILE *f = fopen(filename,"rb");

    if (f == 0) {
        return 0;
    };

    fclose(f);
    return 1;
}

double randRange(double a, double b)
{
    if(a == b) return a;

    double min = a > b ? b : a;
    double max = a > b ? a : b;

    double scale = rand() / (float) RAND_MAX; /* [0, 1.0] */

    return min + scale * ( max - min );
}

inline double toPointsAngle(double x1, double y1, double x2, double y2)
{
    return atan2(y1 - y2, x1 - x2) + M_PI;
}

double toRad(double angle)
{
    return (angle / 360.0) * M_2_PI;
}

double toDeg(double angle)
{
    return (angle / M_2_PI) * 360.0;
}

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
        createPoint(
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


void loadTexture(const char* fn, int id, int scope, int cX, int cY, int isBg)
{
    if(texmGetID(id)) {
        printf("Error while loading texture %i. Texture with same ID alreay exists", id);
        exit(1);
    }

    if(fileExists(fn)) {
        texmPush(createTex(fn, id, scope, cX, cY, isBg));
    } else {
        printf("Error while loading texture %i. Unable to reach file \"%s\"", id, fn);
        exit(1);
    }
}

void loadAnimation(int framesCount, int id, int scope, int cX, int cY, ...)
{
    if(texmGetID(id)) {
        printf("Error while loading animation %i. Texture with same ID alreay exists", id);
        exit(1);
    }

    va_list args;
    va_start(args, cY);

    const char** fileNames = malloc(sizeof(const char*) * framesCount);
    for(int i = 0; i < framesCount; i++) {
        const char* fn = va_arg(args, const char* );
        if(!fileExists(fn))
        {
            printf("Error while loading animation %i (frame %i of %i). Unable to reach file \"%s\"",
                   id, i + 1, framesCount, fn);
            exit(1);
        }
        fileNames[i] = fn;
    }
    texmPush(createAnimation(fileNames, framesCount, id, scope, cX, cY));
}
