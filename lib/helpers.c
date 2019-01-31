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

    double scale = random() / (float) RAND_MAX; /* [0, 1.0] */

    return min + scale * ( max - min );
}

inline double twoPointsAngle(double x1, double y1, double x2, double y2)
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

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
