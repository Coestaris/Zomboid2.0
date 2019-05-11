//
// Created by maxim on 1/24/19.
//

#include "helpers.h"

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

double randRange(double a, double b)
{
    if (a == b) return a;

    double min = a > b ? b : a;
    double max = a > b ? a : b;

    double scale = random() / (float) RAND_MAX; /* [0, 1.0] */

    return min + scale * (max - min);
}

inline double twoPointsAngle(vec_t p1, vec_t p2)
{
    return atan2(p1.y - p2.y, p1.x - p2.x) + M_PI;
}

double toRad(double angle)
{
    return (angle / 360.0) * M_2_PI;
}

double toDeg(double angle)
{
    return (angle / M_2_PI) * 360.0;
}

double distance(vec_t p1, vec_t p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
