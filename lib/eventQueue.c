//
// Created by maxim on 1/23/19.
//

#include "eventQueue.h"

registeredNode* registeredListeners[MAXLISTENERS];
event* eventQueue[MAXEVENTS];

int listenersCount = 0;
int eventCount = 0;

keyboardEvent* createKeyboardEvent(int key, int x, int y)
{
    keyboardEvent* ev = malloc(sizeof(keyboardEvent));
    ev->key = key;
    ev->x = x;
    ev->y = y;
    return ev;
}

mouseEvent* createMouseEvent(int mouse, int state, int x, int y)
{
    mouseEvent* ev = malloc(sizeof(mouseEvent));
    ev->mouse = mouse;
    ev->state = state;
    ev->x = x;
    ev->y = y;
    return ev;
}

event* createEvent(int type, void* data)
{
    event* ev = malloc(sizeof(event));
    ev->data = data;
    ev->eventType = type;
    return  ev;
}

void freeEvent(event* ev)
{
    if(ev->data) free(ev->data);
    free(ev);
}

void subscribeEvent(gameObject *object, int eventType, void (*callback)(gameObject*, void *))
{
    assert(listenersCount < MAXLISTENERS);

    registeredListeners[listenersCount] = malloc(sizeof(registeredNode));
    registeredListeners[listenersCount]->object = object;
    registeredListeners[listenersCount]->eventType = eventType;
    registeredListeners[listenersCount]->callback = callback;

    listenersCount++;
}

void unsubscribeEvent(gameObject* object, int eventType)
{
    for(int i = 0; i < listenersCount; i++) {
        if(registeredListeners[i]->object == object && registeredListeners[i]->eventType == eventType) {
            free(registeredListeners[i]);
            memcpy(registeredListeners + i, registeredListeners + i + 1, (size_t)(listenersCount - i - 1));
        }
    }
}

void evqPushEvent(event* ev)
{
    assert(eventCount < MAXEVENTS);
    eventQueue[eventCount++] = ev;
}

event* evqNextEvent(void)
{
    if(eventCount > 0) {
        event* ev = eventQueue[--eventCount];
        for(int i = 0; i < listenersCount; i++)
        {
            if(registeredListeners[i]->eventType == ev->eventType)
            {
                registeredListeners[i]->callback(registeredListeners[i]->object, ev->data);
            }
        }
        return ev;
    }
    else return NULL;
}

void resetEvents(void)
{
    eventCount = 0;
}