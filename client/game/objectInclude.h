//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_OBJECTINCLUDE_H
#define ZOMBOID2_OBJECTINCLUDE_H

#define allocData(type, object, var) object->data = malloc(sizeof(type)); type* var = object->data;

#include "../resources/scopes.rlist"
#include "../lib/gameLogic/gameObject.h"
#include "../lib/gameLogic/eventQueue.h"
#include "../lib/gameLogic/eventFuncs.h"
#include "../lib/graphics/surface.h"
#include "../lib/menu/composer.h"
#include "../lib/ltracer/ltracer.h"
#include "../lib/helpers.h"

extern font_t* hudFont;
extern font_t* mainFont;

#endif //ZOMBOID2_OBJECTINCLUDE_H
