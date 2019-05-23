//
// Created by maxim on 5/13/19.
//

#ifndef ZOMBOID2_OBJ_EXPLOSION_H
#define ZOMBOID2_OBJ_EXPLOSION_H

#include "../../../objectInclude.h"


#include "../enemy/obj_enemy_tic.h"
#include "../enemy/obj_enemy_body.h"
#include "../enemy/obj_enemy_zombie.h"
#include "../enemy/obj_enemy_slug.h"
#include "../enemy/obj_enemy_ghost.h"
#include "../enemy/obj_enemy_slicer.h"

typedef struct _explosionData {
    double frame;

} explosionData_t;

gameObject_t* createExplosion(vec_t pos);

#endif //ZOMBOID2_OBJ_EXPLOSION_H
