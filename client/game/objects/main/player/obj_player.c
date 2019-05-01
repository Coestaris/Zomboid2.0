//
// Created by maxim on 1/23/19.
//

#include "obj_player.h"

void player_event_keyPressed(gameObject* this, void* data)
{
    keyboardEvent* ke = data;
    playerData* pd = this->data;

    if(ke->key == 'f') {
        pd->enabledFlashLight = !pd->enabledFlashLight;
        ((lightTracer_data*)pd->flashlight->data)->data->disabled = !pd->enabledFlashLight;
        pd->flashlight->pos = this->pos;

    } else if(ke->key == 'e') {

        srfDrawTexture(texmGetID(TEXID_BOX), 0, 1, vec(100, 100), 0, 0);
    } else if(ke->key == 'c') {

        srfClear();
    } else if(ke->key == 'q') {

        int w, h;
        getWinSize(&w ,&h);
        scmPushObject(createEnemy(this, vec(randRange(0, w), randRange(0, h))));
    }
}

void player_init(gameObject* object)
{
    evqSubscribeEvent(object, EVT_Update, player_event_update);
    evqSubscribeEvent(object, EVT_CharKeyUp, player_event_keyPressed);

    playerData* pd = object->data;
    scmPushObject(pd->flashlight);
}

void addFireLight(playerData* pd, vec_t pos)
{
    gameObject* light = createLight(pos ,pd->currLightSize, pd->currLightAlpha);
    pd->fireLights[pd->currentLightsCount++] = light;
    scmPushObject(light);
}

void player_event_update(gameObject *object, void *data)
{
    long long frame = getFrame();

    playerData* pd = object->data;

    vec_t rel = relativeCoordinates(object);
    vec_t mpos = getMousePos();

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

        addFireLight(pd, rel);
    }


    object->angle = twoPointsAngle(object->pos, mpos);

    if(keyPressed('a') || specKeyPressed(GLUT_KEY_LEFT))  object->pos.x -= PLAYER_MOVE_X;
    if(keyPressed('w') || specKeyPressed(GLUT_KEY_UP))    object->pos.y -= PLAYER_MOVE_Y;
    if(keyPressed('s') || specKeyPressed(GLUT_KEY_DOWN))  object->pos.y += PLAYER_MOVE_X;
    if(keyPressed('d') || specKeyPressed(GLUT_KEY_RIGHT)) object->pos.x += PLAYER_MOVE_Y;

    if(getMouseState(MB_LEFT) == MS_PRESSED)
    {
        if(frame - pd->lastFireFrame > PLAYER_FIRE_RATE)
        {
            pd->lastFireFrame = frame;

            object->frame = 0;
            object->animationSpeed = 2;

            pd->currShake = PLAYER_SHAKE_START;
            pd->currLightAlpha = PLAYER_LIGHT_ALPHA_START;
            pd->currLightSize = PLAYER_LIGHT_SIZE_START;
            addFireLight(pd, rel);

            rotateScene(randRange(pd->currShake, pd->currShake * PLAYER_SHAKE_MIN));

            int shellCaseFrame = (int)(randRange(0, 5));
            srfDrawTexture(texmGetID(TEXID_SHELLCASE), shellCaseFrame,
                    (shellCaseFrame == 0 || shellCaseFrame == 5 ? .5 : 1),
                    vec(
                        rel.x + randRange(-5, 5),
                        rel.y + randRange(-5, 5)),
                    (int)random() % 2, (int)random() % 2);

            scmPushObject(createBullet(rel, object->angle));
        }
    }

    if(pd->enabledFlashLight) {
        pd->flashlight->angle = object->angle + M_PI;
        pd->flashlight->pos = rel;
    }


    pd->prevAnimationFrame = object->frame;

    ltracerUpdate();
    ltracerDraw(1);
}

gameObject* createPlayer()
{
    gameObject* go = object();
    go->data = malloc(sizeof(playerData));
    go->drawable = true;

    playerData* pd = go->data;

    int w, h;
    getWinSize(&w,  &h);

    go->depth = 2;
    go->pos = vec(w / 2.0, h / 2.0);

    pd->lastFireFrame = getFrame();
    pd->currentLightsCount = 0;
    pd->prevAnimationFrame = 0;
    pd->enabledFlashLight = true;

    pd->flashlight =
            createTexturedDirectLT(go->pos, 800, M_PI_4, 500, 40, color(1, 1, 1, 0.5), texmGetID(TEXID_LIGHT_WIDE), 0, vec(-1.5, 1.5));
            //createDirectLT(go->pos, 400, M_PI_4, 100, 100, color(1, 1, 1, 0.4));
            //createAreaLT(go->pos, 400, color(1, 1, 0.5, 0.2));
            //createTexturedAreaLT(go->pos, 500, color(1, 1, 0.5, 0.2), texmGetID(TEXID_LIGHT), 0);
            //createLight(go->pos, PLAYER_BACKLIGHT_SIZE, PLAYER_BACKLIGHT_ALPHA);

    go->texID = TEXID_PLAYER;
    go->animationSpeed = 0;
    go->size = 1;
    go->onInit = player_init;
    return go;
}