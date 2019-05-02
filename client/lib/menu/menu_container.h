//
// Created by maxim on 3/2/19.
//

#ifndef ZOMBOID2_MENU_CONTAINER_H
#define ZOMBOID2_MENU_CONTAINER_H

#include "../helpers.h"
#include "../gameLogic/gameScene.h"
#include "../gameLogic/gameobject.h"

#define SETENABLE_MODE_CURRENT_ELEMENT 0
#define SETENABLE_MODE_REC_PARENTS 1
#define SETENABLE_MODE_REC_CHILDS 2

typedef struct _menu_container_child {
    int isContainer;

    void (*setEnable)(struct _menu_container_child*, int state);
    void (*setFocused)(struct _menu_container_child*, int state);

    gameObject_t* object;
    gameObject_t* parent;

} menu_container_child_t;

typedef struct _menu_container_data {

    menu_container_child_t** childs;
    gameObject_t* parent;

    int childs_count;
    int childs_len;

    void* data;

} menu_container_data_t;

void menuSetEnabled(gameObject_t* cont, int mode, int state);
void menuSetFocused(gameObject_t* cont, int state);

void menuDestroy(gameObject_t *cont);

gameObject_t* menuPushChild(gameObject_t* cont, menu_container_child_t *child, int push);

menu_container_child_t* menuCreateChild(gameObject_t* obj);
void menuFreeChild(menu_container_child_t *child, int destroyObject, int freeObject);

gameObject_t* menuCreate(gameObject_t* parent);


#endif //ZOMBOID2_MENU_CONTAINER_H
