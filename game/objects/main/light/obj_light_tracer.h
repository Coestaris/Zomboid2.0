//
// Created by maxim on 2/5/19.
//

#ifndef ZOMBOID2_OBJ_LIGHT_TRACER_H
#define ZOMBOID2_OBJ_LIGHT_TRACER_H

#include <values.h>

#include "../../../objectInclude.h"

#define LT_AREA 1
#define LT_SPOT 2

typedef struct _lightTracer_data {

    relPoint_t* points;
    int pointsCount;

    int type;

    color_t color;

    double range;
    double angleRange;

    double angle;

    int textured;
    tex2d* tex;
    int frame;

} lightTracer_data;

void lightTracer_init(gameObject* this);
void lightTracer_event_update(gameObject* this, void* data);

gameObject* createAreaLT(vec_t pos, double range, color_t color);
gameObject* createTexturedAreaLT(vec_t pos, double range, color_t color, tex2d* tex, int frame);
gameObject* createDirectLT(vec_t pos, double range, double angle, color_t color);

void updateEdges(int texId);


#endif //ZOMBOID2_OBJ_LIGHT_TRACER_H
