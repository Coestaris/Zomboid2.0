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

    return min + random() / (RAND_MAX / (max - min + 1) + 1);
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
    createPoint(
            x, y,
            obj->x, obj->y,
            cos(obj->angle),
            sin(obj->angle),
            0, //obj->cachedTex->width / 2.0,
            0, //obj->cachedTex->height / 2.0,
            - obj->cachedTex->centerX + obj->x,
            - obj->cachedTex->centerY + obj->y,
            0, 0);
}