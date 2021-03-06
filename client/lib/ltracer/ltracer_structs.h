//
// Created by maxim on 2/17/19.
//

#ifndef ZOMBOID2_LTRACER_STRUCTS_H
#define ZOMBOID2_LTRACER_STRUCTS_H

#include "../resources/tex.h"
#include "../graphics/drawer.h"

typedef struct _ltracer_data
{

    vec_t pos;
    double angle;
    int disabled;

    relPoint_t* points;
    int pointsCount;

    int type;

    color_t color;

    double range;

    double width;
    double angleRange;
    vec_t scaleFactor;

    int textured;
    tex_t* tex;
    int frame;

    double backOffset;

} ltracer_data_t;


typedef struct _ltracer_edge
{
    int id;
    vec_t a, b, c, d;

} ltracer_edge_t;


//#define LTRACER_DRAW_RAYS
//#define LTRACER_DRAW_EDGES

#endif //ZOMBOID2_LTRACER_STRUCTS_H
