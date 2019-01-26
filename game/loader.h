//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_TEXLOADER_H
#define ZOMBOID2_TEXLOADER_H

#include <stdarg.h>

#include "../lib/texManager.h"
#include "../lib/helpers.h"
#include "../lib/gameScene.h"

#include "objects/player/obj_player.h"
#include "objects/box/obj_box.h"
#include "objects/flashlight/obj_flashlight.h"

#define TEXSCOPE_MAIN 0

#define TEXID_PLAYER 1
#define TEXID_BULLET 2
#define TEXID_BOX 3
#define TEXID_SIMPLE_LIGHT 4
#define TEXID_LIGHT 5
#define TEXID_FLASHLIGHT 6

#define TEXID_BACK_CONCRETE 7


#define TEXID_SHELLCASE 8


#define SCENEID_MAIN 0

void loadTextures(void);
void initScenes(void);

#endif //ZOMBOID2_TEXLOADER_H
