//
// Created by maxim on 1/24/19.
//

#include "helpers.h"

void createRotatedPoint(vec_t* p, vec_t inp, double vcos, double vsin, double hw, double hh, vec_t cp, int s1, int s2)
{
    inp.x += hw * s1;
    inp.y += hh * s2;

    p->x = inp.x * vcos - inp.y * vsin - cp.x * (vcos - 1) + cp.y * vsin;
    p->y = inp.x * vsin + inp.y * vcos - cp.y * (vcos - 1) - cp.x * vsin;
}

int fileExists(const char* filename)
{
    FILE* f = fopen(filename, "rb");

    if (f == 0)
    {
        return 0;
    };

    fclose(f);
    return 1;
}

vec_t randVector(double maxW, double maxH)
{
    return vec(randRange(0, maxW), randRange(0, maxH));
}

color_t randColor(double alpha)
{
    return color(randRange(0, 1), randRange(0, 1), randRange(0, 1), alpha);
}

int randBool()
{
    return rand() % 2;
}

int randIntRange(int a, int b)
{
    if (a == b) return a;

    int min = a > b ? b : a;
    int max = a > b ? a : b;

    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

double randAngle()
{
    return randRange(-M_PI, M_PI);
}

double randRange(double a, double b)
{
    if (a == b) return a;

    double min = a > b ? b : a;
    double max = a > b ? a : b;

    double scale = rand() / (float) RAND_MAX; /* [0, 1.0] */

    return min + scale * (max - min);
}

inline double twoPointsAngle(vec_t p1, vec_t p2)
{
    return atan2(p1.y - p2.y, p1.x - p2.x) + M_PI;
}

double toRad(double angle)
{
    return (angle / 360.0) * M_PI * 2;
}

double toDeg(double angle)
{
    return (angle / (M_PI * 2)) * 360.0;
}

double distance(vec_t p1, vec_t p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
