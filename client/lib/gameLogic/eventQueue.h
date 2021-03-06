//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_EVENTQUEUE_H
#define ZOMBOID2_EVENTQUEUE_H

#include <malloc.h>
#include <assert.h>
#include <memory.h>

#include "gameObject.h"

#define EVT_KeyDown 0
#define EVT_KeyUp 1
#define EVT_CharKeyDown 2
#define EVT_CharKeyUp 3
#define EVT_MouseClick 4
#define EVT_MouseMove 5
#define EVT_MouseEntry 6
#define EVT_Update 7

#define MAX_CL_EVENTS 200
#define MAX_KB_EVENTS 20
#define MAX_MS_EVENTS 5

#define MAXCOLLISTENERS_START 1024
#define MAXEVENTS_START 256
#define MAXLISTENERS_START 1024

#define SIZE_INCREASE 1.2

#define MB_LEFT 0
#define MB_RIGHT 2
#define MB_MIDDLE 1
#define MB_WHEEL_UP 3
#define MB_WHEEL_DOWN 4

#define MS_PRESSED 0
#define MS_RELEASED 1

typedef struct _registeredNode
{

    int eventType;
    gameObject_t* object;

    void (* callback)(gameObject_t*, void*);

} eventListener_t;

typedef struct _collisionEventListener
{
    int collisionWith;
    gameObject_t* object;
    void (* callback)(gameObject_t*, gameObject_t*);

} collisionEventListener_t;


typedef struct _event
{

    int eventType;
    void* data;

} event_t;

typedef struct _keyboardEvent
{

    int key;
    int x;
    int y;

} keyboardEvent_t;

typedef struct _mouseEvent
{

    int mouse;
    int state;
    int x;
    int y;

} mouseEvent_t;

typedef struct _collisionEvent
{
    gameObject_t* object;

} collisionEvent_t;

collisionEvent_t* createCollisionEvent(gameObject_t* sub);
keyboardEvent_t* createKeyboardEvent(int key, int x, int y);
mouseEvent_t* createMouseEvent(int mouse, int state, int x, int y);
event_t* createEvent();
void freeEvent(event_t* ev);
void evqInit(void);
int evqGetListenersCount(void);
int evqGetColListenersCount(void);
collisionEventListener_t** evqGetCollisionListeners(size_t* count);

void evqSubscribeCollisionEvent(gameObject_t* object, int collisionWith, void (* callback)(gameObject_t*, gameObject_t*));
void evqSubscribeEvent(gameObject_t* object, int eventType, void (* callback)(gameObject_t*, void*));
void evqUnsubscribeEvent(gameObject_t* object, int eventType);
void evqUnsubscribeEvents(gameObject_t* object);
void evqPushEvent(int eventType, void* data);
event_t* evqNextEvent(void);
void evqResetEvents(void);

#endif //ZOMBOID2_EVENTQUEUE_H
