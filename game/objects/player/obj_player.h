//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_OBJ_TEST_H
#define ZOMBOID2_OBJ_TEST_H

#include "../../objectInclude.h"
#include "../bullet/obj_bullet.h"

#define PLAYER_MOVE_X 2.5
#define PLAYER_MOVE_Y 2.5

#define PLAYER_SHAKE_START 0.6
#define PLAYER_SHAKE_MIN 0.5
#define PLAYER_SHAKE_REDUCTION 0.7

#define PLAYER_LIGHT_ALPHA_START 0.03
#define PLAYER_LIGHT_ALPHA_REDUCTION 0.85
#define PLAYER_LIGHT_SIZE_START 1
#define PLAYER_LIGHT_SIZE_INCREASE 2.1

#define PLAYER_MAXLIGHTS 10

typedef struct {
    long long lastFireFrame;

    int prevAnimationFrame;

    double currLightSize;
    double currLightAlpha;
    double currShake;

    int currentLightsCount;

    gameObject* fireLights[PLAYER_MAXLIGHTS];

} playerData;

void player_init(gameObject* object);
void player_event_update(gameObject *object, void *data);
gameObject* createPlayer();

#endif //ZOMBOID2_OBJ_TEST_H
