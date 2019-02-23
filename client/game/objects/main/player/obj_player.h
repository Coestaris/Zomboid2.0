//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_OBJ_TEST_H
#define ZOMBOID2_OBJ_TEST_H

#include "../../../objectInclude.h"

#include "../enemy/obj_enemy.h"
#include "../bullet/obj_bullet.h"
#include "../flashlight/obj_flashlight.h"
#include "../light/obj_light_tracer.h"

#define PLAYER_MOVE_X 2.5
#define PLAYER_MOVE_Y 2.5

#define PLAYER_SHAKE_START 0.6
#define PLAYER_SHAKE_MIN 0.5
#define PLAYER_SHAKE_REDUCTION 0.7

#define PLAYER_LIGHT_ALPHA_START 0.08
#define PLAYER_LIGHT_ALPHA_REDUCTION .85
#define PLAYER_LIGHT_SIZE_START .5
#define PLAYER_LIGHT_SIZE_INCREASE 1.85

#define PLAYER_MAXLIGHTS 3

#define PLAYER_BACKLIGHT_SIZE .5
#define PLAYER_BACKLIGHT_ALPHA .04

typedef struct _playerData {

    long long lastFireFrame;

    int prevAnimationFrame;

    double currLightSize;
    double currLightAlpha;
    double currShake;

    int currentLightsCount;

    gameObject* fireLights[PLAYER_MAXLIGHTS];
    gameObject* backLight;
    gameObject* flashlight;

    int enabledFlashLight;

} playerData;

void player_event_keyPressed(gameObject* this, void* data);
void player_init(gameObject* object);
void player_event_update(gameObject *object, void *data);
gameObject* createPlayer();

#endif //ZOMBOID2_OBJ_TEST_H
