//
// Created by maxim on 1/23/19.
//

#include "obj_player.h"

void player_init(gameObject* object)
{
    subscribeEvent(object, EVT_Update, player_event_update);
}

#define FIRE_RATE 5

void addFireLight(playerData* pd, double x, double y)
{
    gameObject* light = createLight(x, y ,pd->currLightSize, pd->currLightAlpha);
    pd->fireLights[pd->currentLightsCount++] = light;
    pushObject(light);

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
            destroyObject(pd->fireLights[i], true);

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

            pushObject(createBullet(x, y, mx, my));
        }
    }

    pd->prevAnimationFrame = object->frame;
}

gameObject* createPlayer()
{
    gameObject* go = object();
    go->data = malloc(sizeof(playerData));
    ((playerData*)go->data)->lastFireFrame = getFrame();

    go->drawable = true;

    int w, h;
    getWinSize(&w,  &h);

    go->x = w / 2.0;
    go->y = h / 2.0;

    go->texID = TEXID_PLAYER;
    go->animationSpeed = 0;
    go->size = 1;
    go->init = player_init;
    return go;
}