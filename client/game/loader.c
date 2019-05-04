//
// Created by maxim on 1/24/19.
//

#include "loader.h"

font_t* mainFont;

void initPublicObjects(void)
{
    scmPushPublicObject(OBJECT_PLAYER, createPlayer);
    scmPushPublicObject(OBJECT_BOX, createBox);
    scmPushPublicObject(OBJECT_MENU, createMenu);
    scmPushPublicObject(OBJECT_MENU_SPAWNER, createMenuBeetleSpawner);
}

void loadResources()
{
    mainFont = fontLoad("../resources/fonts/arial.ttf", 64, 20, 128);
    if(mainFont == NULL) exit(1);
}