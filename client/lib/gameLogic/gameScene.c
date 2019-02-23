//
// Created by maxim on 1/24/19.
//

#include "gameScene.h"

gameScene* scenes[MAXSCENES];
gameObject* objects[MAXOBJECTS];
publicObject* publicObjects[MAXOBJECTS];

int scenesCount = 0;
int objectsCount = 0;
int publicObjectCount = 0;

int currentScene = -1;

void scmPushPublicObject(int id, gameObject* (*init)())
{
    assert(publicObjectCount <= MAXOBJECTS);

    publicObject* po = malloc(sizeof(publicObject));
    po->id = id;
    po->init = init;
    publicObjects[publicObjectCount++] = po;
}

publicObject* scmGetPublicObject(int id)
{
    for(int i = 0; i < publicObjectCount; i++) {
        if(publicObjects[i]->id == id) {
            return publicObjects[i];
        }
    }

    return NULL;
}


gameScene* scmGetActiveScene()
{
    return scenes[currentScene];
}

gameObject** scmGetObjects(int *count)
{
    if(currentScene != -1) {
        *count = objectsCount;
        return  objects;
    }

    return NULL;
}

int scmHasObject(gameObject *object)
{
    for(int i = 0; i < objectsCount; i++)
        if(objects[i] == object) return 1;
    return 0;
}

void scmPushObject(gameObject *object)
{
    assert(object != NULL);

    if(currentScene != -1 && object->onInit) {
        object->onInit(object);
    }

    for(int i = 0; i < objectsCount; i++)
    {
        if(objects[i]->depth <= object->depth)
        {
            memmove (&objects[i + 1], &objects[i], (objectsCount - i) * sizeof(gameObject*));
            objects[i] = object;
            objectsCount++;
            return;
        }
    }

    objects[objectsCount++] = object;
}

void scmDestroyAllObjects(int free)
{
    if(free) for(int i = 0; i < objectsCount; i++)
        freeObject(objects[i]);
    memset(objects, 0, sizeof(gameObject*) * MAXOBJECTS);
    objectsCount = 0;
}

int remove_element(gameObject** from, int total, int index) {
    if((total - index - 1) > 0) {
        memmove(from + index, from + index + 1, sizeof(gameObject*) * (total-index - 1));
    }
    return total-1; // return the new array size
}

void scmDestroyObject(gameObject *object, int free)
{
    evqUnsubscribeEvents(object);
    for(int i = 0; i < objectsCount; i++)
    {
        if(objects[i] == object)
        {
            if(free) freeObject(object);
            objects[i] = NULL;
            objectsCount = remove_element(objects, objectsCount, i);
            return;
        }
    }
}

void scmPushScene(gameScene *scene)
{
    assert(scenesCount <= MAXSCENES);

    scenes[scenesCount++] = scene;
}

gameScene* scmGetScene(int id)
{
    for(int i = 0; i < scenesCount; i++) {
        if(id == scenes[i]->id) {
            return scenes[i];
        }
    }
    return NULL;
}

void scmLoadScene(int id)
{
    for(int i = 0; i < scenesCount; i++)
    {
        if(scenes[i]->id == id)
        {
            if (scenes[i]->scopesToUnloadCount != 0) {
                for(int j = 0; j < scenes[i]->scopesToUnloadCount; j++) {
                    texmUnloadScope(scenes[i]->scopesToUnload[j]);
                }
            }

            if (scenes[i]->scopesToLoadCount != 0) {
                for(int j = 0; j < scenes[i]->scopesToLoadCount; j++) {
                    texmLoadScope(scenes[i]->scopesToLoad[j]);
                }
            }

            currentScene = i;

            if(scenes[i]->destroyObjects)
            {
                scmDestroyAllObjects(scenes[i]->freeObjects);
                objectsCount = scenes[i]->startupObjectsCount;
                memcpy(objects, scenes[i]->startupObjects, sizeof(gameObject*) * objectsCount);
            }
            else
            {
                memcpy(
                        objects + objectsCount * sizeof(gameObject*),
                        scenes[i]->startupObjects,
                        sizeof(gameObject*) * scenes[i]->startupObjectsCount
                        );
                objectsCount += scenes[i]->startupObjectsCount;
            }

            for(int j = 0; j < scenes[i]->startupObjectsCount; j++) {
                if (scenes[i]->startupObjects[j]->onInit) {
                    scenes[i]->startupObjects[j]->onInit(scenes[i]->startupObjects[j]);
                }
                if (scenes[i]->startupObjects[j]->drawable && !scenes[i]->startupObjects[j]->cachedTex)
                    scenes[i]->startupObjects[j]->cachedTex = texmGetID(scenes[i]->startupObjects[j]->texID);
            }

            if(scenes[i]->onLoad)
                scenes[i]->onLoad(scenes[i]);

            return;
        }
    }

    puts("You must specify scene with id 0");
    exit(1);
}

gameScene* createScene(int id, int scope)
{
    gameScene* scene = malloc(sizeof(gameScene));
    scene->scope = scope;
    scene->id = id;
    scene->scopesToLoadCount = 0;
    scene->scopesToUnloadCount = 0;
    scene->cachedBack = NULL;
    scene->startupObjectsCount = 0;
    scene->onLoad = NULL;
    scene->startupObjectsArrLen = 0;
    scene->freeObjects = 1;
    scene->destroyObjects = 1;
    return scene;
}

int scmGetObjectsCount(void)
{
    return objectsCount;
}

void scmAddScopeToLoad(gameScene* scene, int scope)
{
    scene->scopesToLoad[scene->scopesToLoadCount++] = scope;
}

void scmAddScopeToUnload(gameScene* scene, int scope)
{
    scene->scopesToUnload[scene->scopesToUnloadCount++] = scope;
}

void scmAddStartupObject(gameScene *scene, gameObject *object)
{
    if(scene->startupObjectsArrLen == 0)
    {
        scene->startupObjectsArrLen = 5;
        scene->startupObjects = malloc(scene->startupObjectsArrLen * sizeof(gameObject));
    }
    else if(scene->startupObjectsCount == scene->startupObjectsArrLen - 1)
    {
        scene->startupObjectsArrLen *= 2;
        scene->startupObjects = realloc(scene->startupObjects, scene->startupObjectsArrLen * sizeof(gameObject));
    }
    scene->startupObjects[scene->startupObjectsCount++] = object;
}