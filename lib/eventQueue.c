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

event* createEvent()
{
    event* ev = malloc(sizeof(event));
    ev->data = NULL;
    return ev;
}

int evqGetListenersCount(void)
{
    return listenersCount;
}

void freeEvent(event* ev)
{
    if(ev->data) free(ev->data);
}

void evqSubscribeEvent(gameObject *object, int eventType, void (*callback)(gameObject *, void *))
{
    assert(listenersCount < MAXLISTENERS);

    registeredListeners[listenersCount] = malloc(sizeof(registeredNode));
    registeredListeners[listenersCount]->object = object;
    registeredListeners[listenersCount]->eventType = eventType;
    registeredListeners[listenersCount]->callback = callback;

    listenersCount++;
}

int remove_node(registeredNode** from, int total, int index)
{
    if((total - index - 1) > 0) {
        memmove(from + index, from + index + 1, sizeof(registeredNode*) * (total-index - 1));
    }
    return total-1; // return the new array size
}

void evqUnsubscribeEvents(gameObject *object)
{
    for(int i = listenersCount - 1; i >= 0; i--) {
        if(registeredListeners[i]->object == object) {
            free(registeredListeners[i]);
            listenersCount = remove_node(registeredListeners, listenersCount, i);
        }
    }
}

void evqUnsubscribeEvent(gameObject *object, int eventType)
{
    for(int i = 0; i < listenersCount; i++) {
        if(registeredListeners[i]->object == object && registeredListeners[i]->eventType == eventType) {
            free(registeredListeners[i]);
            listenersCount = remove_node(registeredListeners, listenersCount, i);
            return;
        }
    }
}

void evqPushEvent(int eventType, void* data)
{
    assert(eventCount < MAXEVENTS);
    int index = eventCount++;
    eventQueue[index]->data = data;
    eventQueue[index]->eventType = eventType;
}

event* evqNextEvent(void)
{
    if(eventCount > 0)
    {
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

void evqResetEvents(void)
{
    eventCount = 0;
}

void evqInit(void)
{
    for(int i = 0; i < MAXEVENTS; i++) {
        eventQueue[i] = createEvent();
    }
}
