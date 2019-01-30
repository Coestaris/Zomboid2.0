//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_TEXLOADER_H
#define ZOMBOID2_TEXLOADER_H

#include <stdarg.h>

#include "../lib/texManager.h"
#include "../lib/helpers.h"
#include "../lib/gameScene.h"

#include "objects/main/player/obj_player.h"
#include "objects/main/box/obj_box.h"
#include "objects/main/flashlight/obj_flashlight.h"

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


#define TEXID_BACK_CONCRETE 7

#define SCENEID_MAIN 0

void loadTextures(void);
void initScenes(void);

#endif //ZOMBOID2_TEXLOADER_H
