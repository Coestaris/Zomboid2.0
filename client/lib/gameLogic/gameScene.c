//
// Created by maxim on 1/24/19.
//

#include "gameScene.h"

gameScene_t* scenes[MAXSCENES];
gameObject_t* objects[MAXOBJECTS];
publicObject_t* publicObjects[MAXOBJECTS];

int scenesCount = 0;
int objectsCount = 0;
int publicObjectCount = 0;

int currentScene = -1;

void scmPushPublicObject(int id, gameObject_t* (*init)())
{
    assert(publicObjectCount <= MAXOBJECTS);

    publicObject_t* po = malloc(sizeof(publicObject_t));
    po->id = id;
    po->init = init;
    publicObjects[publicObjectCount++] = po;
}

publicObject_t* scmGetPublicObject(int id)
{
    for(int i = 0; i < publicObjectCount; i++) {
        if(publicObjects[i]->id == id) {
            return publicObjects[i];
        }
    }

    return NULL;
}

int scmHasScene(int id)
{
    for(int i = 0; i < scenesCount; i++) {
        if(scenes[i]->id == id) {
            return 1;
        }
    }
    return 0;
}

gameScene_t* scmGetActiveScene()
{
    return scenes[currentScene];
}

gameObject_t** scmGetObjects(int *count)
{
    if(currentScene != -1) {
        *count = objectsCount;
        return  objects;
    }

    return NULL;
}

int scmHasObject(gameObject_t *object)
{
    for(int i = 0; i < objectsCount; i++)
        if(objects[i] == object) return 1;
    return 0;
}

void scmPushObject(gameObject_t *object)
{
    assert(object != NULL);

    if(currentScene != -1 && object->onInit) {
        object->onInit(object);
    }

    //Order now doesnt matters
    /*for(int i = 0; i < objectsCount; i++)
    {
        if(objects[i]->depth <= object->depth)
        {
            memmove (&objects[i + 1], &objects[i], (objectsCount - i) * sizeof(gameObject_t*));
            objects[i] = object;
            objectsCount++;
            return;
        }
    }*/

    objects[objectsCount++] = object;
}

void scmDestroyAllObjects(int free)
{
    for(int i = 0; i < objectsCount; i++)
        evqUnsubscribeEvents(objects[i]);

    if(free) for(int i = 0; i < objectsCount; i++)
        freeObject(objects[i]);
    memset(objects, 0, sizeof(gameObject_t*) * MAXOBJECTS);
    objectsCount = 0;
}

int remove_element(gameObject_t** from, int total, int index) {
    if((total - index - 1) > 0) {
        memmove(from + index, from + index + 1, sizeof(gameObject_t*) * (total-index - 1));
    }
    return total-1; // return the new array size
}

void scmDestroyObject(gameObject_t *object, int free)
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

void scmPushScene(gameScene_t *scene)
{
    assert(scenesCount <= MAXSCENES);

    scenes[scenesCount++] = scene;
}

gameScene_t* scmGetScene(int id)
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
    printf("[gameScene.c]: Loading scene %i\n", id);

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

            if(currentScene != -1 && scenes[currentScene]->useLtracer) {
                ltracerReset();
            }

            currentScene = i;

            if(scenes[i]->destroyObjects)
            {
                scmDestroyAllObjects(scenes[i]->freeObjects);
                objectsCount = scenes[i]->startupObjectsCount;
                memcpy(objects, scenes[i]->startupObjects, sizeof(gameObject_t*) * objectsCount);
            }
            else
            {
                memcpy(
                        objects + objectsCount * sizeof(gameObject_t*),
                        scenes[i]->startupObjects,
                        sizeof(gameObject_t*) * scenes[i]->startupObjectsCount
                        );
                objectsCount += scenes[i]->startupObjectsCount;
            }

            for(int j = 0; j < scenes[i]->startupObjectsCount; j++)
            {
                gameObject_t* object = scenes[i]->startupObjects[j];
                if (object->onInit)
                {
                    object->onInit(object);

                    //Objects can be destroy and free itself on init function, i think its normal...
                    if(!scmHasObject(object)) continue;
                }

                if (object->drawable && !object->cachedTex)
                {
                    object->cachedTex = texmGetID(object->texID);
                    assert(object->cachedTex != NULL);

                    for(int f = 0; f < object->cachedTex->framesCount; f++)
                        assert(object->cachedTex->textureIds[f] != 0);
                }
            }

            dqnClearQueue();
            evqResetEvents();

            if(scenes[i]->onLoad)
                scenes[i]->onLoad(scenes[i]);

            return;
        }
    }

    printf("[gameScene.c][ERROR]: Unable to find scene with id %i", id);
    exit(1);
}

gameScene_t* createScene(int id, int scope)
{
    gameScene_t* scene = malloc(sizeof(gameScene_t));
    scene->id = id;
    scene->ltracerDepth = 0;
    scene->useLtracer = false;
    scene->scopesToLoadCount = 0;
    scene->scopesToUnloadCount = 0;
    scene->cachedBack = NULL;
    scene->startupObjectsCount = 0;
    scene->onLoad = NULL;
    scene->startupObjectsArrLen = 0;
    scene->freeObjects = 1;
    scene->destroyObjects = 1;

    scmAddScopeToLoad(scene, scope);

    return scene;
}

int scmGetObjectsCount(void)
{
    return objectsCount;
}

void scmAddScopeToLoad(gameScene_t* scene, int scope)
{
    scene->scopesToLoad[scene->scopesToLoadCount++] = scope;
}

void scmAddScopeToUnload(gameScene_t* scene, int scope)
{
    scene->scopesToUnload[scene->scopesToUnloadCount++] = scope;
}

void scmAddStartupObject(gameScene_t *scene, gameObject_t *object)
{
    if(scene->startupObjectsArrLen == 0)
    {
        scene->startupObjectsArrLen = 5;
        scene->startupObjects = malloc(scene->startupObjectsArrLen * sizeof(gameObject_t));
    }
    else if(scene->startupObjectsCount == scene->startupObjectsArrLen - 1)
    {
        scene->startupObjectsArrLen *= 2;
        scene->startupObjects = realloc(scene->startupObjects, scene->startupObjectsArrLen * sizeof(gameObject_t));
    }
    scene->startupObjects[scene->startupObjectsCount++] = object;
}