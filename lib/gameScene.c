//
// Created by maxim on 1/24/19.
//

#include "gameScene.h"

gameScene* scenes[MAXSCENES];
gameObject* objects[MAXOBJECTS];
int scenesCount = 0;
int objectsCount = 0;

int currentScene = -1;

gameObject** getObjects(int* count)
{
    if(currentScene != -1) {
        *count = objectsCount;
        return  objects;
    }

    return NULL;
}

void pushObject(gameObject* object)
{
    objects[objectsCount++] = object;
}

void destroyAllObjects(int free)
{
    if(free) for(int i = 0; i < objectsCount; i++)
        freeObject(objects[i]);
    memset(objects, 0, sizeof(gameObject*) * MAXOBJECTS);
    objectsCount = 0;
}

void destroyObject(gameObject* object, int free)
{
    for(int i = 0; i < objectsCount; i++)
    {
        if(objects[i] == object)
        {
            if(free) freeObject(object);
            memcpy(objects + i, objects + i + 1, (size_t)(objectsCount - i - 1));
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
    scene->startupObjectsCount = 0;
    scene->startupObjectsArrLen = 0;
    return scene;
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