//
// Created by maxim on 1/23/19.
//

#include "eventQueue.h"

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

#define MAXEVENTS 256

event* eventQueue[MAXEVENTS];
int eventCount = 0;

void evqPushEvent(event* ev)
{
    assert(eventCount < MAXEVENTS);
    eventQueue[eventCount++] = ev;
}

event* evqNextEvent(void)
{
    if(eventCount > 0) return eventQueue[--eventCount];
    else return NULL;
}

void resetEvents(void)
{
    eventCount = 0;
}