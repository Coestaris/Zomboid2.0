//
// Created by maxim on 2/17/19.
//

#ifndef ZOMBOID2_LTRACER_H
#define ZOMBOID2_LTRACER_H

#include "../graphics/drawer.h"
#include "../structs.h"

#include "ltracer_structs.h"
#include "ltracer_math.h"

#define LT_AREA 1
#define LT_SPOT 2

void ltracerPushLight(ltracer_data *ld);
void ltracerRemoveLight(ltracer_data *ld);

ltracer_edge* ltracerPushEdge(vec_t a, vec_t b, vec_t c, vec_t d);
void ltracerRemoveEdge(int edgeId);

void ltracerUpdate();
void ltracerDraw(int depth);

#endif //ZOMBOID2_LTRACER_H
