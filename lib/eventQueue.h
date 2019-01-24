//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_EVENTQUEUE_H
#define ZOMBOID2_EVENTQUEUE_H

#include <malloc.h>
#include <assert.h>
#include <memory.h>

#include "gameobject.h"

#define EVT_KeyDown 0
#define EVT_KeyUp 1
#define EVT_CharKeyDown 2
#define EVT_CharKeyUp 3
#define EVT_MouseClick 4
#define EVT_MouseMove 5
#define EVT_MouseEntry 6
#define EVT_Update 7

#define MAXEVENTS 256
#define MAXLISTENERS 1024 //TODO

#define MB_LEFT 0
#define MB_RIGHT 2
#define MB_MIDDLE 1

#define MS_PRESSED 1
#define MS_RELEASED 0

typedef struct {
    int eventType;
    gameObject* object;
    void (*callback)(gameObject*, void *);

} registeredNode;

typedef struct {
    int eventType;
    void* data;
} event;

typedef struct {
    int key;
    int x;
    int y;
} keyboardEvent;

typedef struct {
    int mouse;
    int state;
    int x;
    int y;
} mouseEvent;

keyboardEvent* createKeyboardEvent(int key, int x, int y);
mouseEvent* createMouseEvent(int mouse, int state, int x, int y);

event* createEvent(int type, void* data);
void freeEvent(event* ev);
int getListenersCount(void);

void subscribeEvent(gameObject *object, int eventType, void (*callback)(gameObject*, void *));
void unsubscribeEvent(gameObject* object, int eventType);
void unsubscribeEvents(gameObject* object);

void evqPushEvent(event* ev);
event* evqNextEvent(void);
void resetEvents(void);

#endif //ZOMBOID2_EVENTQUEUE_H
