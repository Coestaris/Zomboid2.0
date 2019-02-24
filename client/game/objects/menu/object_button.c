//
// Created by maxim on 2/23/19.
//

#include "object_button.h"

void button_event_update(gameObject* this, void* data)
{
    button_data* bd = this->data;
    vec_t mpos = getMousePos();

    if(isInObjectRect(this, mpos)) {
        this->frame = 1;
    } else {
        this->frame = 0;
    }
    dqnDrawText(vec_sub(this->pos, vec(bd->width / 2.0, - bd->height / 3.0)), color(1,1,1,1), bd->font, (char*)bd->string);
}

void button_event_mouseClick(gameObject* this, void* data)
{
    mouseEvent* me = data;
    if(me->mouse == MB_LEFT && me->state == MS_PRESSED && isInObjectRect(this, vec(me->x, me->y))) {
        button_data* bd = this->data;
        bd->func();
    }
}

void button_init(gameObject* this)
{
    evqSubscribeEvent(this, EVT_Update, button_event_update);
    evqSubscribeEvent(this, EVT_MouseClick, button_event_mouseClick);
}

gameObject* createButton(vec_t pos, const char* string, void* font, color_t col, int tex, void (*func)())
{
    gameObject* this = object();
    this->drawable = true;
    this->onInit = button_init;
    this->pos = pos;
    this->texID = tex;

    this->data = malloc(sizeof(button_data));
    button_data* bd = this->data;

    bd->string = string;
    bd->font = font;
    bd->col = col;
    bd->height = glutBitmapHeight(bd->font);
    bd->width = glutBitmapLength(bd->font, (const unsigned char*)bd->string);
    bd->func = func;

    return this;
}