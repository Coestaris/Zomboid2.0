//
// Created by maxim on 1/24/19.
//

#include "gameScene.h"

gameScene* scenes[MAXSCENES];
gameObject* objects[MAXOBJECTS];
int scenesCount = 0;
int objectsCount = 0;

int currentScene = -1;

gameScene* activeScene()
{
    return scenes[currentScene];
}

gameObject** getObjects(int* count)
{
    if(currentScene != -1) {
        *count = objectsCount;
        return  objects;
    }

    return NULL;
}

int hasObject(gameObject* object)
{
    for(int i = 0; i < objectsCount; i++)
        if(objects[i] == object) return 1;
    return 0;
}

void pushObject(gameObject* object)
{
    if(currentScene != -1 && object->init) {
        object->init(object);
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

void destroyAllObjects(int free)
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

void destroyObject(gameObject* object, int free)
{
    unsubscribeEvents(object);
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

void pushScene(gameScene* scene)
{
    scenes[scenesCount++] = scene;
}

void loadScene(int id, int loadScope, int destroyObjects, int freeObjects)
{
    for(int i = 0; i < scenesCount; i++)
    {
        if(scenes[i]->id == id)
        {
            if(loadScope)
            {
                if(currentScene != -1) texmUnloadScope(scenes[currentScene]->scope);
                texmLoadScope(scenes[i]->scope);
            }

            if(destroyObjects)
            {
                destroyAllObjects(freeObjects);
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

            for(int j = 0; j < scenes[i]->startupObjectsCount; j++)
                if(scenes[i]->startupObjects[j]->init)
                    scenes[i]->startupObjects[j]->init(scenes[i]->startupObjects[j]);

            currentScene = i;
        }
    }
}

gameScene* createScene(int id, int scope)
{
    gameScene* scene = malloc(sizeof(gameScene));
    scene->scope = scope;
    scene->id = id;
    scene->cachedBack = NULL;
    scene->startupObjectsCount = 0;
    scene->startupObjectsArrLen = 0;
    return scene;
}

int getObjectsCount(void)
{
    return objectsCount;
}

void addStarupObject(gameScene* scene, gameObject* object)
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