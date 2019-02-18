//
// Created by maxim on 2/5/19.
//

#ifndef ZOMBOID2_OBJ_LIGHT_TRACER_H
#define ZOMBOID2_OBJ_LIGHT_TRACER_H

#include <values.h>

#include "../../../objectInclude.h"

typedef struct _lightTracer_data {
    ltracer_data* data;

} lightTracer_data;

void lightTracer_destroy(gameObject* this);
void lightTracer_init(gameObject* this);
void lightTracer_event_update(gameObject* this, void* data);

gameObject* createAreaLT(vec_t pos, double range, color_t color);
gameObject* createTexturedAreaLT(vec_t pos, double range, color_t color, tex2d* tex, int frame);
gameObject* createDirectLT(vec_t pos, double range, double angle, double width, double backOffset, color_t color, vec_t scaleFactor);
gameObject* createTexturedDirectLT(vec_t pos, double range, double angle, double width, double backOffset, color_t color, tex2d* tex, int frame, vec_t scaleFactor);

void updateEdges(int texId);


#endif //ZOMBOID2_OBJ_LIGHT_TRACER_H
