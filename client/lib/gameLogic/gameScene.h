//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_GAMESCENE_H
#define ZOMBOID2_GAMESCENE_H

#include <memory.h>

#include "../resources/texManager.h"
#include "../graphics/drawer.h"
#include "../ltracer/ltracer.h"

#include "gameobject.h"
#include "eventQueue.h"

#define MAXSCENES 256
#define MAXOBJECTS 1024

#define MAX_SCOPES_TO_LOAD   10
#define MAX_SCOPES_TO_UNLOAD 10

typedef struct _gameScene {

    int ltracerDepth;
    int useLtracer;

    int backgroundTexId;
    tex_t* cachedBack;

    gameObject_t** startupObjects;
    int startupObjectsArrLen;
    int startupObjectsCount;

    int id;

    int scopesToLoad  [MAX_SCOPES_TO_LOAD  ];
    int scopesToLoadCount;

    int scopesToUnload[MAX_SCOPES_TO_UNLOAD];
    int scopesToUnloadCount;

    void (*onLoad)(struct _gameScene* scene);

    int destroyObjects;
    int freeObjects;

} gameScene_t;

typedef struct _publicObject {
    int id;
    gameObject_t* (*init)();

} publicObject_t;

gameObject_t** scmGetObjects(int *count);
gameScene_t* scmGetActiveScene();
int scmGetObjectsCount(void);

int scmHasObject(gameObject_t *object);
void scmPushObject(gameObject_t *object);
void scmDestroyObject(gameObject_t *object, int free);
void scmDestroyAllObjects(int free);

void scmPushPublicObject(int id, gameObject_t* (*init)());
void scmPushScene(gameScene_t *scene);
void scmLoadScene(int id);
gameScene_t* scmGetScene(int id);
publicObject_t* scmGetPublicObject(int id);
int scmHasScene(int id);

gameScene_t* createScene(int id, int scope);

void scmAddScopeToLoad(gameScene_t* scene, int scope);
void scmAddScopeToUnload(gameScene_t* scene, int scope);
void scmAddStartupObject(gameScene_t *scene, gameObject_t *object);

#endif //ZOMBOID2_GAMESCENE_H
