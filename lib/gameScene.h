//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_GAMESCENE_H
#define ZOMBOID2_GAMESCENE_H

#include <memory.h>

#include "gameobject.h"
#include "texManager.h"
#include "eventQueue.h"

#define MAXSCENES 256
#define MAXOBJECTS 1024

typedef struct
{
    int backgroundTexId;
    tex2d* cachedBack;

    gameObject** startupObjects;
    int startupObjectsArrLen;
    int startupObjectsCount;

    int scope;
    int id;

} gameScene;

gameObject** scmGetObjects(int *count);
gameScene* scmGetActiveScene();
int scmGetObjectsCount(void);

int scmHasObject(gameObject *object);
void scmPushObject(gameObject *object);
void scmDestroyObject(gameObject *object, int free);
void scmDestroyAllObjects(int free);

void scmPushScene(gameScene *scene);
void scmLoadScene(int id, int loadScope, int destroyObjects, int freeObjects);

gameScene* createScene(int id, int scope);
void scmAddStartupObject(gameScene *scene, gameObject *object);

#endif //ZOMBOID2_GAMESCENE_H
