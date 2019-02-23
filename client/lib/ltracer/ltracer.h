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

void ltracer_pushLight(ltracer_data *ld);
void ltracer_removeLight(ltracer_data *ld);

int ltracer_pushEdge(vec_t a, vec_t b, vec_t c, vec_t d);
void ltracer_removeEdge(int edgeId);

void ltracer_update();
void ltracer_draw();

#endif //ZOMBOID2_LTRACER_H
