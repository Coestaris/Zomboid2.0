//
// Created by maxim on 2/17/19.
//

#include "ltracer.h"

#define MAX_LIGHTS 100
#define MAX_EDGES 300

ltracer_data* lights[MAX_LIGHTS]; //TODO!
ltracer_edge* edges[MAX_EDGES]; //TODO!
int edgesCount = 1;
int lightCount = 0;
int idCounter = 0;

void ltracer_pushLight(ltracer_data *ld)
{
    assert(lightCount <= MAX_LIGHTS);

    if(!lightCount) {
        edges[0] = malloc(sizeof(ltracer_edge));
        edges[0]->id = -1;
        ltracer_updateEdges(edges, edgesCount);
    }

    lights[lightCount++] = ld;
}

int remove_light(ltracer_data** from, int total, int index) {
    if((total - index - 1) > 0) {
        memmove(from + index, from + index + 1, sizeof(ltracer_data*) * (total-index - 1));
    }
    return total-1; // return the new array size
}

void ltracer_removeLight(ltracer_data *ld)
{
    for(int light = 0; light < lightCount; light++)
    {
        if(lights[light] == ld) {
            free(lights[light]);
            remove_light(lights, lightCount--, light);
        }
    }
}

ltracer_edge* ltracer_pushEdge(vec_t a, vec_t b, vec_t c, vec_t d)
{
    assert(edgesCount <= MAX_EDGES);

    ltracer_edge* edge = malloc(sizeof(ltracer_edge));
    edge->id = idCounter++;
    edge->a = a;
    edge->b = b;
    edge->c = c;
    edge->d = d;

    edges[edgesCount++] = edge;

    ltracer_updateEdges(edges, edgesCount);
    return edge;
}

void ltracer_removeEdge(int edgeId)
{
    ltracer_updateEdges(edges, edgesCount);
}

void ltracer_update()
{
    for(int light = 0; light < lightCount; light++)
    {
        ltracer_data* ld = lights[light];
        ld->pointsCount = 0;

        if(ld->disabled) continue;

        double mRange = 0;

        if (ld->type == LT_AREA) {
            edges[0]->a = vec(ld->pos.x + ld->range / 2, ld->pos.y + ld->range / 2);
            edges[0]->b = vec(ld->pos.x + ld->range / 2, ld->pos.y - ld->range / 2);
            edges[0]->c = vec(ld->pos.x - ld->range / 2, ld->pos.y - ld->range / 2);
            edges[0]->d = vec(ld->pos.x - ld->range / 2, ld->pos.y + ld->range / 2);

            mRange = ld->range / 2 * M_SQRT2 + 0.001;
        }

        else if (ld->type == LT_SPOT) {

            mRange = 999999;

            vec_t v_dir = vec_normalize(vec(cos(ld->angle), sin(ld->angle)));
            vec_t v_norm = vec_normalize(vec_normal(v_dir));

            edges[0]->a = vec(ld->pos.x - v_norm.x * ld->width + v_dir.x * ld->backOffset,
                              ld->pos.y - v_norm.y * ld->width + v_dir.y * ld->backOffset);

            edges[0]->b = vec(ld->pos.x + v_norm.x * ld->width + v_dir.x * ld->backOffset,
                              ld->pos.y + v_norm.y * ld->width + v_dir.y * ld->backOffset);

            edges[0]->c = vec(ld->pos.x + v_norm.x * ld->width - v_dir.x * ld->range,
                              ld->pos.y + v_norm.y * ld->width - v_dir.y * ld->range);

            edges[0]->d = vec(ld->pos.x - v_norm.x * ld->width - v_dir.x * ld->range,
                              ld->pos.y - v_norm.y * ld->width - v_dir.y * ld->range);

            mRange = fmax(ld->range, ld->width) * M_SQRT2 + 0.001;
        }


#ifdef LTRACER_DRAW_EDGES
        dqnDrawLine(edges[0]->a, edges[0]->b, ld->color);
        dqnDrawLine(edges[0]->b, edges[0]->c, ld->color);
        dqnDrawLine(edges[0]->c, edges[0]->d, ld->color);
        dqnDrawLine(edges[0]->d, edges[0]->a, ld->color);
#endif

        for (int i = 0; i < edgesCount; i++) {

            if (i == 0) {
                ltracer_ray_single_to(ld, ld->pos, edges[i]->a, mRange);
                ltracer_ray_single_to(ld, ld->pos, edges[i]->b, mRange);
                ltracer_ray_single_to(ld, ld->pos, edges[i]->c, mRange);
                ltracer_ray_single_to(ld, ld->pos, edges[i]->d, mRange);
            } else {
                ltracer_ray_twice_to(ld, ld->pos, edges[i]->a, mRange, 0.00001);
                ltracer_ray_twice_to(ld, ld->pos, edges[i]->b, mRange, 0.00001);
                ltracer_ray_twice_to(ld, ld->pos, edges[i]->c, mRange, 0.00001);
                ltracer_ray_twice_to(ld, ld->pos, edges[i]->d, mRange, 0.00001);
            }
        }

        ltracer_sortPoints(ld);
    }

}

void ltracer_draw()
{

#ifdef LTRACER_DRAW_EDGES
    for(int i = 1; i < edgesCount; i++) {
        dqnDrawLine(edges[i]->a, edges[i]->b, color(1, 0, 1, 1));
        dqnDrawLine(edges[i]->b, edges[i]->c, color(1, 0, 1, 1));
        dqnDrawLine(edges[i]->c, edges[i]->d, color(1, 0, 1, 1));
        dqnDrawLine(edges[i]->d, edges[i]->a, color(1, 0, 1, 1));
    }
#endif

    for(int light = 0; light < lightCount; light++)
    {
        ltracer_data *ld = lights[light];

        if(ld->disabled) continue;

        if (ld->textured) {

            if (ld->type == LT_AREA) {
                dqnDrawTexPolygon(ld->tex, ld->frame, ld->points, ld->pointsCount, ld->pos, ld->color, ld->range);
            }
            else {
                dqnDrawRotatedTexPolygon(ld->tex, ld->frame, ld->points, ld->pointsCount, ld->pos, ld->color, ld->angle, ld->range, vec(ld->backOffset, 0), ld->scaleFactor);
            }

        } else {
            dqnDrawPolygon(ld->points, ld->pointsCount, ld->pos, ld->color);
        }
    }
}