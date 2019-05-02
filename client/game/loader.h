//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_TEXLOADER_H
#define ZOMBOID2_TEXLOADER_H

#include <stdlib.h>

#include "../lib/resources/font.h"
#include "../lib/resources/texManager.h"
#include "../lib/gameLogic/gameHelpers.h"
#include "../lib/gameLogic/gameScene.h"

#include "objects/menu/object_menu.h"
#include "objects/main/player/obj_player.h"
#include "objects/main/box/obj_box.h"

#define SCENEID_MAIN_MENU 0
#define SCENEID_GAME 1


#define TEXSCOPE_MAIN_MENU 0
#define TEXSCOPE_GAME 1
#define TEXSCOPE_MM_GEN 2


// ====== TEXTURE IDS ======
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

#define TEXID_MENU_BUTTON_SMALL 16
#define TEXID_MENU_BUTTON 17
#define TEXID_MENU_INDBL 18
#define TEXID_MENU_OUT 19

// ===== OBJECTS ======
#define OBJECT_PLAYER 0
#define OBJECT_BOX    1
#define OBJECT_MENU   2

extern font_t* mainFont;

void initPublicObjects(void);
void loadResources();

#endif //ZOMBOID2_TEXLOADER_H
