//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_GAMESCENE_H
#define ZOMBOID2_GAMESCENE_H

#include <memory.h>

#include "../resources/texManager.h"
#include "../graphics/drawer.h"

#include "gameobject.h"
#include "eventQueue.h"

#define MAXSCENES 256
#define MAXOBJECTS 1024

#define MAX_SCOPES_TO_LOAD   10
#define MAX_SCOPES_TO_UNLOAD 10

typedef struct _gameScene {

    int backgroundTexId;
    tex2d* cachedBack;

    gameObject** startupObjects;
    int startupObjectsArrLen;
    int startupObjectsCount;

    int scope;
    int id;

    int scopesToLoad  [MAX_SCOPES_TO_LOAD  ];
    int scopesToLoadCount;

    int scopesToUnload[MAX_SCOPES_TO_UNLOAD];
    int scopesToUnloadCount;

    void (*onLoad)(struct _gameScene* scene);

    int destroyObjects;
    int freeObjects;

} gameScene;

typedef struct _publicObject {
    int id;
    gameObject* (*init)();

} publicObject;

gameObject** scmGetObjects(int *count);
gameScene* scmGetActiveScene();
int scmGetObjectsCount(void);

int scmHasObject(gameObject *object);
void scmPushObject(gameObject *object);
void scmDestroyObject(gameObject *object, int free);
void scmDestroyAllObjects(int free);


void scmPushPublicObject(int id, gameObject* (*init)());
void scmPushScene(gameScene *scene);
void scmLoadScene(int id);
gameScene* scmGetScene(int id);
publicObject* scmGetPublicObject(int id);

gameScene* createScene(int id, int scope);

void scmAddScopeToLoad(gameScene* scene, int scope);
void scmAddScopeToUnload(gameScene* scene, int scope);
void scmAddStartupObject(gameScene *scene, gameObject *object);

#endif //ZOMBOID2_GAMESCENE_H
