//
// Created by maxim on 3/2/19.
//

#include "menu_container.h"

void menuSetEnabled(gameObject *cont, int mode, int state)
{
    menu_container_data* cd = cont->data;

    if(mode == SETENABLE_MODE_CURRENT_ELEMENT) {
        for (int i = 0; i < cd->childs_count; i++) {
            cd->childs[i]->setEnable(cd->childs[i], state);
        }

    } else if(mode == SETENABLE_MODE_REC_CHILDS) {
        for (int i = 0; i < cd->childs_count; i++) {
            if (cd->childs[i]->isContainer) {
                menuSetEnabled(cd->childs[i]->object, mode, state);
            } else {
                cd->childs[i]->setEnable(cd->childs[i], state);
            }
        }
    } else if(mode == SETENABLE_MODE_REC_PARENTS) {
        if(cd->parent != NULL) {
            menuSetEnabled(cd->parent, mode, state);
        }
        for (int i = 0; i < cd->childs_count; i++) {
            cd->childs[i]->setEnable(cd->childs[i], state);
        }
    }
}

void menuDestroy(gameObject *cont)
{
    menu_container_data* cd = cont->data;
    for (int i = 0; i < cd->childs_count; i++) {
        if (cd->childs[i]->isContainer) {
            menuDestroy(cd->childs[i]->object);
        } else {
            menuFreeChild(cd->childs[i], true, true);
        }
    }
    scmDestroyObject(cont, true);
}

menu_container_child* menuCreateChild(gameObject *obj)
{
    menu_container_child* child = malloc(sizeof(menu_container_child));
    child->object = obj;
    child->isContainer = false;
    child->setEnable = NULL;
    return child;
}

void menuFreeChild(menu_container_child *child, int destroyObject, int freeObject)
{
    if(destroyObject) scmDestroyObject(child->object, freeObject);
    free(child);
}

gameObject* menuPushChild(gameObject *cont, menu_container_child *child, int push)
{
    menu_container_data* cd = cont->data;
    if(cd->childs_len == 0)
    {
        cd->childs_len = 5;
        cd->childs = malloc(sizeof(menu_container_child) * cd->childs_len);
    }
    else if(cd->childs_count == cd->childs_len - 1)
    {
        cd->childs_len *= 2;
        cd->childs = realloc(cd->childs, sizeof(menu_container_child) * cd->childs_len);
    }

    cd->childs[cd->childs_count++] = child;
    if(push) scmPushObject(child->object);
    child->parent = cont;
}

void onDestroy(gameObject* this) {
    menuDestroy(this);
}

gameObject* menuCreate()
{
    gameObject* this = object();
    this->data = malloc(sizeof(menu_container_data));
    menu_container_data* cd = this->data;

    //this->onDestroy = onDestroy;
    cd->parent = NULL;
    cd->data = NULL;
    cd->childs_count = 0;
    cd->childs_len = 0;

    return this;
}
