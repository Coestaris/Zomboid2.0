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

#define PLAYER_LIGHT_ALPHA_START 0.08
#define PLAYER_LIGHT_ALPHA_REDUCTION .85
#define PLAYER_LIGHT_SIZE_START .5
#define PLAYER_LIGHT_SIZE_INCREASE 1.85

#define PLAYER_MAXLIGHTS 10
#define PLAYER_FLASHLIGHTS 3

#define PLAYER_BACKLIGHT_SIZE .5
#define PLAYER_BACKLIGHT_ALPHA .04

#define PLAYER_FLASHLIGHT_MINDIST 100
#define PLAYER_FLASHLIGHT_MAXDIST 500

typedef struct {
    long long lastFireFrame;

    int prevAnimationFrame;

    double currLightSize;
    double currLightAlpha;
    double currShake;

    int currentLightsCount;

    gameObject* fireLights[PLAYER_MAXLIGHTS];
    gameObject* backLight;
    gameObject* flashlights[PLAYER_FLASHLIGHTS];

    int flashLight;

} playerData;

void player_event_keyPressed(gameObject* this, void* data);
void player_init(gameObject* object);
void player_event_update(gameObject *object, void *data);
gameObject* createPlayer();

#endif //ZOMBOID2_OBJ_TEST_H
