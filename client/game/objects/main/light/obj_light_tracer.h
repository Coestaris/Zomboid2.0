//
// Created by maxim on 2/5/19.
//

#ifndef ZOMBOID2_OBJ_LIGHT_TRACER_H
#define ZOMBOID2_OBJ_LIGHT_TRACER_H

#include <values.h>

#include "../../../objectInclude.h"

typedef struct _lightTracer_data
{
    ltracer_data_t* data;

} lightTracer_data_t;

gameObject_t* createAreaLT(vec_t pos, double range, color_t color);
gameObject_t* createTexturedAreaLT(vec_t pos, double range, color_t color, tex_t* tex, int frame);
gameObject_t* createDirectLT(vec_t pos, double range, double angle, double width, double backOffset, color_t color,
                             vec_t scaleFactor);
gameObject_t* createTexturedDirectLT(vec_t pos, double range, double angle, double width, double backOffset, color_t color,
                       tex_t* tex, int frame, vec_t scaleFactor);

void updateEdges(int texId);


#endif //ZOMBOID2_OBJ_LIGHT_TRACER_H
