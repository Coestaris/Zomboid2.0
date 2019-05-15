//
// Created by h0tw4t3r on 5/14/19.
//

#ifndef ZOMBOID2_NETCONTROLLER_H
#define ZOMBOID2_NETCONTROLLER_H

#include "../../../objectInclude.h"
#include "../../../../../lib/netconf.h"
#include "../../weapon.h"
#include "../enemy/obj_enemy_zombie.h"
#include "../../playerData.h"

extern uint16_t port;

typedef struct _netController_data {

    int wave;
    double completed;

    zsize_t playersCount;

    playerData_t players[MAX_CLIENTS];

} netControllerData_t ;

gameObject_t* createNetController();

#endif //ZOMBOID2_NETCONTROLLER_H
