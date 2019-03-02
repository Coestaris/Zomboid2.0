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

    gameObject* object;
    gameObject* parent;

} menu_container_child;

typedef struct _menu_container_data {

    menu_container_child** childs;
    gameObject* parent;

    int childs_count;
    int childs_len;

    void* data;

} menu_container_data;

void menuSetEnabled(gameObject *cont, int mode, int state);
void menuDestroy(gameObject *cont);

gameObject* menuPushChild(gameObject *cont, menu_container_child *child, int push);

menu_container_child* menuCreateChild(gameObject *obj);
void menuFreeChild(menu_container_child *child, int destroyObject, int freeObject);

gameObject* menuCreate();


#endif //ZOMBOID2_MENU_CONTAINER_H