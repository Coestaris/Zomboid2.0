//
// Created by maxim on 2/7/19.
//

#ifndef ZOMBOID2_STRUCTS_H
#define ZOMBOID2_STRUCTS_H

#include <math.h>

typedef struct _vec
{
    double x;
    double y;
} vec_t;

typedef struct _color
{
    double r, g, b, a;

} color_t;

color_t color(double r, double g, double b, double a);
vec_t vec(double x, double y);
vec_t vec_add(vec_t a, vec_t b);
vec_t vec_sub(vec_t a, vec_t b);
vec_t vec_mult(vec_t a, double c);
vec_t vec_div(vec_t a, double c);
vec_t vec_mult2(vec_t a, double c1, double c2);
vec_t vec_div2(vec_t a, double c1, double c2);
vec_t vec_normal(vec_t a);
double vec_len(vec_t a);
vec_t vec_normalize(vec_t a);

#endif //ZOMBOID2_STRUCTS_H
