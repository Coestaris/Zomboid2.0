//
// Created by maxim on 2/5/19.
//

#include "obj_light_tracer.h"

void lightTracer_destroy(gameObject* this)
{
    ltracer_data* ld = ((lightTracer_data*)this->data)->data;
    ltracer_removeLight(ld);
}

void lightTracer_init(gameObject* this)
{
    ltracer_data* ld = ((lightTracer_data*)this->data)->data;
    ltracer_pushLight(ld);

    evqSubscribeEvent(this, EVT_Update, lightTracer_event_update);
}

void lightTracer_event_update(gameObject* this, void* data)
{
    ltracer_data* ld = ((lightTracer_data*)this->data)->data;
    ld->pos = this->pos;
    ld->angle = this->angle;
}

gameObject* createAreaLT(vec_t pos, double range, color_t color)
{
    gameObject* this = object();
    this->onInit = lightTracer_init;
    this->onDestroy = lightTracer_destroy;
    this->pos = pos;

    this->data = malloc(sizeof(lightTracer_data));
    lightTracer_data* ld = (lightTracer_data*)this->data;

    ld->data = malloc(sizeof(ltracer_data));
    ld->data->points = malloc(sizeof(relPoint_t) * 100);
    ld->data->pointsCount = 0;
    ld->data->angleRange = 0;
    ld->data->textured = false;
    ld->data->type = LT_AREA;
    ld->data->range = range;
    ld->data->disabled = false;
    ld->data->color = color;
    ld->data->pos = this->pos;
    ld->data->angle = this->angle;
    return this;
}

gameObject* createTexturedAreaLT(vec_t pos, double range, color_t color, tex2d* tex, int frame)
{
    gameObject* this = object();
    this->onInit = lightTracer_init;
    this->onDestroy = lightTracer_destroy;
    this->pos = pos;

    this->data = malloc(sizeof(lightTracer_data));
    lightTracer_data* ld = (lightTracer_data*)this->data;

    ld->data = malloc(sizeof(ltracer_data));
    ld->data->points = malloc(sizeof(relPoint_t) * 100);
    ld->data->pointsCount = 0;
    ld->data->angleRange = 0;
    ld->data->textured = true;
    ld->data->tex = tex;
    ld->data->type = LT_AREA;
    ld->data->disabled = false;
    ld->data->frame = frame;
    ld->data->range = range;
    ld->data->color = color;
    ld->data->pos = this->pos;
    ld->data->angle = this->angle;
    return this;
}

gameObject* createDirectLT(vec_t pos, double range, double angle, double width, double backoffset, color_t color, vec_t scaleFactor)
{
    gameObject* this = object();
    this->onInit = lightTracer_init;
    this->onDestroy = lightTracer_destroy;
    this->pos = pos;

    this->data = malloc(sizeof(lightTracer_data));
    lightTracer_data* ld = (lightTracer_data*)this->data;

    ld->data = malloc(sizeof(ltracer_data));
    ld->data->points = malloc(sizeof(relPoint_t) * 100);
    ld->data->pointsCount = 0;
    ld->data->backOffset = backoffset;
    ld->data->width = width;
    ld->data->textured = false;
    ld->data->type = LT_SPOT;
    ld->data->scaleFactor = scaleFactor;
    ld->data->angleRange = angle;
    ld->data->disabled = false;
    ld->data->range = range;
    ld->data->color = color;
    ld->data->pos = this->pos;
    ld->data->angle = this->angle;
    return this;
}

gameObject* createTexturedDirectLT(vec_t pos, double range, double angle, double width, double backOffset, color_t color, tex2d* tex, int frame, vec_t scaleFactor)
{
    gameObject* this = object();
    this->onInit = lightTracer_init;
    this->onDestroy = lightTracer_destroy;
    this->pos = pos;

    this->data = malloc(sizeof(lightTracer_data));
    lightTracer_data* ld = (lightTracer_data*)this->data;

    ld->data = malloc(sizeof(ltracer_data));
    ld->data->points = malloc(sizeof(relPoint_t) * 100);
    ld->data->pointsCount = 0;
    ld->data->backOffset = backOffset;
    ld->data->width = width;
    ld->data->scaleFactor = scaleFactor;
    ld->data->textured = true;
    ld->data->tex = tex;
    ld->data->frame = frame;
    ld->data->disabled = false;
    ld->data->type = LT_SPOT;
    ld->data->angleRange = angle;
    ld->data->range = range;
    ld->data->color = color;
    ld->data->pos = this->pos;
    ld->data->angle = this->angle;
    return this;
}