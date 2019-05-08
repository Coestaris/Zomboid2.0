//
// Created by maxim on 1/23/19.
//

#include "eventQueue.h"

registeredNode_t** registeredListeners;
event_t** eventQueue;

size_t MAXLISTENERS = MAXLISTENERS_START;
size_t MAXEVENTS = MAXEVENTS_START;

keyboardEvent_t* keyboardEvents[MAX_KB_EVENTS];
mouseEvent_t* mouseEvents[MAX_MS_EVENTS];
size_t keyboardEventsCount;
size_t mouseEventsCount;

int listenersCount = 0;
int eventCount = 0;

keyboardEvent_t* createKeyboardEvent(int key, int x, int y)
{
    if(keyboardEventsCount >= MAX_KB_EVENTS) {
        puts("kb alert!"); //todo: remove
        return keyboardEvents[MAX_KB_EVENTS - 1];
    }

    keyboardEvent_t* ev = keyboardEvents[keyboardEventsCount++];
    ev->key = key;
    ev->x = x;
    ev->y = y;
    return ev;
}

mouseEvent_t* createMouseEvent(int mouse, int state, int x, int y)
{
    if(mouseEventsCount >= MAX_MS_EVENTS) {
        //puts("mouse alert!"); //todo: remove
        return mouseEvents[MAX_MS_EVENTS - 1];
    }

    mouseEvent_t* ev = mouseEvents[mouseEventsCount++];
    ev->mouse = mouse;
    ev->state = state;
    ev->x = x;
    ev->y = y;
    return ev;
}

event_t* createEvent()
{
    event_t* ev = malloc(sizeof(event_t));
    ev->data = NULL;
    return ev;
}

int evqGetListenersCount(void)
{
    return listenersCount;
}

void freeEvent(event_t* ev)
{
    //if(ev->data) free(ev->data);
}

void evqSubscribeEvent(gameObject_t *object, int eventType, void (*callback)(gameObject_t *, void *))
{
    if(listenersCount == MAXLISTENERS - 1) {
        size_t newSize = (size_t)(MAXLISTENERS * SIZE_INCREASE);
        registeredListeners = realloc(registeredListeners, newSize);
        MAXLISTENERS = newSize;
    }

    registeredListeners[listenersCount] = malloc(sizeof(registeredNode_t));
    registeredListeners[listenersCount]->object = object;
    registeredListeners[listenersCount]->eventType = eventType;
    registeredListeners[listenersCount]->callback = callback;

    listenersCount++;
}

int remove_node(registeredNode_t** from, int total, int index)
{
    if((total - index - 1) > 0) {
        memmove(from + index, from + index + 1, sizeof(registeredNode_t*) * (total - index - 1));
    }
    return total - 1;
}

void evqUnsubscribeEvents(gameObject_t *object)
{
    for(int i = listenersCount - 1; i >= 0; i--) {
        if(registeredListeners[i]->object == object) {
            free(registeredListeners[i]);
            listenersCount = remove_node(registeredListeners, listenersCount, i);
        }
    }
}

void evqUnsubscribeEvent(gameObject_t *object, int eventType)
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
    if(eventCount == MAXEVENTS - 1) {
        size_t newSize = (size_t)(eventCount * SIZE_INCREASE);
        eventQueue = realloc(eventQueue, newSize);
        for(int i = eventCount; i < newSize; i++) {
            eventQueue[i] = createEvent();
        }

        MAXEVENTS = newSize;
    }

    int index = eventCount++;
    eventQueue[index]->data = data;
    eventQueue[index]->eventType = eventType;
}

event_t* evqNextEvent(void)
{
    if(eventCount > 0)
    {
        event_t* ev = eventQueue[--eventCount];
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
    mouseEventsCount = 0;
    keyboardEventsCount = 0;
    eventCount = 0;
}

void evqInit(void)
{
    eventQueue = malloc(sizeof(event_t*) * MAXEVENTS);
    registeredListeners = malloc(sizeof(registeredNode_t*) * MAXLISTENERS);

    for(int i = 0; i < MAX_KB_EVENTS; i++) {
        keyboardEvents[i] = malloc(sizeof(keyboardEvent_t));
    }

    for(int i = 0; i < MAX_MS_EVENTS; i++) {
        mouseEvents[i] = malloc(sizeof(mouseEvent_t));
    }

    for(int i = 0; i < MAXEVENTS; i++) {
        eventQueue[i] = createEvent();
    }
}
