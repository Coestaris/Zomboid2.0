//
// Created by maxim on 2/5/19.
//

#ifndef ZOMBOID2_OBJ_LIGHT_TRACER_H
#define ZOMBOID2_OBJ_LIGHT_TRACER_H

#include "../../../objectInclude.h"

typedef struct _lightTracer_data {
    gameObject* lightSource;

} lightTracer_data;

void lightTracer_init(gameObject* this);
void lightTracer_event_update(gameObject* this, void* data);
gameObject* createLightTracer(gameObject* ltSource);

#endif //ZOMBOID2_OBJ_LIGHT_TRACER_H
