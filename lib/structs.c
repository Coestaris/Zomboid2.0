//
// Created by maxim on 2/7/19.
//

#include "structs.h"

color_t color(double r, double  g, double b, double  a)
{
    color_t c = {r, g, b, a};
    return c;
}

vec_t vec(double x, double y)
{
    vec_t v = {x, y};
    return v;
}

vec_t vec_add(vec_t a, vec_t b)
{
    return vec(a.x + b.x, a.y + b.y);
}

vec_t vec_sub(vec_t a, vec_t b)
{
    return vec(a.x - b.x, a.y - b.y);
}

vec_t vec_mult(vec_t a, double c)
{
    return vec(a.x * c, a.y * c);
}

vec_t vec_div(vec_t a, double c)
{
    return vec(a.x / c, a.y / c);
}

vec_t vec_mult2(vec_t a, double c1, double c2)
{
    return vec(a.x * c1, a.y * c2);
}

vec_t vec_div2(vec_t a, double c1, double c2)
{
    return vec(a.x / c1, a.y / c2);
}

vec_t vec_normal(vec_t a)
{
    return vec(1, -(a.x * 1) / a.y);
}

double vec_len(vec_t a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

vec_t vec_normalize(vec_t a)
{
    double len = 1 / vec_len(a);
    return vec_mult(a, len);
}