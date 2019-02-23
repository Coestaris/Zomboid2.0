//
// Created by maxim on 1/26/19.
//

#include "obj_flashlight.h"

gameObject* createFlashlight(gameObject* player, double minSize, double alpha)
{
    gameObject* go = object();
    go->drawable = true;
    go->texID = TEXID_FLASHLIGHT;

    go->data = malloc(sizeof(flashlightData));
    ((flashlightData*)go->data)->minSize = minSize;

    go->pos = player->pos;
    go->size = minSize;
    go->alpha = alpha;

    go->angle = player->angle;

    return go;
}

