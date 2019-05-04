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

#include "objects/menu/object_beetle_spawner.h"
#include "objects/menu/object_menu.h"
#include "objects/main/player/obj_player.h"
#include "objects/main/box/obj_box.h"

#include "../resources/scopes.rlist"

extern font_t* mainFont;

void initPublicObjects(void);
void loadResources();

#endif //ZOMBOID2_TEXLOADER_H
