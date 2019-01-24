//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_TEXLOADER_H
#define ZOMBOID2_TEXLOADER_H

#include "../lib/texManager.h"
#include "../lib/helpers.h"
#include "../lib/gameScene.h"

#include "objects/obj_player.h"

#define TEXSCOPE_MAIN 0

#define TEXID_PLAYER 1
#define TEXID_BULLET 2

#define SCENEID_MAIN 0

void loadTexture(const char* fn, int id, int scope);
void loadTextures(void);

void initScenes(void);

#endif //ZOMBOID2_TEXLOADER_H
