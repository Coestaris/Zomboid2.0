//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_GAMESCENE_H
#define ZOMBOID2_GAMESCENE_H

#include <memory.h>

#include "gameobject.h"
#include "texManager.h"

#define MAXSCENES 256
#define MAXOBJECTS 1024

typedef struct
{
    gameObject** startupObjects;
    int startupObjectsArrLen;
    int startupObjectsCount;

    int scope;
    int id;

} gameScene;

gameObject** getObjects(int* count);

void pushObject(gameObject* object);
void destroyObject(gameObject* object, int free);
void destroyAllObjects(int free);

void pushScene(gameScene* scene);

void loadScene(int id, int loadScope, int destroyObjects, int freeObjects);

gameScene* createScene(int id, int scope);
void addStarupObject(gameScene* scene, gameObject* object);

#endif //ZOMBOID2_GAMESCENE_H
