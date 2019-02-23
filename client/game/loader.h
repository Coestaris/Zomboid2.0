//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_TEXLOADER_H
#define ZOMBOID2_TEXLOADER_H

#include <stdarg.h>

#include "../lib/resources/texManager.h"
#include "../lib/gameLogic/gameHelpers.h"
#include "../lib/gameLogic/gameScene.h"

#include "objects/main/player/obj_player.h"
#include "objects/main/box/obj_box.h"


#define TEXSCOPE_MAIN 0

#define TEXID_PLAYER 1
#define TEXID_BULLET 2
#define TEXID_BOX 3
#define TEXID_SIMPLE_LIGHT 4
#define TEXID_LIGHT 5
#define TEXID_FLASHLIGHT 6
#define TEXID_SHELLCASE 8

#define TEXID_ENEMY 9
#define TEXID_ENEMY_LARM 10
#define TEXID_ENEMY_RARM 11
#define TEXID_ENEMY_LARM_D 12
#define TEXID_ENEMY_RARM_D 13
#define TEXID_LIGHT_WIDE 14
#define TEXID_LIGHT_DUO 15

#define TEXID_BACK_CONCRETE 7

#define SCENEID_MAIN 0

#define OBJECT_BOX    1
#define OBJECT_PLAYER 0

void initPublicObjects(void);

#endif //ZOMBOID2_TEXLOADER_H
