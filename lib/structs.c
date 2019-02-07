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