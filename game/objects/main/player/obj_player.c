//
// Created by maxim on 1/23/19.
//

#include "obj_player.h"

double flashlightAlphas[PLAYER_FLASHLIGHTS] = { .03, .025, .015 };
double flashlightSizes [PLAYER_FLASHLIGHTS] = { 1, 1.15, 1.5 };

void player_event_keyPressed(gameObject* this, void* data)
{
    keyboardEvent* ke = data;
    playerData* pd = this->data;

    if(ke->key == 'f') {
        pd->flashLight = !pd->flashLight;
        pd->backLight->drawable = pd->flashLight;

        for (int i = 0; i < PLAYER_FLASHLIGHTS; i++) {
            pd->flashlights[i]->drawable = pd->flashLight;
        }
    } else if(ke->key == 'e') {

        srfDrawTexture(texmGetID(TEXID_BOX), 0, 1, 100, 100, 0, 0);
    } else if(ke->key == 'c') {

        srfClear();
    }
}

void player_init(gameObject* object)
{
    evqSubscribeEvent(object, EVT_Update, player_event_update);
    evqSubscribeEvent(object, EVT_CharKeyUp, player_event_keyPressed);

    playerData* pd = object->data;
    for(int i = 0; i < PLAYER_FLASHLIGHTS; i++) {
        pd->flashlights[i] = createFlashlight(object, flashlightSizes[i], flashlightAlphas[i]);
        scmPushObject(pd->flashlights[i]);
    }

    scmPushObject(pd->backLight);
}

#define FIRE_RATE 5

void addFireLight(playerData* pd, double x, double y)
{
    gameObject* light = createLight(x, y ,pd->currLightSize, pd->currLightAlpha);
    pd->fireLights[pd->currentLightsCount++] = light;
    scmPushObject(light);

    //printf("%i\n", pd->currentLightsCount);
}

void player_event_update(gameObject *object, void *data)
{
    double x, y;
    long long frame = getFrame();

    playerData* pd = object->data;
    relativeCoordinates(&x, &y, object);

    if(object->frame == 0 && pd->prevAnimationFrame != 0)
    {
        rotateScene(0);
        object->animationSpeed = 0;

        for(int i = 0; i < pd->currentLightsCount; i++)
            scmDestroyObject(pd->fireLights[i], true);

        pd->currentLightsCount = 0;

    }

    if(object->frame != 0 && pd->prevAnimationFrame != object->frame)
    {
        pd->currShake *= -1 * PLAYER_SHAKE_REDUCTION;
        rotateScene(randRange(pd->currShake, pd->currShake * PLAYER_SHAKE_MIN));

        pd->currLightAlpha *= PLAYER_LIGHT_ALPHA_REDUCTION;
        pd->currLightSize *= PLAYER_LIGHT_SIZE_INCREASE;

        addFireLight(pd, x, y);
    }

    int mx, my;
    getMousePos(&mx, &my);
    object->angle = toPointsAngle(object->x, object->y, mx, my);

    if(keyPressed('a') || specKeyPressed(GLUT_KEY_LEFT))  object->x -= PLAYER_MOVE_X;
    if(keyPressed('w') || specKeyPressed(GLUT_KEY_UP))    object->y -= PLAYER_MOVE_Y;
    if(keyPressed('s') || specKeyPressed(GLUT_KEY_DOWN))  object->y += PLAYER_MOVE_X;
    if(keyPressed('d') || specKeyPressed(GLUT_KEY_RIGHT)) object->x += PLAYER_MOVE_Y;

    if(getMouseState(MB_LEFT) == MS_PRESSED)
    {
        if(frame - pd->lastFireFrame > FIRE_RATE)
        {
            pd->lastFireFrame = frame;

            object->frame = 0;
            object->animationSpeed = 2;

            pd->currShake = PLAYER_SHAKE_START;
            pd->currLightAlpha = PLAYER_LIGHT_ALPHA_START;
            pd->currLightSize = PLAYER_LIGHT_SIZE_START;
            addFireLight(pd, x, y);

            rotateScene(randRange(pd->currShake, pd->currShake * PLAYER_SHAKE_MIN));

            int shellCaseFrame = (int)(randRange(0, 5));
            srfDrawTexture(texmGetID(TEXID_SHELLCASE), shellCaseFrame,
                    (shellCaseFrame == 0 || shellCaseFrame == 5 ? .5 : 1),
                    (int)(x + randRange(-5, 5)),
                    (int)(y + randRange(-5, 5)),
                    (int)random() % 2, (int)random() % 2);

            scmPushObject(createBullet(x, y, mx, my));
        }
    }

    double dist = distance(x, y, mx, my);

    if(dist < PLAYER_FLASHLIGHT_MINDIST) dist = PLAYER_FLASHLIGHT_MINDIST;
    else if(dist > PLAYER_FLASHLIGHT_MAXDIST) dist = PLAYER_FLASHLIGHT_MAXDIST;

    if(pd->flashLight) {

        for (int i = 0; i < PLAYER_FLASHLIGHTS; i++) {
            pd->flashlights[i]->angle = object->angle;
            pd->flashlights[i]->x =
                    x + (pd->flashlights[i]->cachedTex ? pd->flashlights[i]->cachedTex->width / 2.0 : 0);
            pd->flashlights[i]->y = y;

            flashlightData *fd = pd->flashlights[i]->data;
            pd->flashlights[i]->size = fd->minSize + (dist - PLAYER_FLASHLIGHT_MINDIST) / (PLAYER_FLASHLIGHT_MAXDIST - PLAYER_FLASHLIGHT_MINDIST);
        }

        pd->backLight->x = x;
        pd->backLight->y = y;
    }

    pd->prevAnimationFrame = object->frame;

    dqnDrawText(x + 10, y, 1, 1, 0, 1, GLUT_BITMAP_TIMES_ROMAN_24, "<- player");
    dqnDrawText(mx + 10, my + 10, 1, 1, 0, 1, GLUT_BITMAP_HELVETICA_18, "<- mouse");
}

gameObject* createPlayer()
{
    gameObject* go = object();
    go->data = malloc(sizeof(playerData));
    go->drawable = true;

    playerData* pd = go->data;

    int w, h;
    getWinSize(&w,  &h);

    go->x = w / 2.0;
    go->y = h / 2.0;

    pd->lastFireFrame = getFrame();
    pd->currentLightsCount = 0;
    pd->prevAnimationFrame = 0;
    pd->flashLight = true;
    pd->backLight = createLight(go->x, go->y, PLAYER_BACKLIGHT_SIZE, PLAYER_BACKLIGHT_ALPHA);

    go->texID = TEXID_PLAYER;
    go->animationSpeed = 0;
    go->size = 1;
    go->init = player_init;
    return go;
}