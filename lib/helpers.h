//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_HELPERS_H
#define ZOMBOID2_HELPERS_H

#include <stdio.h>
#include <math.h>
#include "structs.h"

#define true 1
#define TRUE 1
#define false 0
#define FALSE 0

double randRange(double a, double b);
int fileExists(const char* filename);

double twoPointsAngle(vec_t p1, vec_t p2);
double distance(vec_t p1, vec_t p2);



double toRad(double angle);
double toDeg(double angle);

#endif //ZOMBOID2_HELPERS_H
