//
// Created by maxim on 2/5/19.
//

#include "obj_light_tracer.h"

void lightTracer_destroy(gameObject_t* this)
{
    ltracer_data_t* ld = ((lightTracer_data_t*) this->data)->data;
    ltracerRemoveLight(ld);
}

void lightTracer_init(gameObject_t* this)
{
    ltracer_data_t* ld = ((lightTracer_data_t*) this->data)->data;
    ltracerPushLight(ld);

    evqSubscribeEvent(this, EVT_Update, lightTracer_event_update);
}

void lightTracer_event_update(gameObject_t* this, void* data)
{
    ltracer_data_t* ld = ((lightTracer_data_t*) this->data)->data;
    ld->pos = this->pos;
    ld->angle = this->angle;
}

gameObject_t* createAreaLT(vec_t pos, double range, color_t color)
{
    gameObject_t* this = object();
    this->onInit = lightTracer_init;
    this->onDestroy = lightTracer_destroy;
    this->pos = pos;

    this->data = malloc(sizeof(lightTracer_data_t));
    lightTracer_data_t* ld = (lightTracer_data_t*) this->data;

    ld->data = malloc(sizeof(ltracer_data_t));
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

gameObject_t* createTexturedAreaLT(vec_t pos, double range, color_t color, tex_t* tex, int frame)
{
    gameObject_t* this = object();
    this->onInit = lightTracer_init;
    this->onDestroy = lightTracer_destroy;
    this->pos = pos;

    this->data = malloc(sizeof(lightTracer_data_t));
    lightTracer_data_t* ld = (lightTracer_data_t*) this->data;

    ld->data = malloc(sizeof(ltracer_data_t));
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

gameObject_t*
createDirectLT(vec_t pos, double range, double angle, double width, double backoffset, color_t color, vec_t scaleFactor)
{
    gameObject_t* this = object();
    this->onInit = lightTracer_init;
    this->onDestroy = lightTracer_destroy;
    this->pos = pos;

    this->data = malloc(sizeof(lightTracer_data_t));
    lightTracer_data_t* ld = (lightTracer_data_t*) this->data;

    ld->data = malloc(sizeof(ltracer_data_t));
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

gameObject_t*
createTexturedDirectLT(vec_t pos, double range, double angle, double width, double backOffset, color_t color,
                       tex_t* tex, int frame, vec_t scaleFactor)
{
    gameObject_t* this = object();
    this->onInit = lightTracer_init;
    this->onDestroy = lightTracer_destroy;
    this->pos = pos;

    this->data = malloc(sizeof(lightTracer_data_t));
    lightTracer_data_t* ld = (lightTracer_data_t*) this->data;

    ld->data = malloc(sizeof(ltracer_data_t));
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