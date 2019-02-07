//
// Created by maxim on 2/7/19.
//

#ifndef ZOMBOID2_STRUCTS_H
#define ZOMBOID2_STRUCTS_H

typedef struct _vec {
    double x;
    double y;
} vec_t;

typedef struct _color {
    double r, g, b, a;

} color_t;

color_t color(double r, double  g, double b, double  a);
vec_t vec(double x, double y);

#endif //ZOMBOID2_STRUCTS_H
