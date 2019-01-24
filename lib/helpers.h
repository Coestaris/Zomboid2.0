//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_HELPERS_H
#define ZOMBOID2_HELPERS_H

#include <stdio.h>
#include <math.h>

#define true 1
#define TRUE 1
#define false 0
#define FALSE 0

int fileExists(const char* filename);
double toPointsAngle(double x1, double y1, double x2, double y2);

double toRad(double angle);
double toDeg(double angle);

#endif //ZOMBOID2_HELPERS_H
