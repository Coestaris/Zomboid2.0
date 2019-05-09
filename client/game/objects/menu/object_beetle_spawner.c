//
// Created by maxim on 5/4/19.
//

#include "object_beetle_spawner.h"

void mbeetleSpawner_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, mbeetleSpawner_event_update);

    //todo: paint with some surface
}

void mbeetleSpawner_event_update(gameObject_t* this, void* data)
{
    mbeetleSpawnerData_t* sd = this->data;
    int w, h;
    getWinSize(&w, &h);

    long long frame = getFrame();

    if (llabs(sd->lastSpawn - frame) > BEETLE_SPAWN_RATE)
    {
        int dir = (int) randRange(0, 4);
        vec_t pos = vec(0, 0);
        double angle = 0;

        switch (dir)
        {
            case 0: //from top edge
                pos = vec(randRange(0, w), 0);
                angle = randRange(M_PI_4, M_PI - M_PI_4);
                break;
            case 1: //from right edge
                pos = vec(w, randRange(0, h));
                angle = randRange(M_PI_2 + M_PI_4, 3 * M_PI_2 - M_PI_4);
                break;
            case 2: //from bottom edge
                pos = vec(randRange(0, w), h);
                angle = randRange(M_PI_4 + M_PI, 2 * M_PI - M_PI_4);
                break;
            case 3: //from left edge
                pos = vec(0, randRange(0, h));
                angle = randRange(M_PI_4 - M_PI_2, M_PI - M_PI_4 - M_PI_2);
                break;
        }

        scmPushObject(createMenuBeetle(pos, angle, BEETLE_SPEED));
        sd->lastSpawn = frame;
    }
}

gameObject_t* createMenuBeetleSpawner()
{
    gameObject_t* this = object();
    this->onInit = mbeetleSpawner_init;
    this->data = malloc(sizeof(mbeetleSpawnerData_t));
    return this;
}