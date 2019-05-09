//
// Created by maxim on 3/2/19.
//

#include "menu_container.h"

void menuSetFocused(gameObject_t* cont, int state)
{
    menu_container_data_t* cd = cont->data;
    for (int i = 0; i < cd->childs_count; i++)
    {
        if (cd->childs[i]->setFocused)
            cd->childs[i]->setFocused(cd->childs[i], state);
    }
}

void menuSetEnabled(gameObject_t* cont, int mode, int state)
{
    menu_container_data_t* cd = cont->data;

    if (mode == SETENABLE_MODE_CURRENT_ELEMENT)
    {
        for (int i = 0; i < cd->childs_count; i++)
        {
            if (cd->childs[i]->setEnable)
            {
                cd->childs[i]->setEnable(cd->childs[i], state);
            }
        }

    }
    else if (mode == SETENABLE_MODE_REC_CHILDS)
    {
        for (int i = 0; i < cd->childs_count; i++)
        {
            if (cd->childs[i]->isContainer)
            {
                menuSetEnabled(cd->childs[i]->object, mode, state);
            }
            else
            {
                if (cd->childs[i]->setEnable)
                {
                    cd->childs[i]->setEnable(cd->childs[i], state);
                }
            }
        }
    }
    else if (mode == SETENABLE_MODE_REC_PARENTS)
    {
        if (cd->parent != NULL)
        {
            menuSetEnabled(cd->parent, mode, state);
        }
        for (int i = 0; i < cd->childs_count; i++)
        {
            if (cd->childs[i]->setEnable)
            {
                cd->childs[i]->setEnable(cd->childs[i], state);
            }
        }
    }
}

void menuDestroy(gameObject_t* cont)
{
    menu_container_data_t* cd = cont->data;
    for (int i = 0; i < cd->childs_count; i++)
    {
        if (cd->childs[i]->isContainer)
        {
            menuDestroy(cd->childs[i]->object);
        }
        else
        {
            menuFreeChild(cd->childs[i], true, true);
        }
    }
    scmDestroyObject(cont, true);
}

menu_container_child_t* menuCreateChild(gameObject_t* obj)
{
    menu_container_child_t* child = malloc(sizeof(menu_container_child_t));
    child->object = obj;
    child->isContainer = false;
    child->setEnable = NULL;
    return child;
}

void menuFreeChild(menu_container_child_t* child, int destroyObject, int freeObject)
{
    if (destroyObject) scmDestroyObject(child->object, freeObject);
    free(child);
}

gameObject_t* menuPushChild(gameObject_t* cont, menu_container_child_t* child, int push)
{
    menu_container_data_t* cd = cont->data;
    if (cd->childs_len == 0)
    {
        cd->childs_len = 5;
        cd->childs = malloc(sizeof(menu_container_child_t) * cd->childs_len);
    }
    else if (cd->childs_count == cd->childs_len - 1)
    {
        cd->childs_len *= 2;
        cd->childs = realloc(cd->childs, sizeof(menu_container_child_t) * cd->childs_len);
    }

    cd->childs[cd->childs_count++] = child;
    if (push) scmPushObject(child->object);
    child->parent = cont;
}

void onDestroy(gameObject_t* this)
{
    menuDestroy(this);
}

gameObject_t* menuCreate(gameObject_t* parent)
{
    gameObject_t* this = object();
    this->data = malloc(sizeof(menu_container_data_t));
    menu_container_data_t* cd = this->data;

    //this->onDestroy = onDestroy;
    cd->parent = parent;
    cd->data = NULL;
    cd->childs_count = 0;
    cd->childs_len = 0;

    return this;
}
