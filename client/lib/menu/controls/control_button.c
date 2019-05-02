//
// Created by maxim on 2/23/19.
//

#include "control_button.h"

void button_event_update(gameObject_t* this, void* data)
{
    button_data_t* bd = this->data;
    if(bd->enabled) {
        vec_t mpos = getMousePos();
        if (isInObjectRect(this, mpos)) {
            this->frame = 1;
        } else {
            this->frame = 0;
        }
    }
    dqnDrawText(vec_sub(this->pos, vec(bd->width / 2.0, -bd->height / 3.0)), bd->col, bd->font, bd->string, this->depth + 1);
}

void button_event_mouseClick(gameObject_t* this, void* data)
{
    mouseEvent_t* me = data;
    button_data_t* bd = this->data;
    if(bd->enabled) {
        if (me->mouse == MB_LEFT && me->state == MS_PRESSED && isInObjectRect(this, vec(me->x, me->y))) {
            bd->func(bd->self);
        }
    }
}

void button_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, button_event_update);
    evqSubscribeEvent(this, EVT_MouseClick, button_event_mouseClick);
}

void button_setEnable(menu_container_child_t* child, int state)
{
    ((button_data_t*)child->object->data)->enabled = state;
}

menu_container_child_t* createButton(vec_t pos, char* string, void* font, color_t col, int tex, void (*func)(menu_container_child_t*))
{
    gameObject_t* this = object();
    this->drawable = true;
    this->onInit = button_init;
    this->pos = pos;
    this->texID = tex;

    this->data = malloc(sizeof(button_data_t));
    button_data_t* bd = this->data;

    bd->string = string;
    bd->font = font;
    bd->enabled = 1;
    bd->col = col;
    bd->height = glutBitmapHeight(bd->font);
    bd->width = glutBitmapLength(bd->font, (const unsigned char*)bd->string);
    bd->func = func;
    bd->wrappedFunc = NULL;

    menu_container_child_t* child = menuCreateChild(this);
    child->setEnable = button_setEnable;
    child->setFocused = NULL;
    bd->self = child;

    return child;
}