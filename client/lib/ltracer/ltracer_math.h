//
// Created by maxim on 2/17/19.
//

#ifndef ZOMBOID2_LTRACER_MATH_H
#define ZOMBOID2_LTRACER_MATH_H

#include <math.h>
#include <values.h>

#include "ltracer_structs.h"

#include "../graphics/drawer.h"
#include "../helpers.h"

int ltracer_getIntersection(double rayX1, double rayY1, double rayX2, double rayY2,
                            vec_t seg1, vec_t seg2, double* rx, double* ry, double* dist);

void ltracer_ray_to(ltracer_data* ld, double x1, double y1, double x2, double y2, double angle);

void ltracer_ray_single_to(ltracer_data* ld, vec_t p1, vec_t p2, double mDist);
void ltracer_ray_twice_to(ltracer_data* ld, vec_t p1, vec_t p2, double mDist, double delta);
int ltracer_compare(const void* a, const void* b);
void ltracer_sortPoints(ltracer_data* ld);

void ltracer_updateEdges(ltracer_edge** edges, int count);

#endif //ZOMBOID2_LTRACER_MATH_H
